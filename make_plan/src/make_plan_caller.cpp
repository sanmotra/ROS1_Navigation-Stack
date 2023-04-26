#include "nav_msgs/GetPlan.h"
#include "ros/ros.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "PlanExtractor"); // Initialise a ROS node
  ros::NodeHandle nh;

  // Check if we have enough command line arguments
  if (argc != 5) {
    ROS_ERROR("Invalid number of arguments. Usage: rosrun <package_name> "
              "<node_name> <start_x> <start_y> <goal_x> <goal_y>");
    return 1;
  }

  // Parse the command line arguments
  double start_x = std::stod(argv[1]);
  double start_y = std::stod(argv[2]);
  double goal_x = std::stod(argv[3]);
  double goal_y = std::stod(argv[4]);

  // Create the connection to the service /move_base
  ros::ServiceClient client =
      nh.serviceClient<nav_msgs::GetPlan>("/move_base/make_plan");

  nav_msgs::GetPlan srv; // Create an object of type GetPlan

  srv.request.start.header.frame_id = "map";
  srv.request.start.pose.position.x = start_x;
  srv.request.start.pose.position.y = start_y;

  srv.request.goal.header.frame_id = "map";
  srv.request.goal.pose.position.x = goal_x;
  srv.request.goal.pose.position.y = goal_y;
  srv.request.goal.pose.orientation.w = -1;

  if (client.call(srv)) {
    if (srv.response.plan.poses.size() > 0) {
      for (int i = 0; i < srv.response.plan.poses.size(); i++) {
        double x = srv.response.plan.poses[i].pose.position.x;
        double y = srv.response.plan.poses[i].pose.position.y;
        double w = srv.response.plan.poses[i].pose.orientation.w;
        ROS_INFO("Position in plan %d: x = %f, y = %f, w = %f", i + 1, x, y, w);
      }
    } else {
      ROS_WARN("Empty plan returned");
    }
  } else {
    ROS_ERROR("Failed to call service move_base/make_plan");
    return 1;
  }

  return 0;
}
