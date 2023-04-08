#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <get_pose/GetPose.h>
#include <ros/ros.h>

ros::Subscriber pose_subscriber;
geometry_msgs::PoseWithCovarianceStamped current_pose;

bool get_pose_(get_pose::GetPose::Request &req,
              get_pose::GetPose::Response &res) {
  res.pose = current_pose.pose.pose;
  return true;
}

void pose_callback(
    const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg) {
  current_pose = *msg;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "get_pose_service");
  ros::NodeHandle nh;

  pose_subscriber = nh.subscribe("/amcl_pose", 1, pose_callback);
  ros::ServiceServer service = nh.advertiseService("get_pose", get_pose_);

  ros::spin();

  return 0;
}
