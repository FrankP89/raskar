#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include "sensor_msgs/LaserScan.h"
#include "std_srvs/Empty.h"
#include "std_msgs/Header.h"


class convert_RawLaserScan_to_LaserScanObject
 {
 public:
 convert_RawLaserScan_to_LaserScanObject(){
 //Topic you want to publish
  pub_ = n_.advertise<sensor_msgs::LaserScan>("scan/front", 1000);

//Topic you want to subscribe
  sub_ = n_.subscribe("rplidar/scan", 1000, &convert_RawLaserScan_to_LaserScanObject::callback, this);
 }

 void callback(const sensor_msgs::LaserScan::ConstPtr& raw_lidar_msg)
 {
  sensor_msgs::LaserScan scan_msg;

  // Update frame id
  scan_msg = *raw_lidar_msg;
  scan_msg.header.frame_id = "fr_nocorner_center_lidar";

  // Publish again to scan topic
  pub_.publish(scan_msg);
 }

  private:
  ros::NodeHandle n_;
  ros::Publisher pub_;
  ros::Subscriber sub_;

};


int main(int argc, char** argv){
  // Start ROS
  ros::init(argc, argv, "lidar_transformer_front");

  ros::NodeHandle n;

  ros::Rate r(1.0);
  while(n.ok()){

    convert_RawLaserScan_to_LaserScanObject SAPObject;


    // Spin!
    ros::spin();

  }
}
