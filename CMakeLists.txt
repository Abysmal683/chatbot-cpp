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
#set(QT_HOST_PATH "/usr/lib/qt6")
#set(ENV{PATH} "$ENV{PATH}:/usr/lib/qt6/bin")
# Habilita soporte para Qt (ajusta la versión que tengas instalada)
#find_package(QT NAMES Qt6 REQUIRED COMPONENTS
#Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Sql
    LinguistTools
)
#Paths o archivos
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(HDR_DIR ${CMAKE_SOURCE_DIR}/include)
set(UI_DIR ${CMAKE_SOURCE_DIR}/ui)
set(RES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(TS_DIR ${CMAKE_SOURCE_DIR}/translations)
#encontrar el Ui de autouic
set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${UI_DIR}
)
#archivos explicitamente incluidos
#set(SRC_FILES
#${SRC_DIR}/main.cpp
#${SRC_DIR}/mainwindow.cpp
#${SRC_DIR}/welcomewidget.cpp
#${SRC_DIR}/gamelibrarywidget.cpp
#${SRC_DIR}/chatwidget.cpp
#${SRC_DIR}/database/gamedatabase.cpp
#${SRC_DIR}/ai/aiengine.cpp
#${SRC_DIR}/ai/keyworddectector.cpp
#${SRC_DIR}/ai/tfindfclassifier.cpp
#${SRC_DIR}/ai/ruleengine.cpp
#${SRC_DIR}/ai/recomendationengine.cpp
#${SRC_DIR}/ai/intentclassifier.cpp
#)
#set(HDR_FILES
#${INCLUDE_DIR}/mainwindow.h
#${INCLUDE_DIR}/welcomewidget.h
#${INCLUDE_DIR}/gamelibrarywidget.h
#${INCLUDE_DIR}/chatwidget.h
#${INCLUDE_DIR}/database/gamedatabase.h
#${INCLUDE_DIR}/ai/aiengine.h
#${INCLUDE_DIR}/ai/keyworddectector.h
#${INCLUDE_DIR}/ai/tfindfclassifier.h
#${INCLUDE_DIR}/ai/ruleengine.h
#${INCLUDE_DIR}/ai/recomendationengine.h
#${INCLUDE_DIR}/ai/intentclassifier.h
#)
#set(UI_FILES
#${UI_DIR}/mainwindow.ui
#${UI_DIR}/welcomewidget.ui
#${UI_DIR}/gamelibrarywidget.ui
#${UI_DIR}/chatwidget.ui
#)
#set(RES_FILES
#${RES_DIR}/resources.qrc
#)
#set(TS_FILES
#${TS_DIR}/ChatBot_es_PA.ts)
# agregar recursos
#qt_add_resources(${SRC_FILES} ${RES_FILES})
#qt creator usara esto para agrupar archivos por carpetas
file(GLOB_RECURSE SRC_FILES
${SRC_DIR}/*.cpp
)
file(GLOB_RECURSE HDR_FILES
${HDR_DIR}/*.h
)
file(GLOB UI_FILES
${UI_DIR}/*.ui
)
file(GLOB RES_FILES
${RES_DIR}/*.qrc
)
file(GLOB TS_FILES
${TS_DIR}/*.ts
)
#source_group("Sources Files" FILES ${SRC_FILES})
#source_group("Includes Files" FILES ${HDR_FILES})
#source_group("UI Files" FILES ${UI_FILES})
#source_group("Resources Files" FILES ${RES_FILES})
#source_group("Translation Files" FILES ${TS_FILES})
# agrupar archivos por carpetas (Qt Creator)
source_group(TREE ${SRC_DIR} PREFIX "Sources Files" FILES ${SRC_FILES})
source_group(TREE ${HDR_DIR} PREFIX "Includes Files" FILES ${HDR_FILES})
source_group(TREE ${UI_DIR} PREFIX "UI Files" FILES ${UI_FILES})
source_group(TREE ${RES_DIR} PREFIX "Resources Files" FILES ${RES_FILES})
source_group(TREE ${TS_DIR} PREFIX "Translations Files" FILES ${TS_FILES})
#recursos
qt_add_resources(resources ${RES_FILES})

#target u objectivo principal
qt_add_executable(${PROJECT_NAME}
${SRC_FILES}
${HDR_FILES}
${UI_FILES}
${RES_FILES}
)
target_sources(${PROJECT_NAME} PRIVATE ${resources})
#carpeta include
target_include_directories(${PROJECT_NAME} PRIVATE ${HDR_DIR} ${HDR_DIR}/database ${HDR_DIR}/ai)
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
# traducciones
qt_add_translations(${PROJECT_NAME} TS_FILES ${TS_FILES} QM_FILES_OUTPUT_VARIABLE QM_FILES)
set(QM_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/translations)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${QM_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QM_FILES} ${QM_OUTPUT_DIR}
)
message(STATUS "QM files: ${QM_FILES}")
