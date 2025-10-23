cmake_minimun_required(VERSION 3.10)
project(chat-bot VERSION 1.0 LANGUAGES CXX)
#establecer el estandar de c++ 
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#carpetas headers para compilar
include_directories(include)

# Añadir el ejecutable a partir del código fuente
add_executable(chat-bot src/main.cpp)
