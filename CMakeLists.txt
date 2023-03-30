cmake_minimum_required(VERSION 3.10)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.2)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

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