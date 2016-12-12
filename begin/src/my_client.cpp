#include <ros/ros.h>
#include <begin/my_srv.h>
#include <cstdlib>
#include<iomanip>

int main(int argc, char **argv){
    ros::init(argc, argv, "client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<begin::my_srv>("service");
    begin::my_srv srv;
    srv.request.req = atoll(argv[1]);
    //srv.request.req  =  1;
    if(client.call(srv))
    {
        ROS_INFO_STREAM(srv.response.velocity.linear.x);
    }
    else
    {
        ROS_ERROR("Failed to judge!");
        return 1;
    }
    return 0;
}
