cmake_minimum_required(VERSION 3.15)

project(pom)

if(MSVC)
    string(REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    add_compile_options(/std:c++latest /W4 /O2)
    message("${CMAKE_CXX_FLAGS}")
endif()

add_subdirectory(lib)

add_subdirectory(pom)
