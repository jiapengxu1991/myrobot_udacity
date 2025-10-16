#!/bin/sh
# Launch Gazebo
xterm -e "gazebo" & 
sleep 5

# Launch roscore
xterm -e "source /opt/ros/noetic/setup.bash; roscore" & 
sleep 5

# Launch RViz
xterm -e "source /opt/ros/noetic/setup.bash; rosrun rviz rviz"