# Version specification
cmake_minimum_required(VERSION 3.16)

# Project name
project(andersen
        DESCRIPTION "Andersen's pointer analysis"
        LANGUAGES CXX
)

# enable clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# LLVM setting
find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

# Target setting
add_subdirectory(lib)

add_executable(main_app main.cpp)
target_link_libraries(main_app PUBLIC Andersen ${LLVM_LIBS})