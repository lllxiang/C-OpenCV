cmake_minimum_required(VERSION 2.8)
project(chap7)
#C++ 11
add_definitions(-std=c++11)
# add src dir
aux_source_directory(./src  dir_srcs)
add_executable(${PROJECT_NAME}  ${dir_srcs})
# find 3 packge

find_package(OpenCV REQUIRED) 

#include 
include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

#link_libraries
target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

#install 
install(TARGETS chap7 RUNTIME DESTINATION bin)
