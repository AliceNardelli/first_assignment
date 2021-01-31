
In the project are defined two different package. assignment1 contains an olonomic robot, the world where the robot moves. Morover there are some services and messages to be used.
In the package my_assignment contains two different ROS nodes. 
The first one is a ROS service node and it is called random. The service my_assignment/Position (contained in srv directory of the package) is  published in topic /random. The code which implement the node has no request whereas as response returns the coordinates x and y of a random position between -6 and 6.
The second node called get_random is used to pilot the robot.
A subscribers of the /odom topic through the nav_msgs/Odometry gets the actual position, a client of the previous defined costum service takes a random position to achieve. Finally it is defined a publisher of the /cmd_vel topic used to set a linear velocity on x a y to the robot for achieving the target (geometry_msgs/Twist).

The olonomic robot moves as follow: he ask for a random position, if the distance betweem it a the target is greater then 0.1 it moves for achieving the target, in the other case he asks for a new target. It goes on in asking for a random target an reaches it.

To run the code is needed to execcute these nodes:
 rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world
 rosrun my_assignment random
 rosrun my_assignment get_random

