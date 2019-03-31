#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#ifdef __cplusplus
extern "C"
{
#endif
#include <rc/led.h>
#ifdef __cplusplus
}
#endif

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(100);

  int count = 0;

  while (ros::ok())
  {
    rc_led_set(RC_LED_GREEN, count % 2);

    std_msgs::String msg;
    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  rc_led_set(RC_LED_GREEN, 0);

  return 0;
}
