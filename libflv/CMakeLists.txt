cmake_minimum_required(VERSION 3.14)

project(flv C)


SET( SOURCES_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/source" )
SET( INCLUDE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include" )

FILE(GLOB_RECURSE files "${SOURCES_ROOT}/*.c" )
FILE(GLOB_RECURSE hfiles "${INCLUDE_ROOT}/*.c" )

add_library(${PROJECT_NAME} ${files})

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${INCLUDE_ROOT})