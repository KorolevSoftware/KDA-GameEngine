cmake_minimum_required(VERSION 3.14)

project(Lua
	VERSION 5.4.6
	DESCRIPTION "Lua"
	LANGUAGES CXX
)

FetchContent_Declare(lua
	GIT_REPOSITORY https://github.com/lua/lua
	GIT_TAG "ea39042e13645f63713425c05cc9ee4cfdcf0a40"
)

FetchContent_MakeAvailable(lua)

File(GLOB SOURCES ${lua_SOURCE_DIR}/*.c)
 # Remove main point not need from lib
list(REMOVE_ITEM SOURCES ${lua_SOURCE_DIR}/lua.c ${lua_SOURCE_DIR}/onelua.c)

#libraty
add_library(${PROJECT_NAME} STATIC ${SOURCES}) # initialized below
add_library(lua::lib ALIAS ${PROJECT_NAME})

# Include dir
add_library(lua-header INTERFACE)
target_include_directories(lua-header INTERFACE ${lua_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} INTERFACE lua-header)
add_library(lua::header ALIAS lua-header)