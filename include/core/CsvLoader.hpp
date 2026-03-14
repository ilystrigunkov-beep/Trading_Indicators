//
// Created by Aboba on 13.03.2026.
//

#ifndef TRADING_INDICATORS_CSVLOADER_H
#define TRADING_INDICATORS_CSVLOADER_H

#include "TimeSeries.hpp"
#include <memory>
#include <string>

namespace core {

    class CsvLoader {
    public:
        static std::unique_ptr<TimeSeries> load(const std::string& path,char delimiter =',');
    };

}

#endif //TRADING_INDICATORS_CSVLOADER_H