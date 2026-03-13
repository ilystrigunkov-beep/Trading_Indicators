add_library(analysis
        ${CMAKE_CURRENT_SOURCE_DIR}/analysis/SpikeDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/analysis/Statistics.cpp
)
target_include_directories(analysis
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

