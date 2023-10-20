cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(serlcd-tester
  VERSION ${VERSION}
  LANGUAGES CXX C
  DESCRIPTION "SerLCD Tester"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(C_STANDARD_REQUIRED ON)

FILE(GLOB app_sources src/*.c src/*.cpp)
target_sources(app PRIVATE ${app_sources})

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR})
