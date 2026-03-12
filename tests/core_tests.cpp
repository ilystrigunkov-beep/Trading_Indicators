#include <gtest/gtest.h>

#include "core/CsvLoader.hpp"
#include "core/Exceptions.hpp"
#include "core/TimeSeries.hpp"
#include <fstream>
#include <string>

namespace {

    std::filesystem::path createTempCsv(const std::string& content)
    {
        auto path = std::filesystem::temp_directory_path() /"csv_loader_test.csv";

        std::ofstream file(path);
        if (!file.is_open())
            throw std::runtime_error("Failed to create temporary CSV file");

        file << content;
        file.close();

        return path;
    }

}



TEST(CsvLoaderTest,LoadsInvestingComFormat)
{
    const std::string csvData =
        "\"Date\",\"Price\",\"Open\",\"High\",\"Low\",\"Vol.\",\"Change %\"\n"
        "\"03/03/2026\",\"6,738.17\",\"6,763.38\",\"6,785.38\",\"6,730.91\",\"\",\"-2.08%\"\n"
        "\"03/02/2026\",\"6,881.62\",\"6,824.36\",\"6,901.01\",\"6,796.85\",\"\",\"0.04%\"\n";

    auto path = createTempCsv(csvData);

    auto series = core::CsvLoader::load(path.string());

    ASSERT_NE(series, nullptr);
    ASSERT_EQ(series->size(),2u);

    const auto& candle = series->at(0);

    EXPECT_NEAR(candle.open(),6763.38, 1e-6);
    EXPECT_NEAR(candle.high(),6785.38, 1e-6);
    EXPECT_NEAR(candle.low(),6730.91, 1e-6);
    EXPECT_NEAR(candle.close(),6738.17, 1e-6);
}


TEST(CsvLoaderTest, ThrowsExceptionIfFileMissing)
{
    EXPECT_THROW(
        core::CsvLoader::load("file_that_does_not_exist.csv"),
        core::FileException
    );
}