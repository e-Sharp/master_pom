################################################################################

add_executable(pom_sandbox_coloration)

target_sources(pom_sandbox_coloration
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/coloration.cpp
)

target_link_libraries(pom_sandbox_coloration
PRIVATE
	pom_io_qt
	pom_maths
)

################################################################################

add_executable(pom_sandbox_erosion)

target_sources(pom_sandbox_erosion
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/erosion.cpp
)

target_link_libraries(pom_sandbox_erosion
PRIVATE
	pom_io_qt
	pom_maths
)

################################################################################

add_executable(pom_sandbox_gradients)

target_sources(pom_sandbox_gradients
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/gradients.cpp
)

target_link_libraries(pom_sandbox_gradients
PRIVATE
	pom_io_qt
	pom_maths
)

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
	pom_io_qt
	pom_maths
)

################################################################################

add_executable(pom_sandbox_texture)

target_sources(pom_sandbox_texture
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
)

target_link_libraries(pom_sandbox_texture
PRIVATE
	pom_io_qt
)
