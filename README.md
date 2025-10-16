# Home Service Robot Simulation

A ROS Noetic project demonstrating autonomous navigation, localization, and visual object handling using a TurtleBot3 Burger robot in Gazebo.
---
## Overview
The robot:

- Localizes itself on a pre-built map

- Navigates autonomously from a pickup zone to a drop-off zone

- Displays virtual object in RViz to show pickup and drop-off actions
---
## Core ROS Packages
| Function         | Package              | Description                               |
| ---------------- | -------------------- | ----------------------------------------- |
| Mapping      | `map_server`         | Loads pre-built map (`myworldmap.yaml`)   |
| Localization  | `amcl`               | Adaptive Monte Carlo Localization         |
| Navigation    | `move_base`          | Path planning and obstacle avoidance      |
| Visualization | `visualization_msgs` | Publishes pickup/drop-off markers in RViz |
## Node Communication
```bash
pick_objects  →  /pick_obj_status  →  add_markers
       │                             │
       └── sends goals ─────────────▶ move_base
```
---
## Environment Setup
- ROS distribution: ``Neotic``
- Run the following commands to install the required packages:
```bash
sudo apt update
sudo apt install ros-noetic-turtlebot3*
```

- All TurtleBot3-related packages can be found in the ``/opt/ros/noetic/share/`` folder.
- 🔴 **`<IMPORTANT>`** Replace ``/opt/ros/noetic/share/turtlebot3_gazebo/rviz/turtlebot3_gazebo_model.rviz`` with ``~/catkin_ws/src/rvizConfig/turtlebot3_gazebo_model.rviz``.
---
## Run Script
```bash
cd ~/catkin_ws/src/scripts
./home_service.sh 
```
