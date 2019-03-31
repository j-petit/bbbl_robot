#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"
#include <rc/motor.h>
#include <rc/led.h>

void chatterCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
  ROS_INFO_STREAM("I heard: " << msg->axes[1]);
  ROS_INFO_STREAM("I heard: " << msg->axes[3]);

  rc_motor_set(1, msg->axes[1]);
  rc_motor_set(2, msg->axes[3]);

  if (msg->axes[1] > 0.5)
  {
    rc_led_set(RC_LED_GREEN, 1);
  }
  else 
  {
    rc_led_set(RC_LED_GREEN, 0);
  }
  if (msg->axes[3] > 0.5)
  {
    rc_led_set(RC_LED_RED, 1);
  }
  else 
  {
    rc_led_set(RC_LED_RED, 0);
  }
}

int main(int argc, char **argv)
{

  int freq_hz = RC_MOTOR_DEFAULT_PWM_FREQ; 
  if (rc_motor_init_freq(freq_hz)) return -1;


  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("joy", 1000, chatterCallback);

  ros::spin();

  if (rc_motor_cleanup()) return -1;

  return 0;
}
