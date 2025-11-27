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
#qt creator usara esto para agrupar archivos por carpetas
file(GLOB_RECURSE SRC_FILES
${SRC_DIR}/*.cpp
)
file(GLOB_RECURSE HDR_FILES
${HDR_DIR}/*.h
${HDR_DIR}/database/*.inl
${HDR_DIR}/*.inl
${HDR_DIR}/database/*.h
${HDR_DIR}/ai/*.h
${HDR_DIR}/json/*.h
${HDR_DIR}/ai/*.inl
${HDR_DIR}/json/*.inl
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
target_include_directories(${PROJECT_NAME} PRIVATE ${HDR_DIR} ${HDR_DIR}/database ${HDR_DIR}/ai ${HDR_DIR}/json)
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
