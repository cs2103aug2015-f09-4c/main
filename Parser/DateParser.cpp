#include "DateParser.h"
#include "boost\date_time\posix_time\time_parsers.hpp"

DateParser::DateParser(void) {
	// nothing here
}

boost::posix_time::ptime DateParser::parse(std::string userInputDateString) {
	boost::posix_time::ptime retVal;

	if (isLocallySupportedDateFormat(userInputDateString)) {
		std::string formattedDateString = convertToFormattedDateString(userInputDateString);
		retVal = getPtimeObject(formattedDateString);

	} else if (isBoostLibrarySupportedDateFormat(userInputDateString)) {
		retVal = getPtimeObject(userInputDateString);

	} else {
		retVal = getInvalidPtimeObject();
	}

	return retVal;
}

bool DateParser::isLocallySupportedDateFormat(std::string userInputDateString) {
	if (isDDMMYYYY_TTTT(userInputDateString)) {
		return true;
	}
	return false;
}

// checks if userInputDateString is in a format supported by Boost Library
// by passing it as parameter to in-built function
// if exception is thrown, format is not supported;
// otherwise, format is supported
bool DateParser::isBoostLibrarySupportedDateFormat(std::string userInputDateString) {
	try {
		boost::posix_time::time_from_string(userInputDateString);
		return true;
	} catch (std::exception e) {
		return false;
	}
}

std::string DateParser::convertToFormattedDateString(std::string userInputDateString) {
	std::string formattedDateString = "";

	if (isDDMMYYYY_TTTT(userInputDateString)) {
		formattedDateString = parseDDMMYYYY_TTTT(userInputDateString);
	}

	return formattedDateString;
}

boost::posix_time::ptime DateParser::getPtimeObject(std::string formattedDateString) {
	boost::posix_time::ptime retVal;

	try {
		retVal = boost::posix_time::ptime(boost::posix_time::time_from_string(formattedDateString));
	} catch (std::exception e) {
		retVal = getInvalidPtimeObject();
	}

	return retVal;
}

boost::posix_time::ptime DateParser::getInvalidPtimeObject() {
	return boost::posix_time::ptime();
}

bool DateParser::isDDMMYYYY_TTTT(std::string dateString) {
	return std::regex_match(dateString,
	                        std::regex("[0-9]{2}-[0-9]{2}-[0-9]{4} [0-9]{2}[0-9]{2}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

std::string DateParser::parseDDMMYYYY_TTTT(std::string dateString) {
	std::smatch matchResults;
	std::regex_match(dateString, matchResults,
	                 std::regex("([0-9]{2})-([0-9]{2})-([0-9]{4}) ([0-9]{2})([0-9]{2})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string day, month, year, hour, minute, formattedDateString;
	day = matchResults[1];
	month = matchResults[2];
	year = matchResults[3];
	hour = matchResults[4];
	minute = matchResults[5];
	formattedDateString = year + "-" + month + "-" + day + " " + hour + ":" + minute + ":00.000";

	return formattedDateString;
}
