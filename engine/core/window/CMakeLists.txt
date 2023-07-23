cmake_minimum_required(VERSION 3.14)

project(Window-SDL
	 	VERSION 1.0.0
	    DESCRIPTION "Window library"
	    LANGUAGES CXX)

FetchContent_Declare(sdl
 GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
 GIT_TAG "ac13ca9ab691e13e8eebe9684740ddcb0d716203"
)

FetchContent_MakeAvailable(sdl)

SET(SOURCES
  kda_window.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${KDA_HEADERS}) # initialized below
add_library(KDA::window ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/engine/core_interface)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)