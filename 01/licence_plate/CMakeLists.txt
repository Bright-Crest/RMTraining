cmake_minimum_required(VERSION 3.16)

project(plate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp detector.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})