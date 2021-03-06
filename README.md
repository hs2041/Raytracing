
# Raytracing
Basic ray tracing is performed on a number of shapes such as cuboids, spheres and cylinders.
The algorithm takes into account reflection, refraction, shadows and light diffusion. 

It is a basic implementation which takes a lot of time to run but the code is quite simple to comprehend. You can also find some sample images attached. 

# Sample image
![Sample](https://github.com/hs2041/Raytracing/blob/main/Screenshot%202021-02-27%2022:11:49.png)
# System dependencies

I have compiled this code on Ubuntu 20.04 using cmake:

System dependencies:
1. Eigen
2. Glut
3. Eigen3
4. Boost

sudo apt-get install freeglut3*
sudo apt-get install libglfw3*

# Install

Use the following commands make and compile the code:
1. mkdir build && cd build
2. cmake ..
3. make
4. ./assign1

The output image is a bit slow, it takes about a minute to render on my laptop. Be patient.

Since the rendering part is taking a lot time, I am unable to use the keys to change the required camera and light positions (although they have been implemented)
In order to set the camera to a specific pose, you can change the camera position as per requirement in camera.h file line 17 (x, y and z coordinates respectively)

Note: Cook torrence has not been implemented
      The rays are getting trapped inside the tumblers making it impossible to visualise the fluid inside
