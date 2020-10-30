# AMR_batt
## Overview
Read battery-related information returned by the Jbd Battery Management System (BMS).\
Obtain error bits of information and the error content.\
Battery level warning alert. 
## Equipment Type
Jbd Power Lithium Battery
## Environment
Ubuntu16.04 ROS-kinetic

Updated in:
Ubuntu 18.04
ROS-Melodic 

## Nodes
alert_node.py \
jbd_bms_status.node.cpp 

### Driver
jbd_bms_status is a driver for jbd_bms. It reads battery info convert to JbdStatus message.\

### Published Topics
/batt1level \
/batt2level \
it publishes bms topic from the jbd_bms.

#### Parameters
port_bms(string, default: /dev/port_link_bms)\
serial port name used in your system.\
\
baudrate_bms(int, default: 9600)\
serial port baud rate.\
\
looprate_bms(int, default: 1)\
loop rate.\
\
jbd_id(string, default: jbd_bms)\
frame ID for the device.

## install
```bash
git clone 
cd AMR_batt
rosdep install jbd_bms_driver --ignore-src
rosdep install jbd_bms_msg
```
## rules
```bash
sudo cp 10-jbd-bms.rules /etc/udev/rules.d/ 
sudo udevadm control--reload-rules && udevadm trigger
```
## run
```bash
cd catkin_ws
catkin_make
source /devel/setup.bash
roslaunch jbd_bms_status jbd_bms_status.launch
```

