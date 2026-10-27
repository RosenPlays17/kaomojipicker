cmake_minimum_required(VERSION 4.4)
project(kaomojipicker)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(kaomojipicker main.cpp
        MainWindow.cpp
        MainWindow.h
)
target_link_libraries(kaomojipicker
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

