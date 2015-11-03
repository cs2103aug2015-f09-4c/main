//@@ author A0097681N
#include "CommandTokeniser.h"
#include "DateParser.h"

CommandTokeniser::CommandTokeniser(void) {
	// nothing here
}

CommandTokeniser::~CommandTokeniser(void) {
	// nothing here
}

boost::posix_time::ptime CommandTokeniser::parseUserInputDate(std::string userInputDate) {
	return DateParser::parse(userInputDate);
}

bool CommandTokeniser::isRegexMatch(const std::string* userInput, std::string regexString) {
	return std::regex_match(*userInput,
	                        std::regex(regexString,
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

std::smatch CommandTokeniser::getRegexMatches(const std::string* userInput, std::string regexString) {
	std::smatch matchResults;
	std::regex_match(*userInput,
	                 matchResults,
	                 std::regex(regexString,
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));
	return matchResults;
}
