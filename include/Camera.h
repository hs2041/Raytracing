#ifndef CAMERA_H
#define CAMERA_H

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <cmath>
class Camera{
    public:
        Eigen::Vector3f pose;
        Eigen::Vector3f focus_point;
        
        float fov_x;
        float fov_y;
        // void update_pose(Eigen::Matrix3f turn);
        Camera():fov_x(75.0),fov_y(50.0)
        {
            pose = Eigen::Vector3f(10., -50, 30); //desired position
            // pose = Eigen::Vector3f(0., -40., 0);
            focus_point = Eigen::Vector3f(0.0,0.0,0.0);
        }
        void update_pose(Eigen::Matrix3f turn)
        {
            pose = pose.transpose()* turn;
        }
};
#endif