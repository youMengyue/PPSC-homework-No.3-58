cmake_minimum_required(VERSION 3.15)
project(zhanhong_58_assignment)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect available parallel STL implementations
find_package(TBB QUIET)

# Add executable
add_executable(zhanhong_58_main src/main.cpp)

# Set compiler options based on platform
if(MSVC)
    target_compile_options(zhanhong_58_main PRIVATE /O2)
else()
    target_compile_options(zhanhong_58_main PRIVATE -O3)
    if(NOT APPLE)
        target_compile_options(zhanhong_58_main PRIVATE -march=native)
    endif()
endif()

# Add configurations for different build types
option(BUILD_PARALLEL "Build with parallel STL" ON)
option(BUILD_LINEAR "Build with linear version" ON)

if(BUILD_PARALLEL)
    target_compile_definitions(zhanhong_58_main PRIVATE PARALLEL_VERSION)
    message(STATUS "Building with parallel STL support")
endif()

if(BUILD_LINEAR)
    target_compile_definitions(zhanhong_58_main PRIVATE LINEAR_VERSION)
    message(STATUS "Building with linear version")
endif()

# Add TBB if found for better parallel performance
if(TBB_FOUND)
    target_link_libraries(zhanhong_58_main PRIVATE TBB::tbb)
    message(STATUS "TBB found - using for parallel execution")
endif()