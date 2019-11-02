cmake_minimum_required(VERSION 2.8)

project(mygl)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_BUILD_TYPE Release)

set (SOURCES main.cpp myglwidget.cpp myglwidget.h window.cpp window.h ui_window.h window.ui)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets opengl REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)


add_executable(mygl ${SOURCES})

target_link_libraries(mygl ${OPENGL_LIBRARIES} 
									/usr/local/Cellar/glfw/3.3/lib/libglfw.3.3.dylib 
									/usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.0.dylib 
									Qt5::Widgets Qt5::Core Qt5::Gui Qt5::OpenGL)
