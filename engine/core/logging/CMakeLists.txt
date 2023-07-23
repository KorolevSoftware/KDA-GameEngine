cmake_minimum_required(VERSION 3.14)

project(Logging
	 	VERSION 1.0.0
	    DESCRIPTION "Window library"
	    LANGUAGES CXX)

FetchContent_Declare(spdlog
 GIT_REPOSITORY https://github.com/gabime/spdlog
 GIT_TAG "d1eb68154f2a60c7d59e99d1504e6c6ac03fedb4"
)

FetchContent_MakeAvailable(spdlog)

SET(SOURCES
  kda_logging.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${KDA_HEADERS}) # initialized below
add_library(KDA::logging ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
     ${spdlog_SOURCE_DIR}/include
     ${CMAKE_SOURCE_DIR}/engine/core_interface)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2)