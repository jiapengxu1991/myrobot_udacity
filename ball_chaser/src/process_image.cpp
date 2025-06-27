#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Moving toward the ball");

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv))
        ROS_ERROR("Failed to call service command robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    float h_pos = 0.0
    float lin_x, ang_z = 0.0
    float left_threshould = img->width/3
    float right_threshould = img->width/3 * 2
    for (size_t i = 0; i < img->height * img->step; i += 3) {
        int red = img->data[i];
        int green = img->data[i + 1];
        int blue = img->data[i + 2];
        if (red == 255 && green == 255 && blue == 255){
            float h_pos = (i / 3) % img->width
            if h_pos<left_threshould{
                // turn left
                ang_z = 0.5
                lin_x = 0.0
            }
            else if (h_pos>=left_threshould && h_pos<=right_threshould){
                //move forward
                ang_z = 0.0
                lin_x = 0.5
            }
            else if h_pos>right_threshould{
                // turn right
                ang_z = -0.5
                lin_x = 0.0
            }
            }
        else{
            //stop
            ang_z = 0.0
            lin_x = 0.0
        }
        drive_robot(lin_x, ang_z)
        break
    }
}



int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}