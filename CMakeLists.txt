cmake_minimum_required(VERSION 3.10)  # Corrección del typo
project(chat-bot VERSION 1.0 LANGUAGES CXX)

# Establecer el estándar de C++ a C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Carpetas de encabezados para compilar (incluir la carpeta 'include')
include_directories(include)

# Añadir el ejecutable a partir del código fuente (src/main.cpp)
add_executable(chat-bot src/main.cpp)
# Usar directorios específicos para el compilado y binarios
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
