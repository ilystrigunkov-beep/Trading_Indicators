#include "Statistics.h"
namespace analysis {
    double mean(std::span<const double> data) {
        if (data.empty()) {
            return 0.0;
        }
        double sum = 0.0;
        for (const double& value : data) {
            sum += value;
        }
        return sum / static_cast<double>(data.size());
    }
}