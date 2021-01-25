set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# Default

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt_test
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(qt_test SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(qt_test
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(qt_test PRIVATE  Qt${QT_VERSION_MAJOR}::Widgets)

add_library(qt INTERFACE)

target_link_libraries(qt
    INTERFACE
        Qt${QT_VERSION_MAJOR}::Gui
)
