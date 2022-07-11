cmake_minimum_required(VERSION 3.18)
project(game-speak VERSION 0.1 LANGUAGES CXX)

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    qhotkey
    GIT_REPOSITORY https://github.com/Skycoder42/QHotkey.git
    GIT_TAG master
)

set(QHOTKEY_EXAMPLES OFF CACHE INTERNAL "")
set(QHOTKEY_INSTALL OFF CACHE INTERNAL "")

FetchContent_GetProperties(QHotkey)
if (NOT qhotkey_POPULATED)
    FetchContent_Populate(QHotkey)
    message(STATUS "QHotkey source dir: ${qhotkey_SOURCE_DIR}")
    message(STATUS "QHotkey binary dir: ${qhotkey_BINARY_DIR}")
    add_subdirectory(${qhotkey_SOURCE_DIR} ${qhotkey_BINARY_DIR})
endif ()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_DEFAULT_MAJOR_VERSION} COMPONENTS Widgets REQUIRED)
find_package(Qt5TextToSpeech)

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(TESSERACT REQUIRED tesseract)
pkg_search_module(LEPTONICA REQUIRED lept)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${TESSERACT_INCLUDE_DIRS})
include_directories(${LEPTONICA_INCLUDE_DIRS})

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/settingswindow.h
    src/settingswindow.cpp
    src/settingswindow.ui
    src/aboutwindow.cpp
    src/aboutwindow.h
    src/aboutwindow.ui
    include/asmOpenCV.h)

add_executable(game-speak
    ${PROJECT_SOURCES})

target_link_libraries(game-speak PRIVATE
    Qt::Widgets
    Qt::TextToSpeech
    ${OpenCV_LIBS}
    ${LEPTONICA_LIBRARIES}
    ${TESSERACT_LIBRARIES}
    QHotkey::QHotkey
    )

target_include_directories(game-speak PUBLIC ${qhotkey_SOURCE_DIR}/QHotkey)

include(GNUInstallDirs)
install(TARGETS game-speak DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${TESSDATA} DESTINATION ${CMAKE_INSTALL_BINDIR}/tessdata)
