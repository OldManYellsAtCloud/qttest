cmake_minimum_required(VERSION 3.16)

project(BusTimetable VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick QuickControls2 WaylandCompositor REQUIRED)

qt_add_executable(appBusTimetable
    main.cpp
    settings.h settings.cpp
    requesthandler.h requesthandler.cpp
    autocompletionhandler.h autocompletionhandler.cpp
    timetablehandler.h timetablehandler.cpp
)

qt_add_qml_module(appBusTimetable
    URI BusTimetable
    VERSION 1.0
    QML_FILES main.qml
    QML_FILES AutoCompleteDelegate.qml
    QML_FILES Home.qml
    QML_FILES DepartureScreen.qml
    QML_FILES TimetableDelegate.qml
)

target_link_libraries(appBusTimetable
    PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::WaylandCompositor)

install(TARGETS appBusTimetable
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
