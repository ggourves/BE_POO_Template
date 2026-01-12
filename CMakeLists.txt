cmake_minimum_required(VERSION 4.0)
project(BE_POO_KTANE)

set(CMAKE_CXX_STANDARD 14)

include_directories(project_name)

add_executable(BE_POO_KTANE
        project_name/Application.cpp
        project_name/Application.h
        project_name/project_name.ino
        project_name/ModuleBase.cpp
        project_name/ModuleBase.hpp
        project_name/Bombe.cpp
        project_name/Bombe.hpp
        project_name/Arduino.h
        project_name/Thread.cpp
        project_name/Timer.cpp
        project_name/Timer.hpp
        project_name/Simon.h
        project_name/Simon.cpp
)
