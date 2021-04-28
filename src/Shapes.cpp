#include <Shapes.h>

void Cuboid::find_distance(int i, float c, Ray in, std::tuple<Eigen::Vector3f, bool, float> &result)
{
    float param = (c-in.origin(i))/in.direction(i);
    if(param<0){
        //no intersection
        return;
    }
    else{
        float dir_1 = in.origin((i+1)%3)+param*in.direction((i+1)%3)-origin((i+1)%3);
        float dir_2 = in.origin((i+2)%3)+param*in.direction((i+2)%3)-origin((i+2)%3);
        
        if((dir_1 <= (sides[((i+1)%3)])/2)&&(dir_1 >= -(sides[((i+1)%3)])/2))
        {
            if((dir_2 <= (sides[((i+2)%3)])/2)&&(dir_2 >= -(sides[((i+2)%3)])/2))
            {
                // result = std::make_tuple(in.origin+param*in.direction,1,param);
                std::get<0>(result) = in.origin+param*in.direction;
                std::get<1>(result) = 1;
                std::get<2>(result) = param;
            }
        }
        //yes intersection
    }
    return;
}

void Cuboid::is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>& result)
{
    // float distance = -1.0;
    // bool is_collision = false;
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    std::tuple<Eigen::Vector3f, bool, float> rets(Eigen::Vector3f(0.,0.,0.),false,-1);
    Eigen::Vector3f normal(0.0,0.0,0.0);
    for(int i = 0;i<3;i++)
    {
        normal(i)=1.0;
        normal((i+1)%3) = 0.0;
        normal((i+2)%3) = 0.0;
        // float arr[3]={0.,0.,0.};
        if(pos.direction.adjoint()*normal != 0)
        {
            //check distance condition
            this->find_distance(i, origin(i)+(sides[i]/2), pos, rets);
            if(std::get<1>(rets) == true)
            {
                if(std::get<2>(rets) < std::get<2>(result))
                {
                    // result = std::make_tuple(std::get<0>(rets), std::get<1>(rets), std::get<2>(rets), normal);
                    std::get<0>(result) = std::get<0>(rets);
                    std::get<1>(result) = std::get<1>(rets);
                    std::get<2>(result) = std::get<2>(rets);
                    std::get<3>(result) = normal;
                }
            }
            this->find_distance(i, origin(i)-(sides[i]/2), pos, rets);
            if(std::get<1>(rets) == true)
            {
                if(std::get<2>(rets) < std::get<2>(result))
                {
                    // result = std::make_tuple(std::get<0>(rets), std::get<1>(rets), std::get<2>(rets), -normal);
                    std::get<0>(result) = std::get<0>(rets);
                    std::get<1>(result) = std::get<1>(rets);
                    std::get<2>(result) = std::get<2>(rets);
                    std::get<3>(result) = -normal;
                }
            }
        }
    }
    return;
        
}

void Circular_plane::is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>& result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    if(pos.direction.adjoint()*Eigen::Vector3f(0.,0.,1.) != 0)
    {
        float param = (origin(2)-pos.origin(2))/pos.direction(2);
        if(param >= 0)
        {
            float dist_temp = (origin-(pos.origin+param*pos.direction)).norm();
            if((dist_temp>= inner_rad) && (dist_temp<= outer_rad))
            {
                // result = std::make_tuple(pos.origin+param*pos.direction,1,param,Eigen::Vector3f(0.,0.,norm*1.));
                std::get<0>(result) = pos.origin+param*pos.direction;
                std::get<1>(result) = 1;
                std::get<2>(result) = param;
                std::get<3>(result) = Eigen::Vector3f(0.,0.,norm*1.);
            }
        }
    }
    return;  
}

