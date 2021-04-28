#ifndef WINDOW_H
#define WINDOW_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
// Include GLEW
#include "GL/glew.h" 
#include <thread>

// Include GLFW
#include <math.h>
#include <algorithm>
#include <GLFW/glfw3.h>
#include <boost/bind.hpp>
#include "Camera.h"
#include "vector"
#include "Object.h"
#include "Ray.h"
#include "Lights.h"
#include "OpenglDraw.h"

// GLFWwindow* window;
#define RECURSION_DEPTH 4;
// Include GLM

// using namespace glm;


class Window{
    private:
        GLFWwindow* window;
        int current_width, current_height;
        int width, height;
        bool light_toggle;  
        int M,m;
        float light_pos_x;
        float light_pos_y;
        float pose_jump;
        std::vector<Eigen::Vector3f> framebuffer;
        OpenGLdraw opengl;
        GLubyte data[1024*768*3];
        GLubyte color = 255;

        // #objects
        Camera camera;
        Object* base;
        Object* table;
        Object* disk;
        Object* bowl;
        Object* tumbler_[4];
        Object* tumbler_fluid_[4];
        AreaLight areaL;

        DirectionLight Dlight[4];
        const Eigen::Vector3f Background_color;
        std::vector<Object*> list_ob;

        std::vector<std::thread> casters;

         
        Eigen::Vector3f focus_dir, camera_param1, camera_param2;
        Eigen::Vector3f z_dir;
        
    public:
        Window();

        static void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );

        int system_check();                         
        int is_window_made();

        void set_properties()
        {}
        void window_loop();
        void ray_cast();
        void thread_handles(int i, int j, Ray current);
        Eigen::Vector3f find_intersection(Ray&, int rec_depth = 0);
        Eigen::Vector3f reflect(Eigen::Vector3f&, Eigen::Vector3f normal);
        Eigen::Vector3f refract(Eigen::Vector3f &I, const Eigen::Vector3f &N, const float eta_t, const float eta_i=1.f);
        int run();
};

#endif