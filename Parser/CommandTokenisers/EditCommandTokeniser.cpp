//@@ author A0097681N
#include "EditCommandTokeniser.h"

EditCommandTokeniser::EditCommandTokeniser(void) {
	// nothing here
}

EditCommandTokeniser::~EditCommandTokeniser(void) {
	// nothing here
}

bool EditCommandTokeniser::isValidCommand(std::string userInput) {
	if (isEditName(userInput) ||
		isEditEndDate(userInput) ||
		isEditStartDate(userInput)) {
		return true;
	}
	return false;
}

CommandTokens EditCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(isValidCommand(userInput));

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
	return std::regex_match(userInput,
	                        std::regex("EDIT NAME [0-9]+ .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool EditCommandTokeniser::isEditStartDate(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("EDIT START [0-9]+ .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool EditCommandTokeniser::isEditEndDate(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("EDIT END [0-9]+ .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void EditCommandTokeniser::tokeniseEditName(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Name);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("EDIT NAME ([0-9]+) (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	std::string taskName = matchResults[2];

	outputCommandTokens->setIndex(index);
	outputCommandTokens->setTaskName(taskName);
}

void EditCommandTokeniser::tokeniseEditStartDate(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("EDIT START ([0-9]+) (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	boost::posix_time::ptime startDate = parseUserInputDate(matchResults[2]);

	outputCommandTokens->setIndex(index);
	outputCommandTokens->setStartDateTime(startDate);
}

void EditCommandTokeniser::tokeniseEditEndDate(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::End);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("EDIT END ([0-9]+) (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	boost::posix_time::ptime endDate = parseUserInputDate(matchResults[2]);

	outputCommandTokens->setIndex(index);
	outputCommandTokens->setEndDateTime(endDate);
}
