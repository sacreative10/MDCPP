

CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(mdcppExample)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # works


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../ build)

# copy assets folder
file(GLOB_RECURSE ASSET_FILES "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
file(COPY ${ASSET_FILES} DESTINATION ${CMAKE_BINARY_DIR}/assets)

add_executable(mdcppExample main.cpp)
target_link_libraries(mdcppExample mdcpp)
