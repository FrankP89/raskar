# raskar
The AGV

To install:
Dependencies to install:
apt-get install ros-melodic-move-base
apt-get install ros-melodic-gmapping
apt-get install ros-melodic-tf2-sensor-msgs
apt-get install ros-melodic-map_server


To modify:
change the relative path of the map (raskar_run/maps/5_floor_arena.yaml) to your path, after cloning. 
- (This will be changed for absolute path later)


To use:
roslaunch raskar_run navigation_gazebo_world.launch

To re-map:
roslaunch raskar_run gmapping_gazebo_world.launch
