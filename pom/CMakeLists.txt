################################################################################

add_library(pom INTERFACE)

target_include_directories(pom
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

################################################################################

add_executable(pom_sandbox)

target_sources(pom_sandbox
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sandbox.cpp
)

target_link_libraries(pom_sandbox
PRIVATE
    pom
)

add_executable(sandbox_qt)

target_sources(sandbox_qt
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sandbox_qt.cpp
)

target_link_libraries(sandbox_qt
PRIVATE
    pom
)
