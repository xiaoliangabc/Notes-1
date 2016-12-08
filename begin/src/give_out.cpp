#include <ros/ros.h>
#include "std_msgs/String.h"
#include <begin/Vel.h>
#include <geometry_msgs/Twist.h>
#include <sstream>
#include<iomanip>

int main(int argc, char ** argv){
    ros::init(argc, argv, "give_out");
    ros::NodeHandle n;
    ros::Publisher my_pub = n.advertise<begin::Vel> ("my_Vel", 1000);
    ros::Rate loop_rate(1);
    int cnt = 1;
    begin::Vel msg;
    while(ros::ok())
    {
        if((cnt%2) == 0) msg.linear.x = 1.0;
        else msg.linear.x = 2.0;
        ROS_INFO_STREAM(std::setprecision(2) << std::fixed<< "velocity  = " << msg.linear.x );
        my_pub.publish(msg);
        loop_rate.sleep();
        cnt = cnt * 3+ 1;
    }
    return 0;
}
