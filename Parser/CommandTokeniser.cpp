#include "CommandTokeniser.h"

CommandTokeniser::CommandTokeniser(void) {
}


CommandTokeniser::~CommandTokeniser(void) {
}

boost::posix_time::ptime CommandTokeniser::parseUserInputDate(std::string userInputDate) {
	return _dateParser.parse(userInputDate);
}