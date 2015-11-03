//@@ author A0097681N
#include "DisplayCommandTokeniser.h"

DisplayCommandTokeniser::DisplayCommandTokeniser(void) {
	// nothing here
}

DisplayCommandTokeniser::~DisplayCommandTokeniser(void) {
	// nothing here
}

bool DisplayCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isDisplayAll(userInput) ||
		isDisplayFloating(userInput) ||
		isDisplayActivity(userInput) ||
		isDisplayTodo(userInput)) {
		return true;
	}
	return false;
}

CommandTokens DisplayCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Display);

	if (isDisplayAll(userInput)) {
		tokeniseDisplayAll(&tokenisedCommand);
	} else if (isDisplayActivity(userInput)) {
		tokeniseDisplayActivity(&tokenisedCommand);
	} else if (isDisplayTodo(userInput)) {
		tokeniseDisplayTodo(&tokenisedCommand);
	} else if (isDisplayFloating(userInput)) {
		tokeniseDisplayFloating(&tokenisedCommand);
	}

	return tokenisedCommand;
}

void DisplayCommandTokeniser::tokeniseDisplayAll(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::All);
}

void DisplayCommandTokeniser::tokeniseDisplayActivity(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::FromTo);
}

void DisplayCommandTokeniser::tokeniseDisplayTodo(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::By);
}

void DisplayCommandTokeniser::tokeniseDisplayFloating(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Floating);
}

bool DisplayCommandTokeniser::isDisplayAll(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY ALL",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayActivity(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY ACTIVITY",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayTodo(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY TODO",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayFloating(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DISPLAY FLOATING",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}
