cmake_minimum_required(VERSION 3.16)

project(BusTimetable VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick QuickControls2 REQUIRED)

qt_add_executable(appBusTimetable
    src/main.cpp
    include/settings.h src/settings.cpp
    include/requesthandler.h src/requesthandler.cpp
    include/autocompletionhandler.h src/autocompletionhandler.cpp
    include/timetablehandler.h src/timetablehandler.cpp
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

target_include_directories(appBusTimetable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(appBusTimetable
    PRIVATE Qt6::Quick Qt6::QuickControls2)

install(TARGETS appBusTimetable
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
