# require minimum cmake version 2.8
cmake_minimum_required (VERSION 2.8)

enable_language(CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

# adding a project
project (vlogs-cache-performance)


include_directories(${PROJECT_SOURCE_DIR}/../../deps/benchmark/include ${PROJECT_SOURCE_DIR}/../../deps/benchmark/googletest/googletest/include ${PROJECT_SOURCE_DIR}/tools )
link_directories(${PROJECT_SOURCE_DIR}/../../deps/benchmark/build/src ${PROJECT_SOURCE_DIR}/../../deps/benchmark/googletest/build/googlemock/gtest)

add_executable(cache-basic ${PROJECT_SOURCE_DIR}/basic/main.cpp )
target_link_libraries (cache-basic LINK_PUBLIC benchmark shlwapi)

add_executable(cache-perform ${PROJECT_SOURCE_DIR}/performance/main.cpp)
target_link_libraries (cache-perform LINK_PUBLIC benchmark shlwapi)

add_executable(test-rnd ${PROJECT_SOURCE_DIR}/tests/test-rnd.cpp)
target_link_libraries (test-rnd LINK_PUBLIC gtest_main gtest)
