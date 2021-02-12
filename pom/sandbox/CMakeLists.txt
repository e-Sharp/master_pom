################################################################################

add_executable(pom_sandbox_maths)

target_sources(pom_sandbox_maths
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/maths.cpp
)

target_link_libraries(pom_sandbox_maths
PRIVATE
	pom_maths
)

################################################################################

add_executable(pom_sandbox_terrain)

target_sources(pom_sandbox_terrain
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/terrain.cpp
)

target_link_libraries(pom_sandbox_terrain
PRIVATE
	pom_maths
)
