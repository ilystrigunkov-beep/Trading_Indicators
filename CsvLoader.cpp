
#include "CsvLoader.h"
#include <vector>

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

    }
}