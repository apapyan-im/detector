cmake_minimum_required(VERSION 3.12)
project(detector)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
#find_package(CUDA REQUIRED)
link_libraries(${OpenCV_LIBS})
include_directories(modules/capture/include modules/darknet/include ${OpenCV_INCLUDE})
add_subdirectory(modules/darknet)
add_executable(detector main.cpp
        modules/capture/VideoCapture.cpp
        modules/support/Support.cpp
)
target_link_libraries(detector dark)