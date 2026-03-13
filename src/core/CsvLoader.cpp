
#include "../../include/core/CsvLoader.h"
#include "../../include/core/Exceptions.h"
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
        long long days_from_civil(int y,unsigned m,unsigned d) {
            y -= m <= 2;
            const int era = (y>=0 ? y : y-399) /400;
            const unsigned yoe = static_cast<unsigned>(y - era * 400);
            const unsigned doy = (153 *(m+(m>2 ? -3:9))+2)/5 +d-1;
            const unsigned doe = yoe*365+ yoe/4-yoe/100 +doy;
            return static_cast<long long>(era) * 146097 + static_cast<long long>(doe) - 719468;
        }
        std::optional<long long> parse_date_to_unix(std::string_view text) {
            std::string s(text);
            while (!s.empty() && s.front()==' ')
                s.erase(s.begin());


            while (!s.empty() && s.back() ==' ')
                s.pop_back();


            if (s.size() >=2 && ((s.front()=='"' && s.back()=='"') || (s.front()=='\'' && s.back()=='\''))) {
                s = s.substr(1,s.size()-2);
            }
            const auto first_sep=s.find('/');
            const auto second_sep=s.find('/',first_sep == std::string::npos ? 0:first_sep +1);

            if (first_sep == std::string::npos||second_sep == std::string::npos)
                return std::nullopt;

            try {
                int month =std::stoi(s.substr(0,first_sep));
                int day   =std::stoi(s.substr(first_sep+1,second_sep-first_sep-1));
                int year  =std::stoi(s.substr(second_sep+1));
                long long days = days_from_civil(year,month,day);

                return days * 86400LL;
            }
            catch (...) {
                return std::nullopt;
            }
        }
        double parse_double(const std::string& text, const std::string& field_name) {
            std::string s = text;

            while (!s.empty() && s.front() == ' ')
                s.erase(s.begin());

            while (!s.empty() && s.back() == ' ')
                s.pop_back();

            if (s.size() >= 2 &&
                ((s.front() =='"' && s.back() =='"') ||
                 (s.front() =='\'' && s.back() =='\'')))
            {
                s = s.substr(1,s.size() - 2);
            }

            s.erase(std::remove(s.begin(),s.end(),','),s.end());
            s.erase(std::remove(s.begin(),s.end(),'%'),s.end());

            if (s.empty()) return 0.0;

            double value{};
            auto result = std::from_chars(s.data(),s.data()+s.size(), value);

            if (result.ec != std::errc()) {
                throw ParseException("Failed to parse field '" +field_name +"': '" +text + "'");
            }

            return value;
        }

    }
}