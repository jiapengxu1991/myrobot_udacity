#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/String.h>

ros::Publisher marker_pub;
visualization_msgs::Marker marker;


void showMarker(double x, double y)
{
  marker.header.stamp = ros::Time::now();
  marker.pose.position.x = x;
  marker.pose.position.y = y;
  marker.pose.orientation.w = 1.0;
  marker.action = visualization_msgs::Marker::ADD;
  marker_pub.publish(marker);
}

void hideMarker()
{
  marker.header.stamp = ros::Time::now();
  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);
}

void statusCallback(const std_msgs::String::ConstPtr& msg)
{
  std::string status = msg->data;
  ROS_INFO("I heard: [%s]", msg->data.c_str());

  if (status == "pick_up_start") {
    showMarker(4.5507, 2.1794);
  } 
  else if (status == "reached_pick_up") {
    hideMarker();
  } 
  else if (status == "reached_drop_off") {
    showMarker(3.9584, -3.28554);
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  ros::Subscriber sub = n.subscribe("/pick_obj_status", 20, statusCallback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  // Initialize marker common properties
  marker.header.frame_id = "map";
  marker.ns = "marker";
  marker.id = 0;
  marker.type = shape;
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0f;
  marker.lifetime = ros::Duration();

  while (marker_pub.getNumSubscribers() < 1) 
  { 
    if (!ros::ok()) 
    { 
      return 0; 
    } 
    ROS_WARN_ONCE("Please create a subscriber to the marker"); 
    sleep(1); 
  }

  ROS_INFO("add_markers ready and waiting for status updates...");
  ros::spin();
}