//@@ author A0097681N
#include "EditCommandTokeniser.h"

EditCommandTokeniser::EditCommandTokeniser(void) {
	// nothing here
}

EditCommandTokeniser::~EditCommandTokeniser(void) {
	// nothing here
}

bool EditCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isEditName(userInput) ||
		isEditEndDate(userInput) ||
		isEditStartDate(userInput)) {
		return true;
	}
	return false;
}

CommandTokens EditCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Edit);

	if (isEditName(userInput)) {
		tokeniseEditName(userInput, &tokenisedCommand);

	} else if (isEditStartDate(userInput)) {
		tokeniseEditStartDate(userInput, &tokenisedCommand);

	} else if (isEditEndDate(userInput)) {
		tokeniseEditEndDate(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool EditCommandTokeniser::isEditName(std::string userInput) {
	return isRegexMatch(&userInput, "EDIT NAME [0-9]+ .+");
}

bool EditCommandTokeniser::isEditStartDate(std::string userInput) {
	return isRegexMatch(&userInput, "EDIT START [0-9]+ .+");
}

bool EditCommandTokeniser::isEditEndDate(std::string userInput) {
	return isRegexMatch(&userInput, "EDIT END [0-9]+ .+");
}

void EditCommandTokeniser::tokeniseEditName(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Name);

	std::smatch matchResults = getRegexMatches(&userInput, "EDIT NAME ([0-9]+) (.+)");

	int index = stoi(matchResults[1]);
	std::string taskName = matchResults[2];

	outputCommandTokens->setIndex(index);
	outputCommandTokens->setTaskName(taskName);
}

void EditCommandTokeniser::tokeniseEditStartDate(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Start);

	std::smatch matchResults = getRegexMatches(&userInput, "EDIT START ([0-9]+) (.+)");

	int index = stoi(matchResults[1]);
	boost::posix_time::ptime startDate = parseUserInputDate(matchResults[2]);

	outputCommandTokens->setIndex(index);
	outputCommandTokens->setStartDateTime(startDate);
}

void EditCommandTokeniser::tokeniseEditEndDate(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::End);

	std::smatch matchResults = getRegexMatches(&userInput, "EDIT END ([0-9]+) (.+)");

	int index = stoi(matchResults[1]);
	boost::posix_time::ptime endDate = parseUserInputDate(matchResults[2]);

	outputCommandTokens->setIndex(index);
	outputCommandTokens->setEndDateTime(endDate);
}