void Hemisphere::is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>& result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));
    

    float a = pow(pos.direction(0),2)+pow(pos.direction(1),2)+pow(pos.direction(2),2);
    float b = 2*(pos.direction(0)*(pos.origin(0)-origin(0))+pos.direction(1)*(pos.origin(1)-origin(1))+pos.direction(2)*(pos.origin(2)-origin(2)));
    float c = pow(origin(0)-pos.origin(0),2)+pow(origin(1)-pos.origin(1),2)+pow(origin(2)-pos.origin(2),2)-radius*radius;

    float check = b*b-4*a*c;
    if (check>= 0)
    {
        float param[2];
        param[0] = (-b+sqrt(check))/(2*a);
        param[1] = (-b-sqrt(check))/(2*a);
        float current_height = (pos.origin(2)+param[0]*pos.direction(2))-origin(2);
        if(current_height<0)
        {
                Eigen::Vector3f inter =  pos.origin+param[0]*pos.direction;
            if(std::get<1>(result) != true || std::get<2>(result) > (pos.origin-inter).norm())
            {
                // result = std::make_tuple(inter,1, (pos.origin-inter).norm(),(inter-origin).normalized());
                std::get<0>(result) = inter;
                std::get<1>(result) = 1;
                std::get<2>(result) = (pos.origin-inter).norm();
                std::get<3>(result) = (inter-origin).normalized()*norm;
            }
        }
        current_height = (pos.origin(2)+param[1]*pos.direction(2))-origin(2);
        if(current_height<0)
        {
            Eigen::Vector3f inter =  pos.origin+param[1]*pos.direction;
            if(std::get<1>(result) != true || std::get<2>(result) > (pos.origin-inter).norm())
            {   
                // result = std::make_tuple(inter,1, (pos.origin-inter).norm(),(inter-origin).normalized());
                std::get<0>(result) = inter;
                std::get<1>(result) = 1;
                std::get<2>(result) = (pos.origin-inter).norm();
                std::get<3>(result) = (inter-origin).normalized()*norm;
            }
        }
    }

    return;
}

void Cylinder_curve::is_intersect(Ray &pos, std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f>& result)
{
    // std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0.,0.,0.),false,100000.0,Eigen::Vector3f(0.,0.,0.));

    float a = pow(pos.direction(0),2)+pow(pos.direction(1),2);
    float b = 2*(pos.direction(0)*(pos.origin(0)-origin(0))+pos.direction(1)*(pos.origin(1)-origin(1)));
    float c = pow(origin(0)-pos.origin(0),2)+pow(origin(1)-pos.origin(1),2)-radius*radius;

    float check = b*b-4*a*c;
    if (check>= 0)
    {

        float param[2];
        param[0] = (-b+sqrt(check))/(2*a);
        param[1] = (-b-sqrt(check))/(2*a);
        float current_height = (pos.origin(2)+param[0]*pos.direction(2));
        if(current_height<height && current_height>=0)
        {
            Eigen::Vector3f inter =  pos.origin+param[0]*pos.direction;
            // result = std::make_tuple(inter,1, (pos.origin-inter).norm(),Eigen::Vector3f(inter(0)-origin(0),inter(1)-origin(1),0.0).normalized());
            std::get<0>(result) = inter;
            std::get<1>(result) = 1;
            std::get<2>(result) = (pos.origin-inter).norm();
            std::get<3>(result) = normal*Eigen::Vector3f(inter(0)-origin(0),inter(1)-origin(1),0.0).normalized();
        }
        current_height = (pos.origin(2)+param[1]*pos.direction(2));
        if(current_height<height && current_height>=0)
        {
            Eigen::Vector3f inter =  pos.origin+param[1]*pos.direction;
            if(std::get<1>(result) != true || std::get<2>(result) > (pos.origin-inter).norm())
            {    
                // result = std::make_tuple(inter,1, (pos.origin-inter).norm(),Eigen::Vector3f(inter(0)-origin(0),inter(1)-origin(1),0.0).normalized());
                std::get<0>(result) = inter;
                std::get<1>(result) = 1;
                std::get<2>(result) = (pos.origin-inter).norm();
                std::get<3>(result) = normal*Eigen::Vector3f(inter(0)-origin(0),inter(1)-origin(1),0.0).normalized();
            }
        }
    }
    return;
}