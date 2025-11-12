cmake_minimum_required(VERSION 4.0)
project(CPP04)

set(CMAKE_CXX_STANDARD 98)

include_directories(ex00 ex01)

add_executable(CPP04
        ex00/AAnimal.cpp
        ex00/AAnimal.hpp
        ex00/Cat.cpp
        ex00/Cat.hpp
        ex00/main.cpp
        ex00/Dog.cpp
        ex00/Dog.hpp
        ex00/WrongAnimal.cpp
        ex00/WrongAnimal.hpp
        ex00/WrongCat.cpp
        ex00/WrongCat.hpp
        ex01/main.cpp
        ex01/Brain.cpp
        ex01/Brain.hpp)
