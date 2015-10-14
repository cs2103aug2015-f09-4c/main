#include "CommandTokeniser.h"

CommandTokeniser::CommandTokeniser(void) {
	// nothing here
}


CommandTokeniser::~CommandTokeniser(void) {
	// nothing here
}

boost::posix_time::ptime CommandTokeniser::parseUserInputDate(std::string userInputDate) {
	return _dateParser.parse(userInputDate);
}
