add_library(pom_maths INTERFACE)

target_include_directories(pom_maths
INTERFACE
    ${CMAKE_SOURCE_DIR}/.
)

target_link_libraries(pom_maths
INTERFACE 
    decl
    range-v3
)
