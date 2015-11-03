//@@ author A0097681N
#include "CommandTokeniser.h"
#include "DateParser.h"

CommandTokeniser::CommandTokeniser(void) {
	// nothing here
}

CommandTokeniser::~CommandTokeniser(void) {
	// nothing here
}

bool CommandTokeniser::isRegexMatch(std::string userInput, std::string regexString) {
	return std::regex_match(userInput,
	                        std::regex(regexString, std::regex_constants::ECMAScript));
}

boost::posix_time::ptime CommandTokeniser::parseUserInputDate(std::string userInputDate) {
	return DateParser::parse(userInputDate);
}
