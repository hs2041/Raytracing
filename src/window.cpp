#include "window.h"
#define convert_to_radian(in) \
    {                         \
        in * 3.141 / 180      \
    }
#define convert_to_degree(in) \
    {                         \
        in * 180 / 3.141      \
    }

Window::Window() : framebuffer(width * height), Background_color(0., 0., 0.)
{
    light_toggle = true;
    light_pos_x = 0;
    light_pos_y = 0;
    focus_dir = -camera.pose.normalized();
    z_dir = Eigen::Vector3f(0., 0., 1.);
    width = 1024;
    height = 768;
    current_width = width;
    current_height = height;
    camera_param1 = (tan(convert_to_radian(camera.fov_x / 2)) / ((float)width / 2)) * (focus_dir.cross(z_dir).normalized());
    camera_param2 = (tan(convert_to_radian(camera.fov_y / 2)) / ((float)height / 2)) * (((focus_dir.cross(z_dir).normalized()).cross(focus_dir)).normalized());

    casters.reserve(width);
    list_ob.reserve(12);
    pose_jump = 0.1;
    std::vector<float> signs{1, 1, -1, -1, 1};
    float d = 37.5;
    Tumbler tumbler[4];
    Tumbler_fluid fluid[4];
    //Direction lights specified
    for (int i = 0; i < 4; i++)
    {
        Dlight[i].direction = Eigen::Vector3f(signs.at(i) * d, signs.at(i + 1) * d, 75.).normalized();
        if (i < 2)
            Dlight[i].color = Eigen::Vector3f(255., 255., 100.);
        else
            Dlight[i].color = Eigen::Vector3f(0., 255., 255.);
    }

    d = 10.5;
    for (int i = 0; i < 4; i++)
    {
        //outer curved surface
        tumbler[i].material.refractive_index = 1.5;
        tumbler[i].outer_cylinder.radius = 3.;
        tumbler[i].outer_cylinder.height = 10.;
        tumbler[i].outer_cylinder.origin = Eigen::Vector3f(signs.at(i) * d, signs.at(i + 1) * d, 0.05);
        //inner curved surface
        tumbler[i].inner_cylinder = tumbler[i].outer_cylinder;
        tumbler[i].inner_cylinder.radius = 2.;
        //bottom surface
        tumbler[i].glass_bottom.inner_rad = 2;
        tumbler[i].glass_bottom.outer_rad = 3;
        tumbler[i].glass_bottom.origin = Eigen::Vector3f(signs.at(i) * d, signs.at(i + 1) * d, 0.05);
        // tumbler[i].glass_bottom.norm = 1;
        //top surface
        tumbler[i].glass_top = tumbler[i].glass_bottom;
        tumbler[i].glass_top.origin(2) = 10.05;

        //curved region
        fluid[i].fluid = tumbler[i].inner_cylinder;
        fluid[i].fluid.radius = 1.95;
        fluid[i].fluid.height = 5;
        //bottom surface
        fluid[i].fluid_bottom.inner_rad = 0.;
        fluid[i].fluid_bottom.outer_rad = 1.95;
        fluid[i].fluid_bottom.origin = Eigen::Vector3f(signs.at(i) * d, signs.at(i + 1) * d, 0.1);
        //top surface
        fluid[i].fluid_top = fluid[i].fluid_bottom;
        fluid[i].fluid_top.origin(2) = 5.05;
    }
    //transparent
    fluid[0].material.diffuse_color = Eigen::Vector3f(20, 20, 20);
    fluid[0].material.refractive_index = 1.5;
    //wine red
    fluid[1].material.diffuse_color = Eigen::Vector3f(114, 47, 55);
    fluid[1].material.refractive_index = 0.0;
    //bright orange
    fluid[2].material.diffuse_color = Eigen::Vector3f(255, 165, 20);
    fluid[2].material.refractive_index = 0.0;
    //lemon yellow
    fluid[3].material.diffuse_color = Eigen::Vector3f(255, 244, 79);
    fluid[3].material.refractive_index = 0.0;

    base = new Base();
    table = new Table();
    disk = new Disk();
    bowl = new Bowl();

    list_ob.push_back(base);
    list_ob.push_back(disk);
    list_ob.push_back(table);
    list_ob.push_back(bowl);

    for (int i = 0; i < 4; i++)
    {
        // tumbler_[i] = new Tumbler(tumbler[i]);
        // list_ob.push_back(tumbler_[i]);
        tumbler_fluid_[i] = new Tumbler_fluid(fluid[i]);
        list_ob.push_back(tumbler_fluid_[i]);
    }
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Window *windowManager =
        static_cast<Window *>(glfwGetWindowUserPointer(window));

    switch (key)
    {
    case GLFW_KEY_A:
    {
        std::cout << "a pressed\n";
        windowManager->areaL.pose(0) -= windowManager->pose_jump;
        break;
    }
    case GLFW_KEY_S:
    {
        std::cout << "s pressed\n";
        windowManager->areaL.pose(1) -= windowManager->pose_jump;
        break;
    }
    case GLFW_KEY_D:
    {
        std::cout << "d pressed\n";
        windowManager->areaL.pose(0) += windowManager->pose_jump;
        break;
    }
    case GLFW_KEY_W:
    {
        std::cout << "w pressed\n";
        windowManager->areaL.pose(1) += windowManager->pose_jump;
        break;
    }
    case GLFW_KEY_L:
    {
        windowManager->light_toggle = !(windowManager->light_toggle);
        windowManager->areaL.is_on = false;
        std::cout << "l pressed\n";
        break;
    }
    case GLFW_KEY_UP:
    {
        Eigen::Matrix3f turn;
        turn << 1, 0, 0, 0, cos(convert_to_radian(15.0)), sin(convert_to_radian(15.0)), 0, -sin(convert_to_radian(15.0)), cos(convert_to_radian(15.0));
        windowManager->camera.update_pose(Eigen::Matrix3f());

        std::cout << "up pressed\n";
        break;
    }
    case GLFW_KEY_RIGHT:
    {
        Eigen::Matrix3f turn;
        turn << cos(convert_to_radian(15.0)), -sin(convert_to_radian(15.0)), 0, sin(convert_to_radian(15.0)), cos(convert_to_radian(15.0)), 0, 0, 0, 1;
        windowManager->camera.update_pose(Eigen::Matrix3f());
        std::cout << "right pressed\n";
        break;
    }
    case GLFW_KEY_LEFT:
    {
        Eigen::Matrix3f turn;
        turn << cos(convert_to_radian(15.0)), sin(convert_to_radian(15.0)), 0, -sin(convert_to_radian(15.0)), cos(convert_to_radian(15.0)), 0, 0, 0, 1;
        windowManager->camera.update_pose(Eigen::Matrix3f());
        std::cout << "left pressed\n";
        break;
    }
    case GLFW_KEY_DOWN:
    {
        Eigen::Matrix3f turn;
        turn << 1, 0, 0, 0, cos(convert_to_radian(15.0)), -sin(convert_to_radian(15.0)), 0, sin(convert_to_radian(15.0)), cos(convert_to_radian(15.0));
        windowManager->camera.update_pose(Eigen::Matrix3f());

        std::cout << "down pressed\n";
        break;
    }
    default:
        break;
    }
}
int Window::is_window_made()
{
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    return 0;
}
int Window::system_check()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    return 0;
};
int Window::run()
{
    this->system_check();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    glfwSetErrorCallback(error_callback);

    bool coreProfile = true;
    if (coreProfile)
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    this->set_properties();
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ray Tracer", NULL, NULL);
    glfwGetFramebufferSize(window, &current_width, &current_height);
    // printf("Width = %d, Height = %d\n", current_width, current_height);

    // Open a window and create its OpenGL context
    this->is_window_made();
    glfwMakeContextCurrent(window);

    if (GLEW_OK != glewInit())
    {
        glfwTerminate();
        QUIT("gWindow_GLFW", "glewInit failed");
    }

    glfwSwapInterval(1);

    // width -= 5;
    opengl.init(width, height);

    glfwSetWindowUserPointer(window, this);
    // glfwSetUserPointer(window_, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    this->window_loop();

    return 0;
};

