
#include "assignment_3.h"

bool get_moves(assignment3::get_move::Request &req, assignment3::get_move::Response &res){
    std::string infile = "robot_model.csp";

    std::ofstream MyFile(infile.c_str());

    MyFile << "var pos[2]:{0..10} = ["<<req.x1<<","<<req.y1<<"];\n\n";
    // Write to the file
    MyFile << "var posTarget[2]:{0..10} = ["<<req.x2<<","<<req.y2<<"];";
    // Close the file
    MyFile.close();


    std::string runfile = "robot_goals.csp";
    std::string outfile = "out.txt";
    std::string command = "mono PAT3.Console.exe -csp -engine 1 " + runfile + " " + outfile;
    std::cout << command << "\n";
    std::cout << req.x1 << " " << req.y1 << " " << req.x2 << " " << req.y2 << "\n";

    system(command.c_str());

    res.outfile = outfile;

    return true;
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtle_moves");
    ros::NodeHandle n;
    ros::ServiceServer server = n.advertiseService("get_movelist", get_moves);

    ros::spin();

    return EXIT_SUCCESS;
}
