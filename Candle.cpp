//
// Created by Aboba on 13.03.2026.
//

#include "Candle.h"


namespace core {

    Candle::Candle(TimePoint timestamp,
                   double open,
                   double high,
                   double low,
                   double close,
                   std::optional<double> volume)
        : timestamp_(timestamp),
          open_(open),
          high_(high),
          low_(low),
          close_(close),
          volume_(volume) {}

}