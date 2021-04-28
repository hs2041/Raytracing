#include "Object.h"


Base::Base()
{
    floor.origin = Eigen::Vector3f(0.0,0.0,-77.1);
    floor.sides[0] = 100;
    floor.sides[1] = 100;
    floor.sides[2] = 2;
    material.diffuse_color = Eigen::Vector3f(100.,100.,100.);
    material.refractive_index = 0.0;
    material.reflectance = 0.2;
    // floor.origin = Eigen::Vector3f(0.0,0.0,0.0);
    // floor.sides[0] = 10;
    // floor.sides[1] = 10;
    // floor.sides[2] = 10;
}


void Base::is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),true,100.0,Eigen::Vector3f(0.,0.,0.));
    // return result;
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> rets(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));

    floor.is_intersect(input,result);
    // return;
}

Table::Table()
{
    table_top.origin = Eigen::Vector3f(0.,0.,-0.5);
    table_top.sides[0] = 75.0;
    table_top.sides[1] = 75.0;
    table_top.sides[2] = 1.0;
    legs[0].origin = Eigen::Vector3f(36.5,36.5,-38.5);
    legs[1].origin = Eigen::Vector3f(36.5,-36.5,-38.5);
    legs[2].origin = Eigen::Vector3f(-36.5,-36.5,-38.5);
    legs[3].origin = Eigen::Vector3f(-36.5,36.5,-38.5);
    for(int i=0;i<4;i++)
    {
        legs[i].sides[0] = 2;
        legs[i].sides[1] = 2;
        legs[i].sides[2] = 75;
    }
    material.diffuse_color = Eigen::Vector3f(114.,50.,18.);
    material.refractive_index = 1.5;
    material.reflectance = 0.1;
}
void Table::is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> rets(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));

    table_top.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
        result = rets;
    for(int i=0;i<4;i++)
    {
        legs[i].is_intersect(input,rets);
        if(std::get<1>(rets)==true)
        {   
            if(std::get<2>(rets) <= std::get<2>(result))
            result = rets;
        }
    }

    return;
}

Disk::Disk()
{
    cylinder.height = 1;
    cylinder.radius = 10;
    cylinder.origin = Eigen::Vector3f(0.,0.,0.05);
    top.inner_rad = 0.0;
    top.outer_rad = 10.0;
    top.origin = Eigen::Vector3f(0.,0.,1.);
    
    bottom.inner_rad = 0.0;
    bottom.outer_rad = 10.0;
    bottom.origin = Eigen::Vector3f(0.,0.,0.);
    bottom.norm = -1;
    material.diffuse_color = Eigen::Vector3f(175.,175.,175.);
    material.refractive_index = 0.0;
    material.reflectance = 0.3;
}
void Disk::is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> rets(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));

    cylinder.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    top.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    bottom.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    return;
}

Bowl::Bowl()
{
    outer_hemi.radius = 5;
    outer_hemi.normal = Eigen::Vector3f(0.,0.,1.);
    outer_hemi.origin = Eigen::Vector3f(0.,0.,6.1);
    inner_hemi.radius = 4;
    inner_hemi.normal = Eigen::Vector3f(0.,0.,1.);
    inner_hemi.origin = Eigen::Vector3f(0.,0.,6.1);
    inner_hemi.norm = -1.0;

    top.inner_rad = 4;
    top.outer_rad = 5;
    top.origin = outer_hemi.origin; 
    material.diffuse_color = Eigen::Vector3f(220.,203.,93.);
    material.refractive_index = 0.0;
    material.reflectance = 0.4;
}

void Bowl::is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> rets(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));

    outer_hemi.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    inner_hemi.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
         result = rets;
    }
    top.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
         result = rets;
    }

    return;
}

Tumbler::Tumbler()
{
    glass_bottom.norm = -1;   
    material.diffuse_color = Eigen::Vector3f(50.,50.,50.);
    material.refractive_index = 1.52;
    material.reflectance = 0.5;
    outer_cylinder.normal = 1.0;
    inner_cylinder.normal = -1.0;
}
void Tumbler::is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> rets(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));

    outer_cylinder.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    inner_cylinder.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    glass_top.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    glass_bottom.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    return;
}

Tumbler_fluid::Tumbler_fluid()
{
    fluid_bottom.norm = -1;
    material.diffuse_color = Eigen::Vector3f(10.,10.,10.);
    material.refractive_index = 0.00;
    material.reflectance = 0.01;
}
void Tumbler_fluid::is_intersecting(Ray input, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> &result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> rets(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    fluid.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    fluid_top.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }
    fluid_bottom.is_intersect(input,rets);
    if(std::get<1>(rets)==true)
    {   
        if(std::get<2>(rets) <= std::get<2>(result))
        result = rets;
    }

    return;
}
