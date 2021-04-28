#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <tuple>
#include <math.h> 
#include <stdio.h> 
#include "Ray.h"
//is_intersect contains points of intersection, is_intersect, distance, normal to the surface
class Shape{
    public:
    Eigen::Vector3f origin;
    virtual void is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>&) = 0;   

};

// class Sphere:public Shape{
//     public:
//         float radius=40.0;
//         std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> is_intersect(Ray pos)
//         {
//             std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));

//             float dist = (pos.origin - origin).dot(pos.direction);
//             if(((pos.origin - origin).squaredNorm()) -dist*dist <= radius*radius)
//             {
//                 result = std::make_tuple(Eigen::Vector3f(0.,0.,0.),true,100000.0,Eigen::Vector3f(0.,0.,0.));
//             }
//             return result;
//         }   
//         Sphere(){
//             origin = Eigen::Vector3f(0.,0.,0.);
//         };
// };


class Hemisphere:public Shape{
    public:
        Eigen::Vector3f normal; 
        float radius;
        float norm = 1;
        void is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>&); 
        Hemisphere(){
            normal = Eigen::Vector3f(0.,0.,0.);
        }
};

//origin as at centre of base of the cylinder
class Cylinder_curve:public Shape
{
    public:
        float radius, height;
        float normal = 1.0;     
        void is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>&);
    // Eigen::Vector3f normal_to_point();
};

class Circular_plane:public Shape{
    public:
        float inner_rad, outer_rad;
        float norm = 1; //by default plane is along +z
        void is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>&);
};

//origin is at centroid
class Cuboid:public Shape
{
    public:
        float sides[2]; //along x,y and z axes respectively
        // Eigen::Vector3f normal;
        // std::tuple<Eigen::Vector3f, bool, float> find_distance(int i, float c, Ray in);
        void find_distance(int i, float c, Ray in, std::tuple<Eigen::Vector3f, bool, float>&);
        void is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>&);   
}; 

#endif