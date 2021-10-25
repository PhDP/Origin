cmake_minimum_required(VERSION 3.2)
project(origin)

# Set build type to RELEASE by default:
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type provided, default to RELEASE.")
  set(CMAKE_BUILD_TYPE "RELEASE")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Threads REQUIRED)
find_package(GSL)
find_package(Math)

include_directories(. include ${GSL_INCLUDE_DIRS})

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(src)

