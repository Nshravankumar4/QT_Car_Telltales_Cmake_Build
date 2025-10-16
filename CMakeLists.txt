cmake_minimum_required(VERSION 3.16)
project(QtTelltaleProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Xml)

# Add UI search path so Qt AUTOUIC can find .ui files
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

# Define include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Add the main executable
add_executable(QtTelltaleProject
    src/main.cpp
    src/mainwindow.cpp
    inc/mainwindow.h
    ui/mainwindow.ui
)

target_link_libraries(QtTelltaleProject PRIVATE Qt5::Widgets Qt5::Xml)

# Copy resources
file(COPY xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
