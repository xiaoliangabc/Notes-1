## 单线程下的轮转
### 最简单的单线程spin的例子就是ros::spin()自己.
	ros::init(argc, argv, "my_node"); //初始化节点
	ros::NodeHandle nh;        //创建节点句柄
	ros::Subscriber sub = nh.subscribe(...);  //创建消息订阅者
	...
	ros::spin();         //调用spin(),统一处理消息
- 在这里,所有的用户回调函数将在spin()调用之后被调用.
- ros::spin()不会返回,直到节点被关闭,或者调用ros::shutdown(),或者按下ctrl+C

### 另一个常用的模式是周期性地调用ros::spinOnce():
	ros::Rate r(10); // 10 hz
	while (should_continue)
	{
		//... do some work, publish some messages, etc. ...
		ros::spinOnce();  //轮转一次,返回
		r.sleep();        //休眠
	}
	ros::spinOnce()将会在被调用的那一时间点调用所有等待的回调函数.
	注意: ros::spin()和ros::spinOnce()函数对单线程应用很有意义,目前不会应用于多线程.

## 多线程轮转
- 上面是单线程下的消息回调函数轮转,那多线程下是什么样子?
- roscpp库提供了一些内嵌的支持来从多线程中调用回调函数.
### ros::MultiThreadedSpiner
- 它是一个阻塞型轮转器,类似于ros::spin().
- 可以使用它的构造器来设定线程的个数,如果不设置或设成0,它将为每个cpu核心使用一个线程.
	ros::MultiThreadedSpinner spinner(4); // Use 4 threads
	spinner.spin(); // spin() will not return until the node has been shutdown
### ros::AsyncSpinner
- API : http://docs.ros.org/api/roscpp/html/classros_1_1AsyncSpinner.html
- 更实用的多线程轮转是异步轮转器(AsyncSpiner).相对于阻塞的spin()调用,它有自己的start()和stop()调用
- 并且在销毁后将自动停止.对上述MultiThreadedSpiner等效的AsyncSpiner使用如下:
	ros::AsyncSpinner spinner(4); // Use 4 threads
	spinner.start();
	ros::waitForShutdown();

## CallbackQueue::callAvailable() and callOne()
- CallbackQueue API 回调函数队列类: http://docs.ros.org/api/roscpp/html/classros_1_1CallbackQueue.html
- 可以创建一个回调函数队列类:
	#include <ros/callback_queue.h>
	...
	ros::CallbackQueue my_queue;
- 回调函数队列类有两种触发其内部回调函数的方法: callAvailable()方法和callOne()方法.
- 前者将获取当前可以符合条件的回调函数,并且全部触发它们;后者将简单地触发队列中最早的那个回调函数.
- 这两个方法都接受一个可选的timeout超时时间,它们将在此时间之内等待一个回调函数变得符合条件.
- 如果这个值是0,那么,如果队列中没有回调函数,该方法立即返回.

## 高级主题:使用不同的回调函数队列
- 默认的是所有的消息回调函数都会被压入全局消息回调队列.
-roscpp允许使用自定义的消息回调函数队列并分别服务.这可以以两种粒度实现:
### 每个subsceribe(),advertise(),advertiseService(),等
- 这部分可以使用高级版的方法调用原型,使用一个选项结构体指针参数.
### 每个节点句柄
- 这是常见的方法,使用节点句柄的setCallbackQueue()方法:
	ros::NodeHandle nh;
	nh.setCallbackQueue(&my_callback_queue);
- 这使所有的消息订阅者,服务,定时器等的回调函数都进入my_callback_queue,而非roscpp的默认队列.
- 这意味着,ros::spin()和ros::spinOnce()将不会触发这些回调函数.
- 用户自己必须额外调用这些回调函数.可以使用的是回调函数队列类对象的callAvailable()方法和callOne()方法
       
## 应用:
- 将不同的回调函数分别压进不同的回调函数队列有下面几个优势:
### 长时服务:
- 对一个服务的回调函数安排一个单独的队列,然后单独地使用一个线程来调用它,可以保证不会阻塞其它回调函数
### 计算消耗回调函数:
- 与长时服务相似,为一个费计算时间的回调函数安排一个单独的回调队列处理,能够减轻应用的负担.

## Demo
	#include "ros/ros.h"
	#include "ros/callback_queue.h"
	#include "std_msgs/Int64.h"

	ros::CallbackQueue queue_1;
	ros::CallbackQueue queue_2;

	void callBack_1(const std_msgs::Int64::ConstPtr& msg){
		std::cout<<"1Get: "<<msg->data<<std::endl;
		ros::Duration(3).sleep();
	}

	void callBack_2(const std_msgs::Int64::ConstPtr& msg){
		std::cout<<"2Get: "<<msg->data<<std::endl;
	}

	void callBack_3(const std_msgs::Int64::ConstPtr& msg){
		std::cout<<"3Get: "<<msg->data<<std::endl;
	}

	int main(int argc, char** argv){
		ros::init(argc, argv, "MultiThread");
		ros::NodeHandle pnh("~");
		pnh.setCallbackQueue(&queue_1);
		ros::Subscriber sub_1 = pnh.subscribe("Call1", 1, &callBack_1);
		ros::Subscriber sub_3 = pnh.subscribe("Call3", 1, &callBack_3);

		pnh.setCallbackQueue(&queue_2);
		ros::Subscriber sub_2 = pnh.subscribe("Call2", 1, &callBack_2);

		std::cout<<"Running: "<<std::endl;

		ros::AsyncSpinner spinner_1(1, &queue_1);
		spinner_1.start();

		ros::AsyncSpinner spinner_2(1, &queue_2);
		spinner_2.start();

		ros::waitForShutdown();
	}
- queue_1负责callBack_1和callBack_3
- queue_2负责callBack_2
- callBack_1 callBack_2 callBack_3触发频率都是1hz
- callBack_1中的sleep(3)阻塞了callBack_3，但是callBack_2正常触发
- 因为queue_1和queue_2是两个线程
- 如果把ros::AsyncSpinner spinner_1(1, &queue_1);中的1换成2，代表使用两个线程处理callBack_1和callBack_3，则不会发生阻塞
