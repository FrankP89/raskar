#include <ros.h>
#include <std_msgs/Float32MultiArray.h>

ros::NodeHandle nh;

std_msgs::Float32MultiArray distances;

ros::Publisher pub_ultrasound("ultrasound_data", &distances);

const int amount_of_sensor = 5;
const int distance_array_length = amount_of_sensor;
const int averaging_readings = 5; // Seconds
const int trigPin[] = {8,9,10,11,12,13};
const int echoPin[] = {2,3,4,5,6,7};
const float minDist = 0.015;
const float maxDist = 8.000;

void setup() {
  nh.initNode();
  nh.advertise(pub_ultrasound);
  
  distances.data_length = distance_array_length;
  
  for(int x=0; x< amount_of_sensor; x++) {
    pinMode(trigPin[x],OUTPUT);
    pinMode(echoPin[x],INPUT);
  }
}

float readSensor(int x) {
  float distance;
  int duration;
  
  digitalWrite(trigPin[x],LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin[x],HIGH);
  delayMicroseconds(5);
  duration = pulseIn(echoPin[x], HIGH, 10000);

  distance = duration * 0.342/2000;
  //Serial.println(distance);

  if (distance < minDist)
    distance = minDist; //defualt value as the sensor cannot reach below 0.02 meters
  if (distance > maxDist)
    distance = maxDist; //defualt value as the sensor cannot reach above 8 meters
  return distance;
}

float * data_filter(float data_averaged[distance_array_length]){
  float data_collected[averaging_readings][distance_array_length];  
  float temporary = 0;
  
  for (int time_counter= 0 ; time_counter < averaging_readings; time_counter++){
    for (int index_sensor=0; index_sensor < amount_of_sensor; index_sensor++) {
      data_collected[time_counter][index_sensor] = readSensor(index_sensor);
    }
    delay(100);
  }

  for (int index_sensor=0; index_sensor < amount_of_sensor; index_sensor++){
    for (int time_counter= 0 ; time_counter < averaging_readings; time_counter++) {
      temporary = temporary + data_collected[time_counter][index_sensor];            
    }
    data_averaged[index_sensor] = temporary/amount_of_sensor;
    Serial.println("Sensor Number: " + index_sensor);
    Serial.println(data_averaged[index_sensor]);
    Serial.print('\n');
    temporary = 0;
  }
  
  return data_averaged;
}

void loop() {
  float data_averaged[distance_array_length];
  distances.data = data_filter(data_averaged);  
  pub_ultrasound.publish(&distances);
  nh.spinOnce();
  delay(100);
}
