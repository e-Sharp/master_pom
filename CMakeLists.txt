cmake_minimum_required(VERSION 3.0)

project(pom)

if(MSVC)
    add_compile_options(/W4 /std:c++latest)
endif()

add_subdirectory(lib/catch2)

add_subdirectory(pom)
add_subdirectory(pom/maths)
