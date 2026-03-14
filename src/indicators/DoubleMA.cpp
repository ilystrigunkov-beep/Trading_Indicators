#include "indicators/DoubleMA.hpp"

#include <stdexcept>

namespace indicators {

DoubleMA::DoubleMA(std::size_t fast_window, std::size_t slow_window)
    : fast_(fast_window), slow_(slow_window) {
    if (fast_window == 0 || slow_window == 0) {
        throw std::invalid_argument("Moving average window must be > 0");
    }

    if (fast_window >= slow_window) {
        throw std::invalid_argument("Fast window must be smaller than slow window");
    }
}

std::vector<double> DoubleMA::compute_fast(std::span<const double> values) const {
    return fast_.compute(values);
}

std::vector<double> DoubleMA::compute_slow(std::span<const double> values) const {
    return slow_.compute(values);
}

std::vector<Crossover> DoubleMA::find_crossovers(std::span<const double> values) const {
    const auto fast_values = fast_.compute(values);
    const auto slow_values = slow_.compute(values);

    if (fast_values.empty() || slow_values.empty()) {
        return {};
    }

    const auto n = values.size();
    const auto fast_offset = fast_window() - 1;
    const auto slow_offset = slow_window() - 1;

    std::vector<Crossover> signals;

    std::size_t i = slow_offset;
    double prev_diff = fast_values[i - fast_offset] - slow_values[i - slow_offset];

    for (++i; i < n; ++i) {
        const auto fi = i - fast_offset;
        const auto si = i - slow_offset;

        const double diff = fast_values[fi] - slow_values[si];

        if (prev_diff <= 0.0 && diff > 0.0) {
            signals.push_back({i, CrossoverType::GoldenCross});
        }
        else if (prev_diff >= 0.0 && diff < 0.0) {
            signals.push_back({i, CrossoverType::DeathCross});
        }

        prev_diff = diff;
    }

    return signals;
}

} // namespace indicators
