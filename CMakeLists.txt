# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Project name, version, and programming language
project(QtTelltaleProject VERSION 1.0 LANGUAGES CXX)

# Enable automatic handling of Qt features:
# - AUTOMOC: Automatically run the Meta-Object Compiler on header files
# - AUTOUIC: Automatically process .ui files
# - AUTORCC: Automatically process .qrc resource files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find the required Qt5 packages
# Qt5::Widgets -> For GUI widgets (QMainWindow, QLabel, etc.)
# Qt5::Xml     -> For XML parsing (QDomDocument, QDomElement)
find_package(Qt5 REQUIRED COMPONENTS Widgets Xml)

# Add the main executable for the project
# List all source files and headers used in compilation
add_executable(QtTelltaleProject
    main.cpp         # Main entry point of application
    mainwindow.cpp   # Implementation of MainWindow class
    mainwindow.h     # Header file for MainWindow class
    mainwindow.ui    # Qt Designer UI file for MainWindow
)

# Link Qt libraries to the executable
target_link_libraries(QtTelltaleProject PRIVATE Qt5::Widgets Qt5::Xml)

# Copy external folders (XML and images) to the build directory
# Ensures that the application can find these files when running
file(COPY xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
