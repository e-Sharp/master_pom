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
