cmake_minimum_required(VERSION 3.31)
project(Trading_Indicators)

set(CMAKE_CXX_STANDARD 20)

add_executable(Trading_Indicators main.cpp
        src/core/CsvLoader.cpp
        include/core/CsvLoader.h
        src/core/Exceptions.cpp
        include/core/Exceptions.h
        src/core/Candle.cpp
        include/core/Candle.h
        src/core/TimeSeries.cpp
        include/core/TimeSeries.h)
