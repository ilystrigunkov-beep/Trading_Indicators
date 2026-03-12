#include "SpikeDetector.h"
namespace analysis {
    DetectionOutcome SpikeDetector::detect(std::span<const double> prices) const {
        if (prices.size() < 2) {
            return std::unexpected("Not enough data to detect spikes");
        }
        std::vector<double> changes;
        changes.reserve(prices.size() - 1);
        for (std::size_t i = 1; i < prices.size(); ++i) {
            const double prev = prices[i - 1];
            if (prev == 0.0) {
                changes.push_back(0.0);
                continue;
            }
            const double pct = (prices[i] - prev) / prev * 100.0;
            changes.push_back(pct);
        }
    }
}