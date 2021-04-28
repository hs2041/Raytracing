# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Tutorials)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
# find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(Boost REQUIRED system)
find_package(GLEW REQUIRED)
include_directories(
	${EIGEN3_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	include/
	.
)

#Main boy
add_executable(assign1 
		src/main.cpp
		src/window.cpp
		src/Shapes.cpp
		src/Object.cpp
		# assignment1/window.cpp		
		# common/shader.cpp
		# common/shader.hpp	
		)		
target_link_libraries(assign1 glfw 
		${BOOST_LIBRARIES} 
		${OPENGL_LIBRARIES} 
		${GLEW_LIBRARIES}
		${GLUT_LIBRARY}
		)

add_executable(test 
		src/test1.cpp
		)		
target_link_libraries(assign1 glfw 
		${BOOST_LIBRARIES} 
		${OPENGL_LIBRARIES} 
		${GLEW_LIBRARIES}
		${GLUT_LIBRARY}
		)
