cmake_minimum_required(VERSION 3.14)
project(flv_remove_keyframe CXX C ASM)

ADD_SUBDIRECTORY(libflv libflv)

add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/flv_remove_keyframe.cpp")
target_link_libraries(${PROJECT_NAME} flv)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/libflv/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${ST_SOURCE_DIR} 
                           ${CMAKE_SOURCE_DIR}/3rdparty/libflv/include)


