#include "ros/service_client.h"
#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <utility>

int main(int argc, char **argv) {
  ros::init(argc, argv, "global_localization_client");
  ros::NodeHandle nh;

  ros::ServiceClient client =
      nh.serviceClient<std_srvs::Empty>("/global_localization");
  std_srvs::Empty srv;

  if (client.call(srv)) {
    ROS_INFO("Global localization service called successfully");
  } else {
    ROS_ERROR("Failed to call global localization service");
    return 1;
  }

  return 0;
}
