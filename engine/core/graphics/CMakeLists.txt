cmake_minimum_required(VERSION 3.14)

project(Graphics
    VERSION 1.0.0
    DESCRIPTION "Graphics BGFX"
    LANGUAGES CXX)

FetchContent_Declare(bgfx
 GIT_REPOSITORY "https://github.com/KorolevSoftware/bgfx.cmake"
 GIT_TAG "61c15802c37bcb31db28e353bba97efab360c7c8"
)

FetchContent_MakeAvailable(bgfx)

SET(SOURCES
  kda_graphics.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${KDA_HEADERS}) # initialized below
add_library(KDA::graphics ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/engine/core_interface
  ${bgfx_SOURCE_DIR}/bgfx/examples/common
  ${bgfx_SOURCE_DIR}/bx/include
  ${bgfx_SOURCE_DIR}/bimg/include)

target_link_libraries(${PROJECT_NAME} bgfx)