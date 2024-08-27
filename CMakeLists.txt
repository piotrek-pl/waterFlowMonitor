cmake_minimum_required(VERSION 3.16)

project(waterFlowMonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Znajdź pakiety Qt, w tym Qt SQL i Widgets
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Znajdź pliki MySQL (dostosuj ścieżki do rzeczywistego położenia)
find_path(MYSQL_INCLUDE_DIR NAMES mysql.h PATHS "C:/Program Files/MySQL/MySQL Server 8.0/include")
find_library(MYSQL_LIBRARY NAMES libmysql PATHS "C:/Program Files/MySQL/MySQL Server 8.0/lib")

# Sprawdź, czy znaleziono pliki MySQL
if(NOT MYSQL_INCLUDE_DIR OR NOT MYSQL_LIBRARY)
    message(FATAL_ERROR "Nie znaleziono plików MySQL. Upewnij się, że MySQL jest poprawnie zainstalowany.")
endif()

# Ustawienia preprocesora
include_directories(${MYSQL_INCLUDE_DIR})

# Ustawienia linker'a
link_directories(${MYSQL_LIBRARY})

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(waterFlowMonitor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(waterFlowMonitor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(waterFlowMonitor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Podlinkuj aplikację z bibliotekami Qt i MySQL
target_link_libraries(waterFlowMonitor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql ${MYSQL_LIBRARY})

# Ustawienia dla macOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.waterFlowMonitor)
endif()
set_target_properties(waterFlowMonitor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS waterFlowMonitor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(waterFlowMonitor)
endif()
