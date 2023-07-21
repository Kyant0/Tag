cmake_minimum_required(VERSION 3.22.1)

project(tag2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--exclude-libs,ALL")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flto")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdata-sections -ffunction-sections")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections")

add_subdirectory(taglib)

include_directories(
        ${taglib_SOURCE_DIR}/taglib
        ${taglib_SOURCE_DIR}/taglib/toolkit
        ${taglib_SOURCE_DIR}/taglib/asf
        ${taglib_SOURCE_DIR}/taglib/mpeg
        ${taglib_SOURCE_DIR}/taglib/ogg
        ${taglib_SOURCE_DIR}/taglib/ogg/flac
        ${taglib_SOURCE_DIR}/taglib/flac
        ${taglib_SOURCE_DIR}/taglib/mpc
        ${taglib_SOURCE_DIR}/taglib/mp4
        ${taglib_SOURCE_DIR}/taglib/ogg/vorbis
        ${taglib_SOURCE_DIR}/taglib/ogg/speex
        ${taglib_SOURCE_DIR}/taglib/ogg/opus
        ${taglib_SOURCE_DIR}/taglib/mpeg/id3v2
        ${taglib_SOURCE_DIR}/taglib/mpeg/id3v2/frames
        ${taglib_SOURCE_DIR}/taglib/mpeg/id3v1
        ${taglib_SOURCE_DIR}/taglib/ape
        ${taglib_SOURCE_DIR}/taglib/wavpack
        ${taglib_SOURCE_DIR}/taglib/trueaudio
        ${taglib_SOURCE_DIR}/taglib/riff
        ${taglib_SOURCE_DIR}/taglib/riff/aiff
        ${taglib_SOURCE_DIR}/taglib/riff/wav
        ${taglib_SOURCE_DIR}/taglib/mod
        ${taglib_SOURCE_DIR}/taglib/s3m
        ${taglib_SOURCE_DIR}/taglib/it
        ${taglib_SOURCE_DIR}/taglib/xm
        ${taglib_SOURCE_DIR}/taglib/dsf
        ${taglib_SOURCE_DIR}/taglib/dsdiff
)

add_library(${CMAKE_PROJECT_NAME} SHARED
        tag.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        tag)
