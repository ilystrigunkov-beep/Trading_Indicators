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

} // namespace indicators
