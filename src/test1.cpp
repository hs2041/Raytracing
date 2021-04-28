#include <eigen3/Eigen/Dense>
#include <iostream>

int main()
{
    Eigen::Vector3f a(1,2,4);
    Eigen::Vector3f b(-2,2,-0.7);

    std::cout<<a.adjoint()*b;
}