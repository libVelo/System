message(STATUS "Build ${PROJECT_NAME} examples enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_example)

link_libraries(${PROJECT_NAME})

#

if(UNIX)
set(TARGET_NAME ${TARGET_NAME_HEAD}_stream_server)
add_executable(${TARGET_NAME} stream_server)
endif()

#

if(UNIX)
set(TARGET_NAME ${TARGET_NAME_HEAD}_stream_client)
add_executable(${TARGET_NAME} stream_client)
endif()

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_pair)
#add_executable(${TARGET_NAME} pair)
