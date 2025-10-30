cmake_minimum_required(VERSION 3.10)
project(ChatBot VERSION 1.0 LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Incluir headers
include_directories(include)

# Buscar automáticamente todos los .cpp dentro de src/
file(GLOB_RECURSE SOURCES src/*.cpp)

# Crear el ejecutable ChatBot
add_executable(ChatBot ${SOURCES})

# Directorios de salida
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
