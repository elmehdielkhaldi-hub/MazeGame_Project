cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)



project(Project VERSION 1.0)

add_subdirectory(libs/raylib)

add_executable(Project rsc/main.cpp )
target_include_directories(Project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Project PRIVATE raylib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
