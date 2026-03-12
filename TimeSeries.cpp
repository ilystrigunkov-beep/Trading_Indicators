//
// Created by Aboba on 13.03.2026.
//

#include "TimeSeries.h"
#include <cstddef>
#include <span>
#include <vector>

#include <stdexcept>

namespace core {
    TimeSeries::TimeSeries(std::vector<Candle> candles) : candles_(std::move(candles)) {}
}
