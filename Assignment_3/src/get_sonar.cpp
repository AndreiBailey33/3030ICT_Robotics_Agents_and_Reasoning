#include "assignment_3.h"

class Sonar_Values
{
    public:
    double x1;
    double y1;
    double x2;
    double y2;
};

Sonar_Values val;

void command(const assignment3::Sonars &msg){
    val.x1 = msg.robotx;
    val.y1 = msg.roboty;
    val.x2 = msg.targetx;
    val.y2 = msg.targety;
    ROS_INFO("%f, %f, %f, %f", msg.robotx, msg.roboty, msg.targetx, msg.targety);
    return;
}

bool set_target(assignment3::set_target::Request &req, assignment3::set_target::Response &res){
    res.x1 = val.x1;
    res.y1 = val.y1;
    res.x2 = val.x2;
    res.y2 = val.y2;
    return true;
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtle_sonars_sub");
    ros::NodeHandle n;
    ros::ServiceServer server = n.advertiseService("set_target_position", set_target);
    ros::Subscriber sub = n.subscribe("sonars", 1000, command);

    ros::spin();

    return EXIT_SUCCESS;
}
