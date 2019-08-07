cmake_minimum_required(VERSION 3.9)
project(Optimize)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/)
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


set(SOURCE src/main.cpp)

add_executable(height_optimize src/main.cpp src/optimizationSolver/geometry.h src/optimizationSolver/geometry.cpp src/optimizationSolver/cost.h src/optimizationSolver/cost.cpp src/optimizationSolver/optimize.h src/optimizationSolver/optimize.cpp src/optimizationSolver/solutionCandidate.h src/optimizationSolver/solutionCandidate.cpp src/optimizationSolver/feasibilityChecker.cpp src/optimizationSolver/feasibilityChecker.h)





