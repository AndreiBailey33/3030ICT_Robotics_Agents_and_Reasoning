#include "assignment_3.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "controller");
    ros::NodeHandle n;

    ros::ServiceClient clientTarget = n.serviceClient<assignment3::set_target>("set_target_position");
    ros::ServiceClient clientMoves = n.serviceClient<assignment3::get_move>("get_movelist");

    assignment3::get_move srvMoves;
    assignment3::set_target srvTarget;

    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

    ros::Rate rate(5);

    geometry_msgs::Twist vel_msg;

    if(!clientTarget.call(srvTarget)){
        ROS_INFO("FAILED TO CALL SERVICE");
        return EXIT_SUCCESS;
    }

    ROS_INFO("%lf, %lf\n",srvTarget.response.x1, srvTarget.response.y1);
    srvMoves.request.x1 = srvTarget.response.x1;
    srvMoves.request.y1 = srvTarget.response.y1;
    srvMoves.request.x2 = srvTarget.response.x2;
    srvMoves.request.y2 = srvTarget.response.y2;

    if(!clientMoves.call(srvMoves)){
        ROS_INFO("FAILED TO CALL GET_MOVE SERVICE");
        return EXIT_SUCCESS;
    }
    std::cout << srvMoves.response.outfile << "\n";
    std::string str;
    std::ifstream MyReadFile(srvMoves.response.outfile);
    while(str != "<init"){
        MyReadFile >> str;
    }
    MyReadFile >> str;
    while(ros::ok()){
            while (MyReadFile >> str) {
                str.erase(std::remove(str.begin(), str.end(), '>'), str.end());
                if(str == "-"){
                    MyReadFile >> str;
                }
                if(str == "robotdeliveredpackage"){
                    continue;
                }
                str.erase(std::remove(str.begin(), str.end(), '>'), str.end());
                std::cout << str << "\n";
                if(str == "moveup"){
                    vel_msg.linear.x = -0.2;
                    pub.publish(vel_msg);
                    ros::Time start = ros::Time::now();
                    while(ros::Time::now() - start < ros::Duration(5.0));
                    vel_msg.linear.x = 0.0;
                    pub.publish(vel_msg);
                    std::cout << "Up move detected\n";
                }else if (str == "movedown"){
                    vel_msg.linear.x = 0.2;
                    pub.publish(vel_msg);
                    ros::Time start = ros::Time::now();
                    while(ros::Time::now() - start < ros::Duration(5.0));
                    vel_msg.linear.x = 0.0;
                    pub.publish(vel_msg);
                    std::cout << "down move detected\n";
                }else if(str == "moveleft"){
                    vel_msg.angular.z = -0.5;
                    pub.publish(vel_msg);
                    ros::Time start = ros::Time::now();
                    while(ros::Time::now() - start <= ros::Duration(3.0));
                    vel_msg.angular.z = 0.0;
                    vel_msg.linear.x = 0.2;
                    pub.publish(vel_msg);
                    start = ros::Time::now();
                    while(ros::Time::now() - start < ros::Duration(5.0));
                    vel_msg.linear.x = 0.0;
                    pub.publish(vel_msg);
                    vel_msg.angular.z = 0.5;
                    pub.publish(vel_msg);
                    start = ros::Time::now();
                    while(ros::Time::now() - start <= ros::Duration(3.0));
                    vel_msg.angular.z = 0.0;
                    pub.publish(vel_msg);
                    std::cout << "left Move detected\n";
                }else if(str == "moveright"){
                    vel_msg.angular.z = 0.5;
                    pub.publish(vel_msg);
                    ros::Time start = ros::Time::now();
                    while(ros::Time::now() - start <= ros::Duration(3.0));
                    vel_msg.angular.z = 0.0;
                    vel_msg.linear.x = 0.2;
                    pub.publish(vel_msg);
                    start = ros::Time::now();
                    while(ros::Time::now() - start < ros::Duration(5.0));
                    vel_msg.linear.x = 0.0;
                    pub.publish(vel_msg);
                    vel_msg.angular.z = -0.5;
                    pub.publish(vel_msg);
                    start = ros::Time::now();
                    while(ros::Time::now() - start <= ros::Duration(3.0));
                    vel_msg.angular.z = 0.0;
                    pub.publish(vel_msg);
                    std::cout << "right move detected\n";
                }else{
                    std::cout << "Delivery Complete!\n";
                    MyReadFile.close();
                    return EXIT_SUCCESS;
                }
                std::cout << str << "\n\n";
            }
            MyReadFile.close();

            rate.sleep();
            ros::spinOnce();
    }
    std::cout << "ERROR" << "\n";
    return EXIT_SUCCESS;
}
