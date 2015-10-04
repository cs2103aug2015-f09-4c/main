#include "DateParser.h"


DateParser::DateParser(void) {
	// nothing here
}

boost::posix_time::ptime DateParser::parse(std::string dateString) {

	std::smatch matchResults;
	std::regex_match(dateString, matchResults,
		std::regex("([0-9]{2})-([0-9]{2})-([0-9]{4}) ([0-9]{4})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	if (!matchResults.empty()) {
		std::string day, month, year, hour, minute;
		day = matchResults[1];
		month = matchResults[2];
		year = matchResults[3];
		hour = matchResults[4].str().substr(0,2);
		minute = matchResults[4].str().substr(2,2);
		dateString = year + "-" + month + "-" + day + " " + hour + ":" + minute + ":00.000";
	}

	boost::posix_time::ptime ptimePlaceholder(boost::posix_time::time_from_string(dateString));
	return ptimePlaceholder;
}