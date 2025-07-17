cmake_minimum_required(VERSION 3.16)

project(WindowsVideoPlugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick)

qt_standard_project_setup()

qt_add_library(WindowsVideoPlugin STATIC
    windowsvideoplugin.cpp
    windowsvideoplugin.h
    windowsvideoitem.cpp
    windowsvideoitem.h
)

target_link_libraries(WindowsVideoPlugin PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
)

qt_add_qml_module(WindowsVideoPlugin
    URI "OpenHD.WindowsVideo"
    VERSION 1.0
    OUTPUT_TARGETS WindowsVideoPlugin_targets
)
