cmake_minimum_required(VERSION 3.15)

project(pom)

if(MSVC)
    add_compile_options(/std:c++latest)
    # Removes warning D9025.
    string(REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

add_subdirectory(lib/catch2)

add_subdirectory(pom)
add_subdirectory(pom/maths)
