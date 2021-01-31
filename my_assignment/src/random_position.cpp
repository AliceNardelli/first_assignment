
#include "my_assignment/Position.h"
#include "ros/ros.h"

//function myrandom define the service 
bool myrandom(my_assignment::Position::Request &req, my_assignment::Position::Response &res){
 //the service has no request
 //as response it reaturns two random coordinates x and y between -6 and 6 
 res.randX= -6 + rand()%12;
 res.randY= -6 + rand()%12;
   return true;
}

int main(int argc, char** argv){
      ros::init(argc,argv,"random_position");
      //declare a new node
      ros::NodeHandle n;
      //initialize the service
      ros::ServiceServer service=n.advertiseService("/random_position", myrandom);
      ros::spin();
      return 0;
}
