#ifndef DATA_PARSER_HPP
#define DATA_PARSER_HPP
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

class DateParser
{
public:
    DateParser(std::string data) : date{data} {}
    std::chrono::system_clock::time_point parseDate() const;

private:
    std::string date;
};

#endif