#include "geometry_msgs/Twist.h"
#include "math.h"
#include "ros/ros.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "calibrate_odometry");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::Duration(5.0).sleep();

  ros::Rate loop_rate(1000);
  double angular_degree = 0;
  int direction;
  n.param<double>("/angular_degree", angular_degree, 1.0);
  n.param<int>("/direction", direction, 1);

  int count = 0;
  geometry_msgs::Twist msg;

  for (size_t i = 0; i < 4; i++) {
    msg.linear.x = 0.2;
    msg.angular.z = 0;
    pub.publish(msg);
    ROS_INFO("Go straight");
    ros::Duration(5*1.3).sleep();
    count = 0;
    msg.linear.x = 0;
    msg.angular.z = 0;
    pub.publish(msg);
    pub.publish(msg);
    ROS_INFO("Exit");
    usleep(500 * 1000);
    msg.linear.x = 0;
    msg.angular.z = direction * angular_degree / 180.0 * M_PI;
    ROS_INFO("90-degree turn, msg.angular.z = %lf", msg.angular.z);
    pub.publish(msg);
    double delay = 90.0 / angular_degree;
    ROS_INFO("Delay is %lf", delay);
    ros::Duration(delay).sleep();
    // ros::Duration(38.37).sleep();
    count = 0;
    msg.linear.x = 0;
    msg.angular.z = 0;
    for (int i = 0; i < 10; i++) {
      pub.publish(msg);
      ROS_INFO(" i = %d", i);;
    }

    // usleep(500 * 1000);
  }

  return 0;
}
