cmake_minimum_required (VERSION 3.8)
project(tlm_test C CXX)

if(NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message(FATAL_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first, or setup Conan plugin if using CLion")
endif()

set(CONAN_CMAKE_SILENT_OUTPUT TRUE)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(NO_OUTPUT_DIRS TARGETS)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR} $(CONAN_CMAKE_MODULE_PATH))
find_package(SystemCLanguage REQUIRED)

add_subdirectory(src)