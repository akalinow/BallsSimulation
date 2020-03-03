cmake_minimum_required(VERSION 3.0) # setting this is required
project(BallSimulation)             # this sets the project name
set(MODULE_NAME "BallSimulation")

set( CMAKE_VERBOSE_MAKEFILE off)
###############################################################################
###############################################################################
set(CMAKE_INSTALL_PREFIX "$ENV{PWD}") # install in the current directory
MESSAGE( STATUS "CMAKE_INSTALL_PREFIX:         " ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++14 -DWITHOUT_NUMPY -I/usr/include/python2.7/ -lpython2.7")

#Set RPATH to install dir, so user do not have to set the LD_LIBRARY_PATH
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)


###############################################################################
## file globbing ##############################################################
###############################################################################
# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variable
# `sources`
#
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cpp)

###############################################################################
## dependencies ###############################################################
###############################################################################
include_directories(${PROJECT_SOURCE_DIR}/include)

###############################################################################
## target definitions #########################################################
###############################################################################
add_library(${MODULE_NAME} SHARED ${sources})
add_executable(mySimulation bin/main.cpp)

# Compiler flags.
#
target_compile_options(${MODULE_NAME} PUBLIC)
target_compile_options(mySimulation PUBLIC)
target_link_libraries(mySimulation PUBLIC ${MODULE_NAME})

# All install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS ${MODULE_NAME} LIBRARY DESTINATION lib)
install(TARGETS mySimulation RUNTIME DESTINATION bin)
