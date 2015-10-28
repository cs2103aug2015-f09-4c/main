#include "DateParser.h"
#include "boost\date_time\posix_time\time_parsers.hpp"

DateParser::DateParser(void) {
	// nothing here
}

boost::posix_time::ptime DateParser::parse(std::string userInputDateString) {

	// formattedDateString defaults to userInputDateString,
	// if userInputDateString is not properly formatted, boost library will
	// throw the appropriate exception
	std::string formattedDateString = userInputDateString;

	// checks if any of the supported date/time format matches userInputDateString
	// if so, parses it and update the formattedDateSTring accordingly
	if (isDDMMYYYY_TTTT(userInputDateString)) {
		formattedDateString = parseDDMMYYYY_TTTT(userInputDateString);
	}

	try {
		boost::posix_time::ptime ptimeObject(boost::posix_time::time_from_string(formattedDateString));
		return ptimeObject;
	} catch (std::exception e) {
		return boost::posix_time::ptime(); // defaults to invalid date/time
	}
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
