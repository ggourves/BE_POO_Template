cmake_minimum_required(VERSION 4.0)
project(BE_POO_KTANE)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project_KTANE)

add_executable(BE_POO_KTANE
        Project_KTANE/Application.cpp
        Project_KTANE/Application.h
        Project_KTANE/Project_KTANE.ino
        Project_KTANE/ModuleBase.cpp
        Project_KTANE/ModuleBase.hpp
        Project_KTANE/Bombe.cpp
        Project_KTANE/Bombe.hpp
        Project_KTANE/Thread.cpp
        Project_KTANE/Timer.cpp
        Project_KTANE/Timer.hpp
        Project_KTANE/Speaker.cpp
        Project_KTANE/Speaker.hpp
        Project_KTANE/Simon.cpp
        Project_KTANE/Simon.cpp
        Project_KTANE/Password.hpp
        Project_KTANE/Password.cpp
        Project_KTANE/Simon.cpp
)
