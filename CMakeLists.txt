cmake_minimum_required(VERSION 3.17)

project(SMU_HostApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 强制查找 Charts 和 OpenGLWidgets
find_package(Qt6 6.10.1 REQUIRED COMPONENTS Widgets Charts OpenGLWidgets)

set(PROJECT_SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/pages/BasePage.h
    src/pages/DevicePage.cpp
    src/pages/DevicePage.h
    src/pages/ConfigPage.cpp
    src/pages/ConfigPage.h
    src/charts/RealtimeChartPlotter.cpp
    src/charts/RealtimeChartPlotter.h
    src/pages/DataPage.cpp
    src/pages/DataPage.h
    resources/resources.qrc
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# 显式链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Charts
    Qt6::OpenGLWidgets
)

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
