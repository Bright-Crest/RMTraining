cmake_minimum_required(VERSION 3.16)

project(kalman_filter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${Eigen3_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp kalman_filter.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})