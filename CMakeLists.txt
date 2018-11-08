message(STATUS "CMake version: ${CMAKE_VERSION}")
cmake_minimum_required(VERSION 2.8)

set(PROJECT base64codec)

project(${PROJECT})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Default build type to Debug" FORCE)
endif()

#-------------------------------------------------------------------------------

message("System:        ${CMAKE_SYSTEM_NAME}")
message("C compiller:   ${CMAKE_C_COMPILER}")
message("CXX compiller: ${CMAKE_CXX_COMPILER}")
message("Build type:    ${CMAKE_BUILD_TYPE}")

#-------------------------------------------------------------------------------

set(APP_DEFS "${APP_DEFS}")

if(MSVC)
    set(FLAGS_RELEASE "/O2 /MT")
    set(FLAGS_DEBUG   "/wd4996 /Od /Zi /MTd")
else()
    set(CXX_FLAGS "${APP_DEFS} -std=c++14 -static-libgcc -static-libstdc++" )
    set(CXX_FLAGS "${CXX_FLAGS} " )

    set(C_FLAGS "${APP_DEFS} -std=c99")
    set(C_FLAGS "${C_FLAGS} -fdata-sections -ffunction-sections")
    set(WARN_FLAGS "-Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code")

    set(FLAGS_RELEASE "-O2 -Wl,-s -Wl,--gc-section -Wl,--enable-stdcall-fixup")
    set(FLAGS_DEBUG   "-O0 -g -Wl,--enable-stdcall-fixup")
endif()

set(CMAKE_C_FLAGS_RELEASE    "${C_FLAGS} ${FLAGS_RELEASE} ${WARN_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG      "${C_FLAGS} ${FLAGS_DEBUG} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE  "${CXX_FLAGS} ${FLAGS_RELEASE} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG    "${CXX_FLAGS} ${FLAGS_DEBUG} ${WARN_FLAGS}")

#-------------------------------------------------------------------------------
if(NOT DEFINED LIB_DIR OR LIB_DIR STREQUAL "")
    string(REPLACE "\\" "/" LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()

add_subdirectory(src)
