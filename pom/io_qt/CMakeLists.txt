add_library(pom_io_qt INTERFACE)

target_include_directories(pom_io_qt
INTERFACE
    ${CMAKE_SOURCE_DIR}/.
)

target_link_libraries(pom_io_qt
INTERFACE
	Qt5::Widgets
)
