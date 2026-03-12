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
    class SpikeDetector : public Analyzer {
        double threshold_sigma_;
    public:
        explicit SpikeDetector(double threshold_sigma = 2.0) : threshold_sigma_(threshold_sigma) {}
        [[nodiscard]] const char* name() const noexcept override { return "SpikeDetector"; }
        [[nodiscard]] std::shared_ptr<Analyzer> clone() const override {
            return std::make_shared<SpikeDetector>(*this);
        }
        [[nodiscard]] DetectionOutcome detect(std::span<const double> prices) const;
        [[nodiscard]] double threshold_sigma() const noexcept { return threshold_sigma_; }
    };
}