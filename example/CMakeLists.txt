

CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(mdcppExample)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # works


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../ build)

add_executable(mdcppExample main.cpp)
target_link_libraries(mdcppExample mdcpp)
