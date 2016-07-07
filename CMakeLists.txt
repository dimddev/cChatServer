cmake_minimum_required(VERSION 2.8.12)
project(cChatServer)

set (cChatServer_VERSION_MAJOR 0)
set (cChatServer_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code

configure_file (
    "${PROJECT_SOURCE_DIR}/cChatServerConfig.h.in"
    "${PROJECT_SOURCE_DIR}/cChatServerConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find cChatServerConfig.h
include_directories("${PROJECT_BINARY_DIR}")

include_directories (src)
add_subdirectory (src)

include_directories (src/Config)
add_subdirectory (src/Config)

include_directories (src/Socket)
add_subdirectory (src/Socket)

add_executable(cChatServer cChatServer.c)

target_link_libraries(cChatServer Config)

target_link_libraries(cChatServer cJSON)
target_link_libraries(cChatServer Socket)

find_library(M_LIB m)
target_link_libraries(cChatServer ${M_LIB})

find_library(PTHREAD_LIB pthread)
target_link_libraries(cChatServer ${PTHREAD_LIB})
