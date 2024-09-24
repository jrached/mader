#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

////////////Make class////////////////////////////////////
class GuessPub {
public:
//Class constructor
GuessPub(ros::NodeHandle nh);

//attributes
ros::Publisher guess_pub_;
ros::Subscriber ctrl_pnts_sub_;

//methods 
void ctrlPntsCB(const visualization_msgs::Marker::ConstPtr& msg);
};

//Define class methods////////////////////////////////////
GuessPub::GuessPub(ros::NodeHandle nh){
    //Make publisher 
    guess_pub_ = nh.advertise<visualization_msgs::Marker>("SQ01s/mader/init_guess", 1);

    //Make subscriber 
    ctrl_pnts_sub_ = nh.subscribe<visualization_msgs::Marker>("SQ01s/mader/off_ctrl_pnts", 1, &GuessPub::ctrlPntsCB, this);
}

void GuessPub::ctrlPntsCB(const visualization_msgs::Marker::ConstPtr& msg){
    //Take off_ctrl_pnts msg and publish it to init_guess topic
    guess_pub_.publish(*msg);
}


//////////////Main///////////////////////////////////////////
int main(int argc, char** argv){
    //Make node handle
    ros::init(argc, argv, "guess_publisher_node");
    ros::NodeHandle nh;
    
    //Call GuessPub funtion that 
    GuessPub guessPub(nh);

    //Keep the node running and processing callbacks
    ros::spin();

    return 0;
}