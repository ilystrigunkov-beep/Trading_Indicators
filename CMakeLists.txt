cmake_minimum_required(VERSION 3.31)
project(Trading_Indicators)

set(CMAKE_CXX_STANDARD 23)

include(CTest)

add_subdirectory(src)
add_executable(Trading_Indicators main.cpp)
target_link_libraries(Trading_Indicators
        PRIVATE
        analysis
)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
add_executable(Trading_Indicators main.cpp
        src/core/CsvLoader.cpp
        include/core/CsvLoader.h
        src/core/Exceptions.cpp
        include/core/Exceptions.h
        src/core/Candle.cpp
        include/core/Candle.h
        src/core/TimeSeries.cpp
        include/core/TimeSeries.h)
