add_executable(pom_sandbox_heightfield)

target_sources(pom_sandbox_heightfield
PRIVATE
	heightfield.cpp
)

target_link_libraries(pom_sandbox_heightfield
PRIVATE
	pom
)
