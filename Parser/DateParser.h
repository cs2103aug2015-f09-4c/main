//@@ author A0097681N
#pragma once
#include <regex>
#include "../boost/date_time/posix_time/ptime.hpp"

class DateParser {
public:
	DateParser(void);
	static boost::posix_time::ptime parse(std::string dateString);

private:
	static bool isLocallySupportedDateFormat(std::string userInputDateString);
	static bool isBoostLibrarySupportedDateFormat(std::string userInputDateString);

	static std::string convertToFormattedDateString(std::string userInputDateString);
	static boost::posix_time::ptime getPtimeObject(std::string formattedDateString);
	static boost::posix_time::ptime getInvalidPtimeObject(void);

	static bool isDDMMYYYY_TTTT(std::string dateString);
	static bool isDDMMYY(std::string dateString);
	static std::string parseDDMMYYYY_TTTT(std::string dateString);
	static std::string parseDDMMYYYY(std::string dateString);
};
