cmake_minimum_required(VERSION 3.20)
project(walking_city)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(assimp REQUIRED)
find_package(glm REQUIRED)

add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

add_executable(walking_city
    src/main.cpp
)

target_include_directories(walking_city PRIVATE 
    include
)

target_link_libraries(walking_city
    glad
    glfw
    OpenGL::GL
    assimp::assimp
)
