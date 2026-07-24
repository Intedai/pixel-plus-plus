cmake_minimum_required(VERSION 3.16)

project(Pixel++ VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(Pixel++
    resources/resources.qrc
    src/main.cpp
    src/MainWindow.cpp
    include/MainWindow.hpp
    src/ColorButtons.cpp
    include/ColorButtons.hpp
    src/ColorWheel.cpp
    include/ColorWheel.hpp
    src/ColorSelector.cpp
    include/ColorSelector.hpp
    src/Document.cpp
    include/Document.hpp
    src/CanvasView.cpp
    include/CanvasView.hpp
)

target_include_directories(Pixel++ PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Pixel++ PRIVATE Qt6::Widgets)

set_target_properties(Pixel++ PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
