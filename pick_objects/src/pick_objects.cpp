#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/String.h>
 
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");
  
  ros::NodeHandle n;
  ros::Publisher status_pub = n.advertise<std_msgs::String>("/pick_obj_status", 20);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  std_msgs::String msg;

  msg.data = "pick_up_start";
  status_pub.publish(msg);
  ROS_INFO("Pick up session start!");

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  
  // Define goal for pick up
  goal.target_pose.pose.position.x = -4.35;
  goal.target_pose.pose.position.y = -2.72;
  goal.target_pose.pose.orientation.w = 0.02;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal for pick up!");
  ac.sendGoal(goal);
  
  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Arrive at the pick up zone.");
    msg.data = "reached_pick_up";
    status_pub.publish(msg);
  }
  else{

    ROS_INFO("Fail to arrive at the pick up zone.");
  }

  // Wait 5 sec
  ros::Duration(5.0).sleep();


  msg.data = "drop_off_start";
  status_pub.publish(msg);
  ROS_INFO("Drop off session start!");

  goal.target_pose.header.stamp = ros::Time::now();
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -2.28;
  goal.target_pose.pose.position.y = 2.76;
  goal.target_pose.pose.orientation.w = 0.96;
  
  ROS_INFO("Sending goal for drop off!");
  ac.sendGoal(goal);
  
  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Arrive at the drop off zone.");
    msg.data = "reached_drop_off";
    status_pub.publish(msg);
  }
  else
  {
    ROS_INFO("Fail to arrive at the drop off zone.");
  }
  return 0;
}