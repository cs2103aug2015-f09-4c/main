//@@ author A0097681N
#pragma once
#include <regex>
#include "../boost/date_time/posix_time/ptime.hpp"

class DateParser {
public:
	DateParser(void);
	boost::posix_time::ptime parse(std::string dateString);

private:
	bool isLocallySupportedDateFormat(std::string userInputDateString);
	bool isBoostLibrarySupportedDateFormat(std::string userInputDateString);

	std::string convertToFormattedDateString(std::string userInputDateString);
	boost::posix_time::ptime getPtimeObject(std::string formattedDateString);
	boost::posix_time::ptime getInvalidPtimeObject(void);

	bool isDDMMYYYY_TTTT(std::string dateString);
	bool isDDMMYY(std::string dateString);
	std::string parseDDMMYYYY_TTTT(std::string dateString);
	std::string parseDDMMYYYY(std::string dateString);
};
