cmake_minimum_required(VERSION 3.16)
project(pixelator LANGUAGES CXX)

#include("~/vcpkg/scripts/buildsystems/vcpkg.cmake")
#set(CMAKE_TOOLCHAIN_FILE "~/vcpkg/scripts/buildsystems/vcpkg.cmake")

#export OpenCV_DIR=~/opencv/opencv-4.2.0/build
#set(protobuf_DIR "~/vcpkg/packages/protobuf_x64-linux/share/protobuf")
#set(gflags_DIR "~/vcpkg/packages/gflags_x64-linux/share/gflags")
#set(OpenCV_DIR "~/vcpkg/packages/opencv4_x64-linux/share/opencv")
#export OpenCV_DIR="~/vcpkg/packages/opencv4_x64-linux/share/opencv"
set(CMAKE_IGNORE_PATH "/mnt/c/Users/phili/anaconda3/Library")
#set(CMAKE_MODULE_PATH "~/vcpkg/installed/x64-linux/include")
set(CMAKE_PREFIX_PATH "~/vcpkg/installed/x64-linux/")
#set(OpenCV_DIR "~/vcpkg/packages/opencv4_x64-linux/share/opencv")
#set(TIFF_INCLUDE_DIR "~/home/philip/vcpkg/installed/x64-linux/include")
#set(TIFF_LIBRARY "~/home/philip/vcpkg/installed/x64-linux/lib/libtiff.a")

find_package(protobuf CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(gflags CONFIG REQUIRED)
#find_package(TIFF)
#find_package(quirc)

add_library(pixeling ${CMAKE_SOURCE_DIR}/source/pixeling.cpp)
target_link_libraries(pixeling ${OpenCV_LIBS})
add_executable(io ${CMAKE_SOURCE_DIR}/source/io.cpp)
target_link_libraries(io pixeling gflags)
# find_package(MPI REQUIRED)
# find_package(OpenMP REQUIRED)
# find_package(Boost)
#find_package(Catch2 QUIET)
#if (NOT Catch2_FOUND)
#  include(FetchContent)
#  FetchContent_Declare(
#	  catch2
#	  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#	  GIT_TAG        v2.11.0
 # )

#  FetchContent_MakeAvailable(catch2)
 # list(APPEND CMAKE_MODULE_PATH "catch2_SOURCE_DIR/contrib")
#endif()
#include(CTest)
#include(Catch)

# add_library, add_executable, add_subdirectory, target_link_library

#enable_testing()
#catch_discover_tests(tests)