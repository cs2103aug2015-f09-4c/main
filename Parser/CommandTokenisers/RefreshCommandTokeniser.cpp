//@@author A0097681N
#include "RefreshCommandTokeniser.h"

RefreshCommandTokeniser::RefreshCommandTokeniser(void) {
	// nothing
}

RefreshCommandTokeniser::~RefreshCommandTokeniser(void) {
	// nothing
}

bool RefreshCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isRefreshBasic(userInput)) {
		return true;
	}
	return false;
}

CommandTokens RefreshCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Refresh);

	if (isRefreshBasic(userInput)) {
		tokeniseRefreshBasic(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool RefreshCommandTokeniser::isRefreshBasic(std::string userInput) {
	return isRegexMatch(&userInput, "REFRESH");
}

void RefreshCommandTokeniser::tokeniseRefreshBasic(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::None);
}
