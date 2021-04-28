#ifndef LIGHTS_H
#define LIGHTS_H

#include <eigen3/Eigen/Dense>
#include <Shapes.h>
#include<stdio.h>

class DirectionLight {
    public:
        Eigen::Vector3f direction{0.,0.,0.};
        Eigen::Vector3f color;
};

//Sqaure shaped area light
class AreaLight{
    public:
        // Cuboid light_box;
        Eigen::Vector3f normal;
        Material material;
        Eigen::Vector3f pose;
        bool is_on = true;
        float length = 2; //side of the square
        float t;
        bool is_intersecting(Ray &pos, float &distance)
        {
            // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
            // float arr[3]={0.,0.,-1.};
            
            if(pos.direction.dot(normal) != 0)
            {
                t = (pose(2)-pos.origin(2))/pos.direction(2); 
                if(t > 0)
                {
                    if((abs(pos.origin(0)+t*pos.direction(0) - pose(0)) < (length/2)) && (abs(pos.origin(1)+t*pos.direction(1) - pose(1)) < (length/2)))
                    {
                        if(t<distance)
                        return true;
                    }
                }
            }
            return false;
        };
        AreaLight()
        {
            normal = Eigen::Vector3f(0.,0.,-1.);
            pose = Eigen::Vector3f(0.,0.,10.);
            material.diffuse_color = Eigen::Vector3f(255.,255.,255.);
            // light_box.sides = Eigen::Vector3f(2.,2.,0.01);
            // light_box.origin = pose_origin;
        }
};


    
#endif