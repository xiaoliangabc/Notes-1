#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include<iomanip>

void rec(const geometry_msgs::Twist & msg)
{
    ROS_INFO_STREAM(std::setprecision(2) << std::fixed
                    << "velocity  = " << msg.linear.x << "," << msg.angular.z );
}

int main (int argc, char  ** argv){
    ros::init(argc, argv, "listen");
    ros::NodeHandle nh;

   //ros::Subscriber sub = nh.subscribe ( "turtle1/cmd_vel", 1000, &rec);
    ros::Subscriber sub = nh.subscribe ( "my_Vel", 1000, &rec);
    ros::spin();
}
