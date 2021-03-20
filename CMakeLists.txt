cmake_minimum_required(VERSION 3.15)

project(pom)

if(MSVC)
    string(REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    add_compile_options(/std:c++latest /W4)
    message("${CMAKE_CXX_FLAGS}")
endif()

################################################################################
# Dependencies.

# Declarative cpp.

add_subdirectory(lib/declarative)

# Qt.

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Gui Widgets REQUIRED)

# Range v3.

add_subdirectory(lib/range_v3_0_11_0)

################################################################################

add_subdirectory(pom)
