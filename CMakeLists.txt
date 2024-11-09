cmake_minimum_required(VERSION 3.8)
project(duck_thread)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package (glog REQUIRED)

include_directories(./)

file(GLOB_RECURSE SOURCES "task/*.cpp" "thread/*.cpp")

add_executable(main ${SOURCES} main.cpp)
target_link_libraries (main glog::glog)

add_executable(safe_queue_test ${SOURCES} safe_queue_test.cpp)
target_link_libraries (safe_queue_test glog::glog)















