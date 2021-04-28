#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <eigen3/Eigen/Dense>

class Ray{
    public:
        Eigen::Vector3f origin;
        Eigen::Vector3f direction;
        // float intensity;
};

#endif