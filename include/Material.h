#ifndef MATERIAL_H
#define MATERIAL_H


#include <eigen3/Eigen/Dense>

struct Material {
    Material(const float r, const Eigen::Vector4f &a, const Eigen::Vector3f &color, const float spec) : refractive_index(r), albedo(a), diffuse_color(color), specular_exponent(spec) {}
    Material() : refractive_index(1), albedo(1,0,0,0), diffuse_color(), specular_exponent() {}
    float refractive_index;
    Eigen::Vector4f albedo;
    Eigen::Vector3f diffuse_color;
    float specular_exponent;
    float reflectance = 0.05;
};


#endif