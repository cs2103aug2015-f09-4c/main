//@@ author A0097681N
#include "DisplayCommandTokeniser.h"

DisplayCommandTokeniser::DisplayCommandTokeniser(void) {
	// nothing here
}

DisplayCommandTokeniser::~DisplayCommandTokeniser(void) {
	// nothing here
}

bool DisplayCommandTokeniser::isValidCommand(std::string userInput) {
	if (isDisplayAll(userInput) ||
		isDisplayFloating(userInput) ||
		isDisplayFromTo(userInput) ||
		isDisplayFrom(userInput) ||
		isDisplayBy(userInput)) {
		return true;
	}
	return false;
}

CommandTokens DisplayCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(isValidCommand(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Display);

	if (isDisplayAll(userInput)) {
		tokeniseDisplayAll(&tokenisedCommand);
	} else if (isDisplayFloating(userInput)) {
		tokeniseDisplayFloating(&tokenisedCommand);
	} else if (isDisplayFromTo(userInput)) {
		tokeniseDisplayFromTo(userInput, &tokenisedCommand);
	} else if (isDisplayFrom(userInput)) {
		tokeniseDisplayFrom(userInput, &tokenisedCommand);
	} else if (isDisplayBy(userInput)) {
		tokeniseDisplayBy(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

void DisplayCommandTokeniser::tokeniseDisplayAll(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::All);
}

void DisplayCommandTokeniser::tokeniseDisplayFloating(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Floating);
}

void DisplayCommandTokeniser::tokeniseDisplayFromTo(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("DISPLAY FROM (.+) TO (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[1]);
	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[2]);

	outputCommandTokens->setStartDateTime(startDateTime);
	outputCommandTokens->setEndDateTime(endDateTime);
}

void DisplayCommandTokeniser::tokeniseDisplayFrom(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("DISPLAY FROM (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setStartDateTime(startDateTime);
}

void DisplayCommandTokeniser::tokeniseDisplayBy(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("DISPLAY BY (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setEndDateTime(endDateTime);
}

bool DisplayCommandTokeniser::isDisplayAll(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY ALL",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayFloating(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY FLOATING",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayFromTo(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY FROM .+ TO .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayFrom(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY FROM .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayBy(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY BY .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}
