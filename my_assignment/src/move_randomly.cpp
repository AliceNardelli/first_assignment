#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include "my_assignment/Position.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include <math.h>

//setting velocity
ros::Publisher pub; 
//getting random target
ros::ServiceClient client;
//public service
my_assignment::Position rand_pose;


//note that these variables must be public because of they are used both in main and in positionCallback


//return the distance between two point in 2d space
int distance(int x,int y){
      return sqrt(x^2 + y^2);
}


void positionCallback(const nav_msgs::Odometry::ConstPtr& msg){
   

    //show on the shell the actual position of the robot and the target to reach
    ROS_INFO("robot position [ %f %f]",msg->pose.pose.position.x,msg->pose.pose.position.y);
    ROS_INFO("robot target[ %f %f]",rand_pose.response.randX,rand_pose.response.randY);

    //call a geometry_msgs/Twist to set velocity
    geometry_msgs::Twist vel;
    
    //compute the distance on x and on y between actual position and target
    //d_x and d_y are vector that go from actual position to the target one
    int d_x=rand_pose.response.randX-msg->pose.pose.position.x;
    int d_y=rand_pose.response.randY-msg->pose.pose.position.y;

    //if the distance is smaller than 0.1 I ask for a new target 
    //in the other case I set velocity to get the target
    int d=distance(d_x,d_y);

    if(d<=0.1){
       //publish that target has been reached
       ROS_INFO("reached");
       //ask new target to reach
       client.call(rand_pose);  
    }

    else if(d>0.1){
      
       
      //set velocity
      //direction of velocity is given by d_x and d_y
      vel.linear.x=1*d_x;  
      vel.linear.y=1*d_y;

      //publish velocity
      pub.publish(vel);
      //show status of the robot
      ROS_INFO("reaching target");  
    }
   
}



int main(int argc, char** argv){
    
     ros::init(argc,argv,"move_randomly");
     
     //declare the new node
     ros::NodeHandle n;

     //initialize client
     client=n.serviceClient<my_assignment::Position>("/random_position");
     //call a random position
     client.call(rand_pose);

     //initialize publisher of topic /cmd_vel to set velocity
     pub=n.advertise<geometry_msgs::Twist>("/cmd_vel",1000);

     //subscriber to set position in positionCallback function
     ros::Subscriber sub=n.subscribe("/odom",1000,positionCallback);


     ros::spin();
     return 0;
}
