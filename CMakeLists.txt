cmake_minimum_required(VERSION 3.8)

project(File2Stream)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(BOOST_ROOT "/usr/")
find_package(Boost REQUIRED COMPONENTS system program_options)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost library not found, please install or indicate the directory.")
endif()

include_directories(${Boost_INCLUDE_DIRS})
include_directories(include)

add_executable(file2stream src/main.cpp)
target_link_libraries(file2stream ${Boost_LIBRARIES})