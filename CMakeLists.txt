cmake_minimum_required(VERSION 3.16)
project(ChatBot VERSION 0.1 LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#habilitar caracteristicas automaticas de qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# Arch Linux: Qt tools están en /usr/lib/qt6/bin
set(QT_HOST_PATH "/usr/lib/qt6")
set(ENV{PATH} "$ENV{PATH}:/usr/lib/qt6/bin")
# Habilita soporte para Qt (ajusta la versión que tengas instalada)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS
Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Sql
    LinguistTools
)
#Paths o archivos
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(UI_DIR ${CMAKE_SOURCE_DIR}/ui)
set(RES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(TS_DIR ${CMAKE_SOURCE_DIR}/translations)
#encontrar el Ui de autouic
set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${UI_DIR}
)
#qt creator usara esto para agrupar archivos por carpetas
source_group("Sources Files" FILES ${SRC_FILES})
source_group("Header Files" FILES ${HDR_FILES})
source_group("UI Files" FILES ${UI_FILES})
source_group("Resources Files" FILES ${RES_FILES})
#archivos explicitamente incluidos
set(SRC_FILES
${SRC_DIR}/main.cpp
${SRC_DIR}/mainwindow.cpp
${SRC_DIR}/welcomewidget.cpp
${SRC_DIR}/gamelibrarywidget.cpp
${SRC_DIR}/chatwidget.cpp
)
set(HDR_FILES
${INCLUDE_DIR}/mainwindow.h
${INCLUDE_DIR}/welcomewidget.h
${INCLUDE_DIR}/gamelibrarywidget.h
${INCLUDE_DIR}/chatwidget.h
)
set(UI_FILES
${UI_DIR}/mainwindow.ui
${UI_DIR}/welcomewidget.ui
${UI_DIR}/gamelibrarywidget.ui
${UI_DIR}/chatwidget.ui
)
set(RES_FILES
${RES_DIR}/resources.qrc
)
set(TS_FILES
${TS_DIR}/ChatBot_es_PA.ts)
#target u objectivo principal
qt_add_executable(${PROJECT_NAME}
${SRC_FILES}
${HDR_FILES}
${UI_FILES}
${RES_FILES}
)
# traducciones
##qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
qt_add_translations(${PROJECT_NAME} TS_FILES ${TS_FILES})
#carpeta include
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
#librerias del qt enlazadas
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
)
#salidas de directorios
set_target_properties(${PROJECT_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)


