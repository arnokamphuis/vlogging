# require minimum cmake version 2.8
cmake_minimum_required (VERSION 2.8)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# adding a project
project (vlogs-cache-performance)

add_executable(cache-basic ${PROJECT_SOURCE_DIR}/basic/main.cpp)
add_executable(cache-perform ${PROJECT_SOURCE_DIR}/performance/main.cpp)
