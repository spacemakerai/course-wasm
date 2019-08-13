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

add_executable(height_optimize
        src/solver/main.cpp
        src/solver/geometry.h
        src/solver/geometry.cpp
        src/solver/cost.h
        src/solver/cost.cpp
        src/solver/optimize.h
        src/solver/optimize.cpp
        src/solver/solutionCandidate.h
        src/solver/solutionCandidate.cpp
        src/solver/feasibilityChecker.cpp
        src/solver/feasibilityChecker.h
        )





