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

file(GLOB public_interface ${CMAKE_CURRENT_SOURCE_DIR}/public_interface/*.h)
# file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/public_interface/*.h)
message(${public_interface})
set(SOURCES
	kda_scripts.cpp
)



source_group("Public interface" FILES ${public_interface})

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${public_interface}) # initialized below

target_include_directories(${PROJECT_NAME} PRIVATE ${KDA_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public_interface)
target_link_libraries(${PROJECT_NAME} lua::lib lua::header sol2::sol2)

add_library(KDA::scripts ALIAS ${PROJECT_NAME})

