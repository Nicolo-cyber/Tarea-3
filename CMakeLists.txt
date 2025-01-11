cmake_minimum_required(VERSION 3.16)
project(camino_corto_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    graph.cpp
    graph.h
)

add_executable(camino_corto_qt ${PROJECT_SOURCES})
target_link_libraries(camino_corto_qt PRIVATE Qt5::Widgets)
