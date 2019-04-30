cmake_minimum_required (VERSION 3.5)
project(mpi_examples VERSION 1.0.0 LANGUAGES C CXX)

# Location of additional cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}/cmake
    )
include("PreventInTreeBuilds")
include("cs484common")
