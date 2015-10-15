#pragma once
#include <regex>
#include "../boost/date_time/posix_time/ptime.hpp"

class DateParser {
public:
	DateParser(void);
	boost::posix_time::ptime parse(std::string dateString);

private:
	bool isDDMMYYYY_TTTT(std::string dateString);
	std::string parseDDMMYYYY_TTTT(std::string dateString);
};
