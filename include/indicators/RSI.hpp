#pragma once

#include "indicators/Indicator.hpp"

#include <cstddef>
#include <span>
#include <vector>

namespace indicators {

class RSI : public Indicator {
private:
    std::size_t period_;

public:
    explicit constexpr RSI(std::size_t period) : period_(period) {}

    [[nodiscard]] const char* name() const noexcept override { return "RSI"; }

    [[nodiscard]] constexpr std::size_t period() const noexcept { return period_; }

    [[nodiscard]] std::vector<double> compute(std::span<const double> values) const;
};

} // namespace indicators
