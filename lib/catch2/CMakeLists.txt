add_library(catch2 INTERFACE)

target_sources(catch2
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp
)

target_include_directories(catch2
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
