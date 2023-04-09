#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "send_goal_client");
  actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> client(
      "move_base", true);
  client.waitForServer();

  move_base_msgs::MoveBaseGoal goal;

  while (true) {

    //  Position
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.pose.position.x = 0.2223128080368042;
    goal.target_pose.pose.position.y = -7.395302772521973;
    goal.target_pose.pose.orientation.w = -1.0;
    client.sendGoal(goal);
    client.waitForResult();
    ROS_INFO("1st Goal reached");

    //  Position
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.pose.position.x = 1.9447038173675537;
    goal.target_pose.pose.position.y = 0.13158226013183594;
    goal.target_pose.pose.orientation.w = -1.0;
    client.sendGoal(goal);
    client.waitForResult();
    ROS_INFO("2nd Goal reached");

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.pose.position.x = -2.112874746322632;
    goal.target_pose.pose.position.y = 0.17116689682006836;
    goal.target_pose.pose.orientation.w = 1.0;
    client.sendGoal(goal);
    client.waitForResult();
    ROS_INFO("3rd Goal reached");
  }

//   if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//     ROS_INFO("Goal reached");
//   else
//     ROS_INFO("Failed to reach goal");

  return 0;
}
