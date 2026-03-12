add_library(analysis
        ${CMAKE_SOURCE_DIR}/src/analysis/SpikeDetector.cpp
        ${CMAKE_SOURCE_DIR}/src/analysis/Statistics.cpp)
target_include_directories(analysis
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include)