
#include "CsvLoader.h"
#include <vector>
#include <charconv>
namespace core {
    namespace {
        std::vector<std::string> split(const std::string& line, char delimiter) {
            std::vector<std::string> tokens;
            std::string current;
            bool in_quotes = false;

            for (char ch : line) {
                if (ch == '"'){
                    in_quotes = !in_quotes;
                }

                else if (ch == delimiter &&  !in_quotes){
                    tokens.push_back(current);
                    current.clear();
                }

                else{
                    current.push_back(ch);
                }
            }
            tokens.push_back(current);
            return tokens;
        }
        std::optional<long long> parse_int64(std::string_view text) {
            long long value{};

            auto* begin= text.data();
            auto* end= text.data()+text.size();
            auto [ptr,ec] = std::from_chars(begin,end,value);

            if (ec != std::errc{} || ptr !=end) {
                return std::nullopt;
            }
            return value;
        }

    }
}