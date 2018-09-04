## chores是action所在的包
------
### C++实现:
	#include <chores/DoDishesAction.h>
	#include <actionlib/server/simple_action_server.h>

	typedef actionlib::SimpleActionServer<chores::DoDishesAction> Server;

	void execute(const chores::DoDishesGoalConstPtr& goal, Server* as)
	{
		// Do lots of awesome groundbreaking robot stuff here
		as->setSucceeded();
	}
	
	int main(int argc, char** argv)
	{
		ros::init(argc, argv, "do_dishes_server");
		ros::NodeHandle n;
		Server server(n, "do_dishes", boost::bind(&execute, _1, &server), false);
		server.start();
		ros::spin();
		return 0;
	}
------	
### Python实现:
	#! /usr/bin/env python
	
	import roslib
	roslib.load_manifest('my_pkg_name')
	import rospy
	import actionlib
	
	from chores.msg import DoDishesAction
	
	class DoDishesServer:
		def __init__(self):
		self.server = actionlib.SimpleActionServer('do_dishes', DoDishesAction, self.execute, False)
		self.server.start()

	def execute(self, goal):
		# Do lots of awesome groundbreaking robot stuff here
		self.server.set_succeeded()


	if __name__ == '__main__':
		rospy.init_node('do_dishes_server')
		server = DoDishesServer()
		rospy.spin()

### 别忘了：
- chmod +x xxx.py

