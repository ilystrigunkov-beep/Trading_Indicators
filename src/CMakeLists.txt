add_library(core
        core/Candle.cpp
        core/TimeSeries.cpp
        core/CsvLoader.cpp
        core/Exceptions.cpp
)

target_include_directories(core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)