#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Range.h>

float Arr[5];
sensor_msgs::Range us[5];
float minDist = 0.015;
float maxDist = 4.000;
float fov = 0.1;

void ultrasoundCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
  int i = 0;
  // print all the remaining numbers
  for(std::vector<float>::const_iterator it = msg->data.begin(); it != msg->data.end(); ++it){
    Arr[i] = *it;
    i++;
  }

  for (int t = 0; t < sizeof(Arr) ; t++){
    us[t].radiation_type = sensor_msgs::Range::ULTRASOUND;
    us[t].range = Arr[t];    
    us[t].min_range = minDist;
    us[t].max_range = maxDist;
    us[t].field_of_view = fov;  
  }    
  
  us[0].header.frame_id =  "fr_corner_left_ultrasound";
  us[1].header.frame_id =  "fr_nocorner_left_ultrasound";
  us[2].header.frame_id =  "fr_nocorner_right_ultrasound";
  us[3].header.frame_id =  "fr_corner_right_ultrasound";
  us[4].header.frame_id =  "bk_corner_left_ultrasound";
  us[5].header.frame_id =  "bk_corner_right_ultrasound";
  
  return;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ultrasound_frame_transformer");
  ros::NodeHandle nh;
  ros::Rate loop_pub_rate(100);

  ros::Publisher pub_us1 = nh.advertise<sensor_msgs::Range>("ultrasound_1",500);
  ros::Publisher pub_us2 = nh.advertise<sensor_msgs::Range>("ultrasound_2",500);    
  ros::Publisher pub_us3 = nh.advertise<sensor_msgs::Range>("ultrasound_3",500);    
  ros::Publisher pub_us4 = nh.advertise<sensor_msgs::Range>("ultrasound_4",500);    
  ros::Publisher pub_us5 = nh.advertise<sensor_msgs::Range>("ultrasound_5",500);    
  ros::Publisher pub_us6 = nh.advertise<sensor_msgs::Range>("ultrasound_6",500);        

  ros::Subscriber sub = nh.subscribe("ultrasound_data", 1000, ultrasoundCallback);  

  while (ros::ok()) {
    pub_us1.publish(us[0]);
    pub_us2.publish(us[1]);
    pub_us3.publish(us[2]);
    pub_us4.publish(us[3]);
    pub_us5.publish(us[4]);
    pub_us6.publish(us[5]);
    ros::spinOnce();
    loop_pub_rate.sleep();
  }

  return 0;
}


