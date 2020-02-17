cmake_minimum_required(VERSION 3.16)
project(pixelator LANGUAGES CXX)

#export OpenCV_DIR=~/opencv/opencv-4.2.0/build
find_package(OpenCV REQUIRED)
add_executable(io source/io.cpp)
target_link_libraries(io ${OpenCV_LIBS})
add_executable(pixeling source/pixeling.cpp)
target_link_libraries(pixeling ${OpenCV_LIBS})
# find_package(MPI REQUIRED)
# find_package(OpenMP REQUIRED)
# find_package(Boost)
# find_package(gflags REQUIRED)
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