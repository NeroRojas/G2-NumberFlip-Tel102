cmake_minimum_required(VERSION 3.19)
project(NumberFlip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

qt_add_executable(NumberFlip
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    board.cpp
    board.h
    resources.qrc
)

target_link_libraries(NumberFlip
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
