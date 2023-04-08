#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>

ros::Publisher pub;
ros::Subscriber sub;
geometry_msgs::PoseWithCovarianceStamped amcl_pose;

void amclCallback(
    const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg) {
  amcl_pose = *msg;
}

void moveSquare() {
  geometry_msgs::Twist vel;
  double forward_speed = 0.1;
  double turn_speed = 0.1;
  double forward_time = 5.0;
  double turn_time = 2.5;
  int num_turns = 4;

  for (int i = 0; i < num_turns; i++) {
    // Move forward
    vel.linear.x = forward_speed;
    vel.angular.z = 0.0;
    pub.publish(vel);
    ros::Duration(forward_time).sleep();

    // Turn
    vel.linear.x = 0.0;
    vel.angular.z = turn_speed;
    pub.publish(vel);
    ros::Duration(turn_time).sleep();
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "square_move");
  ros::NodeHandle nh;

  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  sub = nh.subscribe("amcl_pose", 1, amclCallback);

  moveSquare();

  ROS_INFO("Covariance of filter particles:");
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      ROS_INFO_STREAM(amcl_pose.pose.covariance[6 * i + j] << " ");
    }
    ROS_INFO_STREAM("");
  }

  return 0;
}
