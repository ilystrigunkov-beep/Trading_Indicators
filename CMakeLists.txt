cmake_minimum_required(VERSION 3.31)
project(Trading_Indicators)

set(CMAKE_CXX_STANDARD 23)

add_executable(Trading_Indicators main.cpp
        include/analysis/Analyzer.h
        include/analysis/SpikeDetector.h
        src/analysis/SpikeDetector.cpp
        include/analysis/Statistics.h
        src/analysis/Statistics.cpp
)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
