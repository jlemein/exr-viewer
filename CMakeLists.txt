cmake_minimum_required(VERSION 3.15)

project(exr-viewer VERSION 0.1 LANGUAGES CXX)

execute_process(COMMAND conan install .. -s build_type=${CMAKE_BUILD_TYPE})
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the Qt6 path to the location where the library is installed.
if (NOT DEFINED QT6_SDK_PATH)
    message(FATAL_ERROR "Please specify a prefix path for QT6_SDK_PATH. Example:
            -DQT6_SDK_PATH="/home/jeffrey/Qt/6.2.1/gcc_64"")
endif()

list(APPEND CMAKE_PREFIX_PATH ${QT6_SDK_PATH})

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES exr-viewer_nl_NL.ts)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/openexrloader.h src/openexrloader.cpp
        src/openexrloader.h src/openexrloader.cpp
        src/exposurecontrol.h src/exposurecontrol.cpp
        ${TS_FILES}
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(exr-viewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET exr-viewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(exr-viewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(exr-viewer
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

find_package(fmt REQUIRED)
find_package(openexr REQUIRED)
target_link_libraries(exr-viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets openexr::openexr fmt::fmt)

target_compile_definitions(exr-viewer PUBLIC
#        -DTINYEXR_USE_ZFP=1
        )

set_target_properties(exr-viewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(exr-viewer)
endif()

add_executable(exrinfo exrinfo.cpp src/openexrloader.h src/openexrloader.cpp)
target_link_libraries(exrinfo PRIVATE openexr::openexr)

install(TARGETS exr-viewer
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)