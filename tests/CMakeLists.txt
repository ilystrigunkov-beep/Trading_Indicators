cmake_minimum_required(VERSION 3.20)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(TradingIndicatorsTests LANGUAGES CXX)
endif()

get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

enable_testing()

if (NOT TARGET analysis)
    add_library(analysis
            ${PROJECT_ROOT}/src/analysis/SpikeDetector.cpp
            ${PROJECT_ROOT}/src/analysis/Statistics.cpp
    )

    target_include_directories(analysis
            PUBLIC
            ${PROJECT_ROOT}/include
    )
endif()

add_executable(analysis_tests
        analysis_tests.cpp
)

target_link_libraries(analysis_tests
        PRIVATE
        GTest::gtest_main
        analysis
)

include(GoogleTest)
gtest_discover_tests(analysis_tests)