void Window::window_loop()
{
    do
    {
        const clock_t begin_time = clock();
        glfwGetFramebufferSize(window, &current_width, &current_height);
        printf("Width = %d, Height = %d\n", current_width, current_height);

        // glClear( GL_COLOR_BUFFER_BIT );
        glClearColor(0.5, 1, 1, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        ray_cast();
        std::cout << "window loop ending\n";
        opengl.draw(data, 1024, 768, 0, 0); // Display data (which has 640x480 pixels) Start at 0,0 in window.
        // Render OpenGL here

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
        std::cout << "Running time" << float(clock() - begin_time);
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);
    glfwTerminate();
}

void Window::ray_cast()
{
    Ray current;
    current.origin = camera.pose;

    for (int i = 0; i < height; i++)
    {
        casters.clear();
        for (int j = 0; j < width; j++)
        {
            current.direction = (focus_dir +
                                 (j - (width / 2)) * camera_param1 +
                                 (i - (height / 2)) * camera_param2)
                                    .normalized();
            // current.direction = current.direction.normalized();
            casters.push_back(std::thread(&Window::thread_handles, this, i, j, current));
        }
        for (std::thread &th : casters)
        {
            th.join();
        }
    }
}
void Window::thread_handles(int i, int j, Ray current)
{
    Eigen::Vector3f pix_color = this->find_intersection(current);
    for (int k = 0; k < 3; k++)
    {
        if (pix_color(k) >= 255.0)
            data[(i * width + j) * 3 + k] = 255.0;
        else if (pix_color(k) >= 255.0)
            data[(i * width + j) * 3 + k] = 0.0;
        else
            data[(i * width + j) * 3 + k] = (int)pix_color(k);
    }
}
Eigen::Vector3f Window::find_intersection(Ray &current, int rec_depth)
{
    // Object *cur;
    if (rec_depth >= 3)
        return Eigen::Vector3f(0., 0., 0.);

    int current_ob = -1;
    std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> result(Eigen::Vector3f(0., 0., 0.), false, 10000.0, Eigen::Vector3f(0., 0., 0.));
    std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> rets(Eigen::Vector3f(0., 0., 0.), false, 100000.0, Eigen::Vector3f(0., 0., 0.));
    for (int i = 0; i < list_ob.size(); i++)
    {
        std::get<1>(rets) = false;
        std::get<2>(rets) = 100000;
        list_ob.at(i)->is_intersecting(current, rets);
        if (std::get<1>(rets) == true)
        {
            if (std::get<2>(rets) <= std::get<2>(result))
            {
                result = rets;
                current_ob = i;
            }
        }
    }
    if (light_toggle == true)
        if (areaL.is_intersecting(current, std::get<2>(result)) == true)
        {
            return areaL.material.diffuse_color;
        }

    if (current_ob != -1)
    {

        Ray reflect_ray;
        reflect_ray.direction = reflect(current.direction, std::get<3>(result));
        reflect_ray.origin = std::get<0>(result) + 0.05 * reflect_ray.direction;
        //Material color + diffusion

        //shadows
        Eigen::Vector3f shadow_color(0.0, 0.0, 0.0);

        Eigen::Vector3f light_intensity(0., 0., 0.);

        for (int j = 0; j < 4; j++)
        {
            std::tuple<Eigen::Vector3f, bool, float, Eigen::Vector3f> rets(Eigen::Vector3f(0., 0., 0.), false, 100000.0, Eigen::Vector3f(0., 0., 0.));

            Ray shadow_ray;
            shadow_ray.origin = std::get<0>(result) + 0.01 * std::get<3>(result);
            shadow_ray.direction = Dlight[j].direction;
            bool is_light = false;

            if (shadow_ray.direction.dot(std::get<3>(result)) > 0)
                for (int i = 0; i < list_ob.size(); i++)
                {
                    list_ob.at(i)->is_intersecting(shadow_ray, rets);
                    if (std::get<1>(rets) == true)
                    {
                        is_light = true;
                        // shadow_color = shadow_color - Dlight[j].color/100.0;
                        break;
                    }
                }
            if (is_light == false)
                light_intensity += Dlight[j].color * ((Dlight[j].direction).dot(std::get<3>(result)));
        }

        bool is_area_light = false;
        float distance_to_area_light = (areaL.pose - (std::get<0>(rets))).norm();
        Ray area_ray;
        area_ray.origin = std::get<0>(result) + 0.01 * std::get<3>(result);
        area_ray.direction = (areaL.pose - area_ray.origin).normalized();
        std::get<1>(rets) = false;
        for (int i = 0; i < list_ob.size(); i++)
        {
            list_ob.at(i)->is_intersecting(area_ray, rets);
            if (std::get<1>(rets) == true && std::get<2>(rets) < distance_to_area_light)
            {
                is_area_light = true;
                // std::cout<<"found area light intersection \n";
                // shadow_color = shadow_color - Dlight[j].color/100.0;
                break;
            }
        }
        if (is_area_light == true && light_toggle == true)
        {
            light_intensity += (areaL.material.diffuse_color) * distance_to_area_light / 100.0;
        }

        //check distance from the area light
        //object color
        Eigen::Vector3f current_color = list_ob.at(current_ob)->material.diffuse_color;
        //light intensity added
        current_color += 0.04 * light_intensity;
        // current_color += shadow_color;
        //reflection added
        current_color += 0.05 * find_intersection(reflect_ray, rec_depth + 1);
        current_color += list_ob.at(current_ob)->material.reflectance * find_intersection(reflect_ray, rec_depth + 1);
        //shadow added
        // refraction added
        //refraction
        if (list_ob.at(current_ob)->material.refractive_index != 0.0)
        {
            Ray refract_ray;
            refract_ray.direction = refract(current.direction, std::get<3>(result), list_ob.at(current_ob)->material.refractive_index).normalized();
            refract_ray.origin = std::get<0>(result) + 0.05 * refract_ray.direction;
            current_color += 0.5 * find_intersection(refract_ray, rec_depth + 1);
        }
        // if(list_ob.at(current_ob)->material.refractive_index == 0.0)
        // return current_color;
        return current_color;
        // else
        // {

        // }
    }
    return Background_color;
}

Eigen::Vector3f Window::reflect(Eigen::Vector3f &dir, Eigen::Vector3f normal)
{
    return dir - 2 * (dir.dot(normal)) * normal;
}

Eigen::Vector3f Window::refract(Eigen::Vector3f &I, const Eigen::Vector3f &N, const float eta_t, const float eta_i)
{ // Snell's law
    float cosi = -std::max(-1.f, std::min(1.f, I.dot(N)));
    if (cosi < 0)
    {
        return refract(I, -N, eta_i, eta_t);
    } // if the ray comes from the inside the object, swap the air and the media
    float eta = eta_i / eta_t;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? reflect(I, N) : I * eta + N * (eta * cosi - sqrtf(k)); // k<0 = total reflection, no ray to refract. I refract it anyways, this has no physical meaning
}
