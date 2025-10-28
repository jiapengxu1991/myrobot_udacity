#!/bin/bash
set -e
export TURTLEBOT3_MODEL=burger

# launch my world
xterm -e "roslaunch my_robot world.launch" &
sleep 10

# launch map server and load map of my world
xterm -e "rosrun map_server map_server $(rospack find my_robot)/maps/slam_map.yaml" &
sleep 5

# launch amcl node and setup initial pose
xterm -e "roslaunch turtlebot3_navigation amcl.launch initial_pose_x:=-2.435 initial_pose_y:=-0.1344 initial_pose_a:=0.00039" &
sleep 5

# launch navigation node
xterm -e "roslaunch turtlebot3_navigation move_base.launch" &
sleep 5

# launch rviz
xterm -e "roslaunch turtlebot3_gazebo turtlebot3_gazebo_rviz.launch" &
sleep 20
