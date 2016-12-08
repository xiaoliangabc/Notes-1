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
    ros::init(argc, argv, "server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("service" , judge);
    ROS_INFO_STREAM("ready to judge!");
    ros::spin();

    return 0;
}
