

SET(PROJECT LEARN_GL)
project (${PROJECT})
set(TARGET_NAME main)

cmake_minimum_required(VERSION 3.10)

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md VERSION_FILE)
string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" VERSION_STRING "${VERSION_FILE}")
string(REGEX MATCHALL "[0-9]+" VERSION_PARTS "${VERSION_STRING}")
list(GET VERSION_PARTS 0 DEEPRCS_VERSION_MAJOR)
list(GET VERSION_PARTS 1 DEEPRCS_VERSION_MINOR)
list(GET VERSION_PARTS 2 DEEPRCS_VERSION_PATCH)
message("VERSION:${DEEPRCS_VERSION_MAJOR}.${DEEPRCS_VERSION_MINOR}.${DEEPRCS_VERSION_PATCH}")

SET(LIB /usr/local/lib)
link_directories(${LIB})
link_directories(${CMAKE_SOURCE_DIR}/libs/assimp)
link_directories(${CMAKE_SOURCE_DIR}/libs/glfw)
link_directories(${CMAKE_SOURCE_DIR}/libs/urdf)

# ----------------------------------------------------------------------------
# System architecture detection
# ----------------------------------------------------------------------------
set(SYSPROC "AMD64" CACHE STRING "AARCH64 ARM AMD64" )
if (${SYSPROC} STREQUAL "AARCH64")
    set(CC_PREFIX aarch64-linux-gnu-)
    set(CMAKE_SYSTEM_PROCESSOR aarch64)
elseif(${SYSPROC} STREQUAL "ARM")
    set(CC_PREFIX arm-linux-gnueabihf-)
    set(CMAKE_SYSTEM_PROCESSOR arm)
elseif(${SYSPROC} STREQUAL "AMD64")
    set(CC_PREFIX)
    set(CMAKE_SYSTEM_PROCESSOR amd64)  
else()
    message(FATAL_ERROR "Don't support this plateform!")
endif()

set(CMAKE_C_COMPILER ${CC_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${CC_PREFIX}g++)


# 添加编译选项
set(CMAKE_CXX_FLAGS "-g")

# 设置ulimit以允许生成core文件
# set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# set(CMAKE_INSTALL_RPATH "$ORIGIN")
# set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
# set(CMAKE_SKIP_BUILD_RPATH FALSE)
# set(CMAKE_BUILD_RPATH "$ORIGIN")
# set(CMAKE_INSTALL_PREFIX /usr/local)
# set(CMAKE_SKIP_RPATH FALSE)

# 设置core文件的名称和路径
# set(CMAKE_COREFILE_NAME core)
# set(CMAKE_COREFILE_PATH /var/core)
# ----------------------------------------------------------------------------
# export project name
# ----------------------------------------------------------------------------
add_definitions(-DPROJECT="${PROJECT}")
# ----------------------------------------------------------------------------
# enable test in this project
# ----------------------------------------------------------------------------
option(BUILD_TEST "enable test binary building" ON)

include_directories(.)
include_directories(src)
include_directories(glad)
include_directories(KHR)
include_directories(stb)
include_directories(glm)
include_directories(imgui)
aux_source_directory(${CMAKE_SOURCE_DIR}/imgui  imgui_cpp) 

set(compile_path src/shader03)

include_directories(${compile_path} )
aux_source_directory(${compile_path}  files)  


set(src_files  
    src/glad.c
    ${files}
    ${imgui_cpp})
add_executable(${TARGET_NAME} ${src_files})
target_link_libraries(${TARGET_NAME} GL glfw X11  pthread Xrandr Xi dl) 
