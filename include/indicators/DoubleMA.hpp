#pragma once

#include "indicators/Indicator.hpp"
#include "indicators/MovingAverage.hpp"

#include <cstddef>
#include <span>
#include <vector>

namespace indicators {

enum class CrossoverType {
    GoldenCross,
    DeathCross
};

struct Crossover {
    std::size_t index;
    CrossoverType type;
};

class DoubleMA : public Indicator {
private:
    MovingAverage fast_;
    MovingAverage slow_;

public:
    DoubleMA(std::size_t fast_window, std::size_t slow_window);

    [[nodiscard]] const char* name() const noexcept override { return "DoubleMA"; }
};

} // namespace indicators
