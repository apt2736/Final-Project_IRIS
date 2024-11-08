#include <ros/ros.h>
#include <FP_Magang/PC2BS.h>
#include <FP_Magang/BS2PC.h>
#include <FP_Magang/BallCoordinates.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <cmath>
//Aslam Pandu Tasminto
FP_Magang::PC2BS msg;

using namespace std;

float prev_enc_left = 0, prev_enc_right = 0, diff_left = 0, diff_right = 0, distMove = 0, robot_x = 0, robot_y = 0;
float tujuan_x = 0, tujuan_y = 0, enc_left = 0, enc_right = 0, th = 0;
float destBallX = 0, destBallY = 0;
bool ballPicked = false;
float theta = 0;
int status = 0; 

float dist(float tujuanX, float tujuanY) {
    return sqrt(pow(tujuanX - robot_x, 2) + pow(tujuanY - robot_y, 2));
}

float toRads(float theta1) {
    return theta1 * (M_PI / 180);
}

void processKey(char key) {
    float vel = 400;
    switch(key) {
        case 'w':
            msg.motor1 = -vel * cos(toRads(-90 - th));
            msg.motor2 = -vel * cos(toRads(150 - th));
            msg.motor3 = -vel * cos(toRads(30 - th));
            break;
        case 's':
            msg.motor1 = vel * cos(toRads(-90 - th));
            msg.motor2 = vel * cos(toRads(150 - th));
            msg.motor3 = vel * cos(toRads(30 - th));
            break;
        case 'a':
            msg.motor1 = -vel * cos(toRads(180 + th));
            msg.motor2 = -vel * cos(toRads(60 - th));
            msg.motor3 = -vel * cos(toRads(-60 - th));
            break;
        case 'd':
            msg.motor1 = vel * cos(toRads(180 + th));
            msg.motor2 = vel * cos(toRads(60 - th));
            msg.motor3 = vel * cos(toRads(-60 - th));
            break;
        case 'q':
            msg.motor1 = -vel / 2;
            msg.motor2 = -vel / 2;
            msg.motor3 = -vel / 2;
            break;
        case 'e':
            msg.motor1 = vel / 2;
            msg.motor2 = vel / 2;
            msg.motor3 = vel / 2;
            break;
        case 'z':
            msg.motor1 = 0;
            msg.motor2 = 0;
            msg.motor3 = 0;

            if (dist(msg.bola_x, msg.bola_y) < 100) {
                msg.bola_x = robot_x;
                msg.bola_y = robot_y;
                ballPicked = true;
            }
            break;
        case 'x':
            msg.motor1 = 0;
            msg.motor2 = 0;
            msg.motor3 = 0;

            ballPicked = false;
            break;
        case 'p':
            msg.motor1 = 0;
            msg.motor2 = 0;
            msg.motor3 = 0;

            if (ballPicked) {
                msg.bola_x = robot_x + (300 * sin(toRads(th)));
                msg.bola_y = robot_y + (300 * cos(toRads(th)));
                ballPicked = false;
            }
            break;
        case 'o':
            msg.motor1 = 0;
            msg.motor2 = 0;
            msg.motor3 = 0;

            if (ballPicked) {
                msg.bola_x = robot_x + (100 * sin(toRads(th)));
                msg.bola_y = robot_y + (100 * cos(toRads(th)));
                ballPicked = false;
            }
            break;
        default:
            return;
    }
}

void getKey() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    processKey(ch);
}

void updatePosition() {
    robot_x = enc_left * sin(toRads(135)) + enc_right * sin(toRads(45));
    robot_y = enc_left * cos(toRads(135)) + enc_right * cos(toRads(45));
}

void toGoal(float tujuanX, float tujuanY) {
    float deltaX = (tujuanX - robot_x);
    float deltaY = (tujuanY - robot_y);
    theta = atan2(deltaY, deltaX) * (180 / M_PI);

    if (robot_x < 0 || robot_y < 0 || robot_x > 900 || robot_y > 600) {
        msg.motor1 = 0; 
        msg.motor2 = 0;
        msg.motor3 = 0;
        return;
    }

    msg.motor1 = -(theta - (2 * deltaX)) / 3;
    msg.motor2 = -(theta + deltaX - (sqrt(3) * deltaY)) / 3;
    msg.motor3 = -(theta + deltaX + (sqrt(3) * deltaY)) / 3;
}

void circularMovement() {
    float circum = M_PI * 100;
    msg.motor1 = (circum * 2 / 3) + (-360 * 1 / 3);
    msg.motor2 = (circum * (-1 / 3)) + (-360 * 1 / 3);
    msg.motor3 = (circum * (-1 / 3)) + (-360 * 1 / 3);
}

void callback (const FP_Magang::BS2PC::ConstPtr& msgv) {
    status = msgv->status;
    tujuan_x = msgv->tujuan_x;
    tujuan_y = msgv->tujuan_y;
    enc_left = msgv->enc_left;
    enc_right = msgv->enc_right;
    th = msgv->th;
    ROS_INFO("robot_x: %f  robot_y: %f  tujuan_x: %f  tujuan_y: %f", robot_x, robot_y, tujuan_x, tujuan_y);
}

void callback2 (const FP_Magang::BallCoordinates::ConstPtr& msgv) {
    destBallX = msgv->center_x;
    destBallY = msgv->center_y;
    ROS_INFO("x: %f  y: %f", destBallX, destBallY);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "robotPub");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<FP_Magang::PC2BS>("/pc2bs", 10);
    ros::Rate rate(50);

    ros::Subscriber sub1 = nh.subscribe<FP_Magang::BS2PC>("/bs2pc", 1, callback);
    ros::Subscriber sub2 = nh.subscribe<FP_Magang::BallCoordinates>("/center", 1, callback2);

    while(ros::ok()) {
        updatePosition();
        if (ballPicked) {
            msg.bola_x = robot_x;
            msg.bola_y = robot_y;
        }

        switch (status) {
            case 1:
                getKey();
                break;
            case 2:
                ballPicked = false;

                msg.bola_x = destBallX;
                msg.bola_y = destBallY; 
                
                if (dist(msg.bola_x, msg.bola_y) > 5) {
                    toGoal(msg.bola_x, msg.bola_y);
                } else {
                    msg.motor1 = 0;
                    msg.motor2 = 0;
                    msg.motor3 = 0;
                }
                break;
            case 3:
                ballPicked = false;

                if (dist(tujuan_x, tujuan_y) > 5) {
                    toGoal(tujuan_x, tujuan_y);
                } else {
                    msg.motor1 = 0;
                    msg.motor2 = 0;
                    msg.motor3 = 0;
                }
                break;
            case 4:
                ballPicked = false;

                msg.bola_x = destBallX;
                msg.bola_y = destBallY; 
                
                if (dist(msg.bola_x, msg.bola_y) > 100) {
                    toGoal(msg.bola_x, msg.bola_y);
                } else {
                    circularMovement;
                }
                break;
        }

        pub.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}