#include "indicators/RSI.hpp"

#include <algorithm>
#include <cmath>

namespace indicators {

std::vector<double> RSI::compute(std::span<const double> values) const {
    if (period_ == 0 || values.size() < period_ + 1) {
        return {};
    }

    std::vector<double> result;
    result.reserve(values.size() - period_);

    std::vector<double> changes;
    changes.reserve(values.size() - 1);
    for (std::size_t i = 1; i < values.size(); ++i) {
        changes.push_back(values[i] - values[i - 1]);
    }

    double sum_gains = 0.0;
    double sum_losses = 0.0;
    for (std::size_t i = 0; i < period_; ++i) {
        if (changes[i] > 0.0) {
            sum_gains += changes[i];
        } else {
            sum_losses += -changes[i];
        }
    }

    double avg_gain = sum_gains / static_cast<double>(period_);
    double avg_loss = sum_losses / static_cast<double>(period_);

    double rs = avg_loss == 0.0 ? 100.0 : avg_gain / avg_loss;
    double rsi = 100.0 - (100.0 / (1.0 + rs));
    result.push_back(rsi);

    for (std::size_t i = period_ + 1; i < values.size(); ++i) {
        const double change = changes[i - 1];
        const double gain = change > 0.0 ? change : 0.0;
        const double loss = change < 0.0 ? -change : 0.0;

        avg_gain = (avg_gain * static_cast<double>(period_ - 1) + gain) / static_cast<double>(period_);
        avg_loss = (avg_loss * static_cast<double>(period_ - 1) + loss) / static_cast<double>(period_);

        rs = avg_loss == 0.0 ? 100.0 : avg_gain / avg_loss;
        rsi = 100.0 - (100.0 / (1.0 + rs));
        result.push_back(rsi);
    }

    return result;
}

} // namespace indicators
