#include "date_parser.hpp"
std::chrono::system_clock::time_point DateParser::parseDate() const
{
    std::tm tm = {};
    std::stringstream ss(date);
    ss >> std::get_time(&tm, "%d/%m/%Y %H:%M");

    if (ss.fail())
    {
        throw std::invalid_argument("Failed to parse date and time");
    }
    std::time_t time = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(time);
}



