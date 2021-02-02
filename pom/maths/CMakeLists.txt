add_library(pom_maths INTERFACE)

target_include_directories(pom_maths
INTERFACE
    ${CMAKE_SOURCE_DIR}/.
)

################################################################################

add_executable(maths_sandbox)

target_sources(maths_sandbox
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sandbox.cpp
 )

target_link_libraries(maths_sandbox
PRIVATE
    pom_maths
)
