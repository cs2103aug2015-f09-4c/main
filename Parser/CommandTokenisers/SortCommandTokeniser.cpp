//@@ author A0097681N
#include "SortCommandTokeniser.h"

SortCommandTokeniser::SortCommandTokeniser(void) {
	// nothing here
}

SortCommandTokeniser::~SortCommandTokeniser(void) {
	// nothing here
}

bool SortCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isSortName(userInput) ||
		isSortStart(userInput) ||
		isSortEnd(userInput)) {
		return true;
	}
	return false;
}

CommandTokens SortCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Sort);

	if (isSortName(userInput)) {
		tokeniseSortName(userInput, &tokenisedCommand);

	} else if (isSortStart(userInput)) {
		tokeniseSortStart(userInput, &tokenisedCommand);

	} else if (isSortEnd(userInput)) {
		tokeniseSortEnd(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool SortCommandTokeniser::isSortName(std::string userInput) {
	return isRegexMatch(userInput, "SORT NAME( DESC)?");
}

bool SortCommandTokeniser::isSortStart(std::string userInput) {
	return isRegexMatch(userInput, "SORT START( DESC)?");
}

bool SortCommandTokeniser::isSortEnd(std::string userInput) {
	return isRegexMatch(userInput, "SORT END( DESC)?");
}

void SortCommandTokeniser::tokeniseSortName(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Name);

	std::string sortOrder = getSortOrder(userInput);
	outputCommandTokens->setOtherCommandParameter(sortOrder);
}

void SortCommandTokeniser::tokeniseSortStart(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Start);

	std::string sortOrder = getSortOrder(userInput);
	outputCommandTokens->setOtherCommandParameter(sortOrder);
}

void SortCommandTokeniser::tokeniseSortEnd(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::End);

	std::string sortOrder = getSortOrder(userInput);
	outputCommandTokens->setOtherCommandParameter(sortOrder);
}

std::string SortCommandTokeniser::getSortOrder(std::string userInput) {
	std::string sortOrder = "Ascending";

	if (std::regex_match(userInput,
	                     std::regex(".+ DESC",
	                                std::regex_constants::ECMAScript | std::regex_constants::icase))) {
		sortOrder = "Descending";
	}

	return sortOrder;
}
