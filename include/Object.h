#ifndef OBJECT_H
#define OBJECT_H


#include "Material.h"
#include "Shapes.h"

class Object
{
    public:
        Material material;
        Eigen::Vector3f pose_origin;
        bool is_light = false;
        virtual void is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result) = 0;
};

class Base: public Object
{
    public:
    Base();
    Cuboid floor;
    void is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result);
};
//legs are in clock wise order starting from the first quadrant
class Table: public Object
{
    public:
    Cuboid legs[4];
    Cuboid table_top;
    void is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result);
    Table();
};
class Disk: public Object
{
    public:
    Disk();
    Cylinder_curve cylinder;
    Circular_plane top;
    Circular_plane bottom;
    void is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result);
};
class Bowl: public Object
{
    public:
    Bowl();
    Hemisphere outer_hemi;
    Hemisphere inner_hemi;
    Circular_plane top;
    void is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result);
};
class Tumbler: public Object
{
    public:
    Tumbler();
    Cylinder_curve outer_cylinder;
    Cylinder_curve inner_cylinder;
    Circular_plane glass_top;
    Circular_plane glass_bottom;
    void is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result);
};
class Tumbler_fluid: public Object
{
  public:
    Tumbler_fluid();
    Cylinder_curve fluid;
    Circular_plane fluid_top;
    Circular_plane fluid_bottom;
    void is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result);  
};

#endif