add_executable(example_fract fract.cpp)
target_link_libraries(example_fract PRIVATE decl)

add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox PRIVATE decl)

