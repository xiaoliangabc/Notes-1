# Thread
------
## 创建线程
	#include <iostream>
	#include <thread>
	using namespace std;

	void t1()  //普通的函数，用来执行线程
	{
	    for (int i = 0; i < 20; ++i)
	    {
		cout << "t1111\n";
	    }
	}
	void t2()
	{
	    for (int i = 0; i < 20; ++i)
	    {
		cout << "t22222\n";
	    }
	}
	int main()
	{
	    thread th1(t1);  //实例化一个线程对象th1，使用函数t1构造，然后该线程就开始执行了（t1()）
	    thread th2(t2);

	    cout << "here is main\n\n";

	    return 0;
	}
#### Tip: 上面的代码存在一个问题，主线程结束之后，其他两个线程也会直接结束，引起异常报错
------
## join方法
- join的作用是让主线程在join函数处等待，直到该子线程执行结束，再往后执行
	#include <iostream>
	#include <thread>
	using namespace std;

	void t1()
	{
	    for (int i = 0; i < 20; ++i)
	    {
		cout << "t1111\n";
	    }
	}
	void t2()
	{
	    for (int i = 0; i < 20; ++i)
	    {
		cout << "t22222\n";
	    }
	}
	int main()
	{
	    thread th1(t1);
	    thread th2(t2);
	    
	    th1.join(); //等待th1执行完
	    th2.join(); //等待th2执行完

	    cout << "here is main\n\n";

	    return 0;
	}
- 这样，当两个线程执行完之后，主程序才会执行cout并退出
#### Tips: 需要注意的是线程对象执行了join后就不再joinable了，所以只能调用join一次
------
## detach方法
- detach是用来和线程对象分离的，这样线程可以独立地执行，不过这样由于没有thread对象指向该线程而失去了对它的控制，当对象析构时线程会继续在后台执行，但是当主程序退出时并不能保证线程能执行完
	int main()
	{
	    thread th1(t1);
	    thread th2(t2);
	    
	    th1.detach();
	    th2.detach();

	    cout << "here is main\n\n";

	    return 0;
	}
#### Tips: 如果没有良好的控制机制或者这种后台线程比较重要，最好不用detach而应该使用join
------
## 注意：调用 join 或 detach 之前需要调用 joinable() 判断一下线程是否运行. 如果 joinable() 返回 false, 则不需要.

------
## 调用类内对象
	class Demo{
	Public:
		Demo(;
		~Demo();

		void Run(int a, int b);
	}

	int main(char agrc, char** argv){
		Demo* pDemo;
		std::Thread* pT;
		pDemo = new Demo();
		pT = std::thread(&Demo::Run, pDemo, 1, 2);//第一个参数是函数,第二个参数是类(如果是在类内创建就用this),后面就是函数传入的参数
		if(pT->joinable()){
			pT->join();//Program will wait here until the end of Run().
		}
	}
------
## CMakeLists.txt
- 需要加,否则编译无法通过:
	TARGET_LINK_LIBRARIES( your_executable
	pthread
	)
