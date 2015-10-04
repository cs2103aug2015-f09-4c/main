#pragma once
#include <regex>
#include <string>
#include "../boost/date_time/posix_time/ptime.hpp"
#include <boost/date_time/posix_time/time_parsers.hpp>

class DateParser {
public:
	DateParser(void);
	boost::posix_time::ptime parse(std::string dateString);
};

