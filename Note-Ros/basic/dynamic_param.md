### 步骤：
-catkin_create_pkg package_name rospy roscpp dynamic_reconfigure
-mkdir cfg
-cd cfg
-新建dynamic_controller.cfg文件:

	#!/usr/bin/env python
	# -*- coding: utf-8 -*-
	PACKAGE = "gl8_controller_test"

	from dynamic_reconfigure.parameter_generator_catkin import *

	gen = ParameterGenerator()
	# 参数名，参数类型，级别，描述，缺省值，最小值，最大值
	gen.add("speed_ref", double_t, 0, "the speed of gl8", 1.0,  0.1, 1.5)
	# 参数2:cfg文件依附的节点名;参数3是生成头文件名称的前缀，要和.cfg文件的名字一致
	exit(gen.generate(PACKAGE, "gl8_controller_test", "dynamic_controller"))

-chmod a+x cfg/dynamic_controller.cfg

### 在CmakeLists里面加如下内容

	generate_dynamic_reconfigure_options(
  		cfg/dynamic_controller.cfg
	)
	add_dependencies(example_node ${PROJECT_NAME}_gencfg)

------
### 在package.xml文件里加

	<build_depend>dynamic_reconfigure</build_depend>
	<exec_depend>dynamic_reconfigure</exec_depend>

------
### 编写Node

	#include <ros/ros.h>
	#include <std_msgs/Float32.h>
	#include <geometry_msgs/Twist.h>
	#include <gl8_controller_test/gl8_controller_cmd.h>
	#include <gl8_controller_test/dynamic_controllerConfig.h>
	#include <dynamic_reconfigure/server.h>

	gl8_controller_test::gl8_controller_cmd ctrl_cmd;

	void ConfigCb(gl8_controller_test::dynamic_controllerConfig &config, uint32_t level){
    		ROS_INFO("arguements are changed!");
    		ctrl_cmd.speed_ref = config.speed_ref;
	}

	int main(int argc, char **argv){
    		ros::init(argc, argv, "gl8_controller_test");
    		ros::NodeHandle nh;
    		ros::Publisher ctrl_cmd_pub = nh.advertise<gl8_controller_test::gl8_controller_cmd> ("ctrl_cmd", 1000);
		ros::Rate loop_rate(10);

		/*dynamic config*/
		dynamic_reconfigure::Server<gl8_controller_test::dynamic_controllerConfig> server;
		dynamic_reconfigure::Server<gl8_controller_test::dynamic_controllerConfig>::CallbackType f;

    		f = boost::bind(&ConfigCb, _1, _2);
    		server.setCallback(f);

    		nh.param<double>("speed_ref", ctrl_cmd.speed_ref, 0.3);
    		nh.setParam("speed_ref", 0.4);
    		nh.getParam("speed_ref", ctrl_cmd.speed_ref);

    		//ctrl_cmd.speed_ref = 1.0;
    		//speed_ref = 1.0; // m/s
    		while (ros::ok) {
			ros::spinOnce();
        		ROS_INFO_STREAM("speed_ref: " << ctrl_cmd.speed_ref);
       			ctrl_cmd_pub.publish(ctrl_cmd);
			loop_rate.sleep();
    		}
	}

------

## 注意！！！ros::spinOnce();这个一定要加，用来处理callback函数
