cmake_minimum_required(VERSION 2.4)
project(xlWin32APIHelper)
if(${CMAKE_COMPILER_IS_GNUCXX})
  set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Wfatal-errors")
endif()

file(GLOB SRC_LIST *.h)
add_custom_target(xlWin32APIHelper SOURCES ${SRC_LIST})

file(GLOB SRC_LIST "UnitTest/*.cpp")
add_executable(UnitTest ${SRC_LIST})
add_dependencies(UnitTest xlWin32APIHelper)
