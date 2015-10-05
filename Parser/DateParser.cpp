#include "DateParser.h"


DateParser::DateParser(void) {
	// nothing here
}

boost::posix_time::ptime DateParser::parse(std::string dateString) {
	// defaults to dateString, if dateString is not formatted, boost library
	// will handle exception
	std::string formattedDateString = dateString;

	// checks if any of the common date/time format matches; updates formmatted
	// dateString accordingly
	if (isDDMMYYYY_TTTT(dateString)) {
		formattedDateString = parseDDMMYYYY_TTTT(dateString);
	}

	boost::posix_time::ptime ptimeObject(boost::posix_time::time_from_string(formattedDateString));
	return ptimeObject;
}

bool DateParser::isDDMMYYYY_TTTT(std::string dateString) {
	return std::regex_match(dateString,
		std::regex("[0-9]{2}-[0-9]{2}-[0-9]{4} [0-9]{4}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

std::string DateParser::parseDDMMYYYY_TTTT(std::string dateString) {
	std::smatch matchResults;
	std::regex_match(dateString, matchResults,
		std::regex("([0-9]{2})-([0-9]{2})-([0-9]{4}) ([0-9]{4})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	std::string day, month, year, hour, minute, formattedDateString;
	day = matchResults[1];
	month = matchResults[2];
	year = matchResults[3];
	hour = matchResults[4].str().substr(0,2);
	minute = matchResults[4].str().substr(2,2);
	formattedDateString = year + "-" + month + "-" + day + " " + hour + ":" + minute + ":00.000";

	return formattedDateString;
}