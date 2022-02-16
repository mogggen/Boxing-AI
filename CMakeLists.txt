cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

SET(files
    Point2D.h
    Point2D.cc

    Shape.h
    Shape.cc

    Rectangle.h
    Rectangle.cc

    Circle.h
    Circle.cc

    main.cc
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})



add_executable(SDL2Test ${files})
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})