### 在功能包的src文件夹中新建ABC.cpp文件
------
### 打开CMakeLists.txt文件，添加如下代码
- xxx_srv是节点名，rosrun package/xxx_srv
	add_executable(xxx_srv src/ABC.cpp)   
	target_link_libraries(xxx_srv ${catkin_LIBRARIES})
	add_dependencies(xxx_srv package_name_gencpp)
------
### 把CMakLists.txt拉入Clion
- 源码结构如下
	#include <ros/ros.h>
	#include <begin/my_srv.h>
	#include<iomanip>
	bool judge(begin::my_srv::Request &req, begin::my_srv::Response &res){
		if ((req.req%2)) res.velocity.linear.x = 1.0;
		else res.velocity.linear.x = 2.0;
		ROS_INFO_STREAM(req.req);
		ROS_INFO_STREAM(std::setprecision(2) << std::fixed<< "SENDING BACK : " << res.velocity.linear.x );
		return true;
	}

	int main(int argc, char **argv){
		ros::init(argc, argv, "server");//server是节点的名字
		ros::NodeHandle n;

		ros::ServiceServer service = n.advertiseService("service" , judge);
		//service 是服务的名字
		ROS_INFO_STREAM("ready to judge!");
		ros::spin();//ros::spinOnce()的用法参考浅谈P70、155
		//如果除了服务调用之外还有其他任务要做，用spinOnce

		return 0;
	}

