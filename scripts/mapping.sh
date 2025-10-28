#!/bin/bash
set -e
export TURTLEBOT3_MODEL=burger

# launch my world
xterm -e "roslaunch my_robot world.launch" &
sleep 10

xterm -e "roslaunch turtlebot3_slam turtlebot3_slam.launch slam_methods:=gmapping" &
sleep 5

xterm -e "roslaunch turtlebot3_slam turtlebot3_slam_rviz.launch" &
sleep 5

xterm -e "roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch"