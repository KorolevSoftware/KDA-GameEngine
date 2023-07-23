cmake_minimum_required(VERSION 3.14)

project(Scripts-Lua
	VERSION 1.0.0
	DESCRIPTION "Lua scripts engine"
	LANGUAGES CXX
)

add_subdirectory(lua)

FetchContent_Declare(sol2
	GIT_REPOSITORY https://github.com/ThePhD/sol2
	GIT_TAG "dca62a0f02bb45f3de296de3ce00b1275eb34c25"
)

FetchContent_MakeAvailable(sol2)

set(SOURCES
	kda_scripts.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES}) # initialized below
add_library(KDA::scripts ALIAS ${PROJECT_NAME})
message("${LUABRIDGE_HEADERS}")
target_include_directories(${PROJECT_NAME} PRIVATE ${KDA_INCLUDES})
 
target_link_libraries(${PROJECT_NAME} lua::lib lua::header sol2::sol2)