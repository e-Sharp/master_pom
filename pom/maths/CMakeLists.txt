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
 "preset/default.hpp")

target_link_libraries(maths_sandbox
PRIVATE
    pom_maths
)

################################################################################

add_executable(pom_maths_tests)

target_sources(pom_maths_tests
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vector/tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp
 "preset/default.hpp")

target_link_libraries(pom_maths_tests
PRIVATE
    catch2
    pom_maths
)
