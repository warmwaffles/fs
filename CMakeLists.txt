cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(fs C)

set(SOURCES src/all/fs.c)

if (WIN32)
    LIST(APPEND SOURCES src/win/fs.c)
else()
    LIST(APPEND SOURCES src/posix/fs.c)
endif()

include_directories(include)

add_library(fs STATIC ${SOURCES})

target_include_directories(fs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

export(TARGETS fs FILE fs_config.cmake)
