cmake_minimum_required(VERSION 3.0.2)
project(get_pose)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  message_generation
)

add_service_files(
  FILES
  GetPose.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)

catkin_package(
  CATKIN_DEPENDS
  geometry_msgs
  roscpp
  std_msgs
  message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(get_pose_service src/get_pose_service.cpp)
target_link_libraries(get_pose_service ${catkin_LIBRARIES})
add_dependencies(get_pose_service ${PROJECT_NAME}_generate_messages_cpp)
