//@@ author A0097681N
#include "CommandTokeniser.h"

CommandTokeniser::CommandTokeniser(void) {
	// nothing here
}

CommandTokeniser::~CommandTokeniser(void) {
	// nothing here
}

CommandTokens CommandTokeniser::tokeniseUserInput(std::string userInput) {
	// nothing here, to be implemented by subclasses
	// this function not made pure virtual because the function in Parser needs to
	// return a CommandTokeniser, which cannot be an abstract class

	return CommandTokens();
}

boost::posix_time::ptime CommandTokeniser::parseUserInputDate(std::string userInputDate) {
	return _dateParser.parse(userInputDate);
}
