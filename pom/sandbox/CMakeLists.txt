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

add_executable(pom_sandbox_declarative)

target_sources(pom_sandbox_declarative
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/declarative.cpp
)

target_link_libraries(pom_sandbox_declarative
PRIVATE
	pom_meta
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
	pom_io_qt
	pom_maths
)
