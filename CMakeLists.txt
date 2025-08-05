
CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
project(mdcpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # works


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# GLFW
add_subdirectory(external/glfw)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

# glm
add_subdirectory(external/glm)

# spdlog
add_subdirectory(external/spdlog)

#stb_image
include_directories(external/stb_image)



# shaders
set(SHADER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders)
set(SHADER_OUTPUT_DIR ${CMAKE_BINARY_DIR}/shaders)

# copy shaders
file(COPY ${SHADER_SRC_DIR} DESTINATION ${SHADER_OUTPUT_DIR})

add_library(mdcpp SHARED external/glad/src/glad.c
        include/mdcpp/input/input.h
        include/mdcpp/input/keycodes.h
        include/mdcpp/utils/definitions.h)
add_subdirectory(src)

target_include_directories(mdcpp PUBLIC include/)
target_include_directories(mdcpp PUBLIC external/glad/include)
target_link_libraries(mdcpp glfw glm spdlog::spdlog)

# make compile_commands.json


