cmake_minimum_required(VERSION 3.14)
project(KDA-GameEngine CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

if(MSVC AND (MSVC_VERSION GREATER_EQUAL 1914))
    add_compile_options("/Zc:__cplusplus")
endif()

FetchContent_Declare(entt
 GIT_REPOSITORY "https://github.com/skypjack/entt"
 GIT_TAG "59abfbfb5a3b4d8dd589a0819cadb1f66e9fa9ae"
)

FetchContent_Declare(physfs
 GIT_REPOSITORY https://github.com/icculus/physfs
 GIT_TAG 957176bcf1db005e2528242636f644d9121013d5
)

FetchContent_MakeAvailable(entt physfs)

set(KDA_INCLUDES ${CMAKE_SOURCE_DIR}/engine/core_interface)

set(KDA_HEADERS
    ${KDA_INCLUDES}/kda_window.h
    ${KDA_INCLUDES}/kda_logging.h
    ${KDA_INCLUDES}/kda_graphics.h
    ${KDA_INCLUDES}/kda_scripts.h
)

set(my_list ddd)

function(append value)
    message(${value})
    list(APPEND my_list ${value})
    message(${my_list})
endfunction()

message(${my_list})

add_subdirectory(engine)
add_subdirectory(extensions)
message(${my_list})
set(SOURCES
  engine/engine.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${KDA_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${entt_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${KDA_INCLUDES}
    physfs-static
)

target_link_libraries(${PROJECT_NAME}
    PhysFS::PhysFS-static
    KDA::window
    KDA::logging
    KDA::graphics
    KDA::scripts
)