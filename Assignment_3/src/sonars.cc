#include "ros/ros.h"
#include "gazebo_msgs/GetModelState.h"
#include "assignment3/Sonars.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include <math.h>
#include <stdint.h>
#include <algorithm>
#include <unistd.h>
#include <string>

#include <iostream>
#include <fstream>

assignment3::Sonars setMsg(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    assignment3::Sonars msg;
    msg.robotx = x1;
    msg.roboty = y1;
    msg.targetx = x2;
    msg.targety = y2;
    return msg;
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "sonars");
    std::string targetName = "Mailbox";
    std::string groundPlane = "ground_plane";
    std::string robotName = "turtlebot3_burger";

    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<assignment3::Sonars>("sonars", 1000);

    ros::Rate rate(100);

    gazebo_msgs::GetModelState srvRobot;
    gazebo_msgs::GetModelState srvTarget;

    srvRobot.request.relative_entity_name = groundPlane;
    srvRobot.request.model_name = robotName;

    srvTarget.request.relative_entity_name = groundPlane;
    srvTarget.request.model_name = targetName;

    ros::ServiceClient locations = n.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");

    while (ros::ok()) {

       ros::spinOnce();

       if (!locations.call(srvRobot)) {
           ROS_ERROR("Failed to query model state. Is gazebo running?");
           rate.sleep();
           continue;
       }
       if (!srvRobot.response.success) {
           ROS_ERROR("Can't find target object %s for robot %s. Is the target and robot name correct?", targetName.c_str(), robotName.c_str());
           rate.sleep();
           continue;
       }

       if (!locations.call(srvTarget)) {
           ROS_ERROR("Failed to query model state. Is gazebo running?");
           rate.sleep();
           continue;
       }
       if (!srvTarget.response.success) {
           ROS_ERROR("Can't find target object %s for robot %s. Is the target and robot name correct?", targetName.c_str(), robotName.c_str());
           rate.sleep();
           continue;
       }

       double x1 = srvRobot.response.pose.position.x;
       double y1 = srvRobot.response.pose.position.y;

       double x2 = srvTarget.response.pose.position.x;
       double y2 = srvTarget.response.pose.position.y;

       std::cout << x1 << "\n";
       std::cout << y1 << "\n\n";
       std::cout << x2 << "\n";
       std::cout << y2 << "\n\n\n";

       assignment3::Sonars msg;

       msg = setMsg(x1, y1, x2, y2);

       pub.publish(msg);
       rate.sleep();
    }
    return EXIT_SUCCESS;
}
