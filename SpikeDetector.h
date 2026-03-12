#pragma once
#include "Analyzer.h"
#include <cstddef>
#include <expected>
#include <memory>
#include <span>
#include <string>
#include <vector>
#include <variant>
namespace analysis {
    struct Spike {
        std::size_t index;
        double change_pct;
    };
    using SpikeList = std::vector<Spike>;
    using DetectionResult = std::variant<SpikeList, std::string>;
    using DetectionOutcome = std::expected<SpikeList, std::string>;
    [[nodiscard]] DetectionResult to_detection_result(DetectionOutcome outcome);
}