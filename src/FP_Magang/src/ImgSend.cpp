#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    
    image_transport::Publisher pub = it.advertise("/image", 1);

    cv::Mat image = cv::imread("/home/apt2736/FP_Magang/srcImg/bola2.jpg", cv::IMREAD_COLOR);

    cv::resize(image, image, cv::Size(900, 600));

    sensor_msgs::ImagePtr msg;
    ros::Rate loop_rate(1);

    while (nh.ok()) {
        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
        pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
}