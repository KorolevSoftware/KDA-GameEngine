cmake_minimum_required(VERSION 3.14)

project(Sprite
    VERSION 1.0.0
    DESCRIPTION "Graphics BGFX"
    LANGUAGES CXX)

SET(SOURCES
  kda_sprite.cpp
)
file(GLOB public_interface ${CMAKE_CURRENT_SOURCE_DIR}/public_interface/*.h)
source_group("Public interface" FILES ${public_interface})
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${KDA_HEADERS} ${public_interface}) # initialized below
add_library(KDA::sprite ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/engine/core_interface)

target_link_libraries(${PROJECT_NAME} KDA::scripts)