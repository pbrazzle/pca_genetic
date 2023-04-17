cmake_minimum_required(VERSION 3.10)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.2)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(ExternalProject)

if(WIN32)
  set(JPEG_LIBNAME ${CMAKE_BINARY_DIR}/bin/jpeg-static.lib)
else(WIN32)
  set(JPEG_LIBNAME ${CMAKE_BINARY_DIR}/bin/libjpeg.a)
endif(WIN32)

ExternalProject_Add(libjpeg-turbo
        CMAKE_ARGS
        -DENABLE_SHARED=OFF
        -DENABLE_STATIC=ON
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/libjpeg-turbo
        -DCMAKE_INSTALL_LIBDIR=${CMAKE_BINARY_DIR}/bin
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
  		GIT_REPOSITORY https://github.com/libjpeg-turbo/libjpeg-turbo.git
  		GIT_TAG        2.1.91
        BUILD_BYPRODUCTS ${JPEG_LIBNAME})

project(pca_genetic)
include(CTest)
include(Catch)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/lib)
enable_testing()

function(create_test)
	add_executable(${ARGV} ${ARGV})
	add_test(NAME ${ARGV}
			 COMMAND $<TARGET_FILE:${ARGV}>)
endfunction(create_test)

add_subdirectory(src)