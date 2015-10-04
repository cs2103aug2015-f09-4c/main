#include "DateParser.h"


DateParser::DateParser(void) {
	// nothing here
}

boost::posix_time::ptime DateParser::parse(std::string dateString) {
	boost::posix_time::ptime ptimePlaceholder(boost::posix_time::time_from_string(dateString));
	return ptimePlaceholder;
}