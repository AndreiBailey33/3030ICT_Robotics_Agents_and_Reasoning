#include "ros/ros.h"
#include "gazebo_msgs/GetModelState.h"
#include "assignment3/Sonars.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "assignment3/set_target.h"
#include "assignment3/get_move.h"
#include <math.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <string>

#define TARGET_SIZE 0.13
#define MAX_SPEED 0.22
