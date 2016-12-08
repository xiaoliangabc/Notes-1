#include <ros/ros.h>
//#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
//#include <sstream>
//#include <iomanip>

int main(int argc, char ** argv){
    ros::init(argc, argv, "publish_velocity");//节点的名字
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist> ("turtle1/cmd_vel", 1000);//turtle1/cmd_vel是话题的名字

    srand(time(0));

    ros::Rate rate(2);

    geometry_msgs::Twist msg;

    while(ros::ok())
    {
        msg.linear.x = double(rand())/double (RAND_MAX);
        msg.angular.z = double(rand())/double(RAND_MAX) - 1;

        pub.publish(msg);

        ROS_INFO_STREAM("Sending random velocity command : "
                        <<"linear = "<< msg.linear.x
                        <<"angular = "<< msg.angular.z);
        rate.sleep();
    }
    return 0;
}
