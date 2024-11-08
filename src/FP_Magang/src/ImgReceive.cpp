#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <FP_Magang/BallCoordinates.h>
#include <vector>

using namespace cv;
using namespace std;

FP_Magang::BallCoordinates msg;

float radius;
Point2f center;

void imageProcess(Mat image) {
    cvtColor(image, image, COLOR_BGR2HSV);
    inRange(image, Scalar(5, 135, 120), Scalar(20, 255, 255), image);

    vector<vector<Point>> contours;
    findContours(image, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    minEnclosingCircle(contours[0], center, radius);

    circle(image, center, (int)radius, Scalar(255, 0, 0), 2);

    msg.center_x = center.x;
    msg.center_y = center.y;
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    imageProcess(cv_ptr->image);

    ostringstream textStream;
    textStream << center;
    string text = textStream.str();

    putText(cv_ptr->image, text, Point(50, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1.7);
    imshow("Image", cv_ptr->image);
    waitKey(30);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "image_subscriber");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<FP_Magang::BallCoordinates>("/center", 1);
    ros::Rate rate(1);

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/image", 1, imageCallback);

    while(ros::ok()) {
        pub.publish(msg);
        ros::spinOnce();

        rate.sleep();
    }

    return 0;
}