add_library(core
        core/Candle.cpp
        core/TimeSeries.cpp
        core/CsvLoader.cpp
        core/Exceptions.cpp
)

target_include_directories(core
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

add_library(indicators
        indicators/MovingAverage.cpp
        indicators/RSI.cpp
        indicators/DoubleMA.cpp
)

target_include_directories(indicators
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(indicators
        PUBLIC
        core
)

add_library(analysis
        analysis/SpikeDetector.cpp
        analysis/Statistics.cpp
)

target_include_directories(analysis
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(analysis
        PUBLIC
        core
)
