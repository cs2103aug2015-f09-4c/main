//@@author A0097681N
#include "ConfigureCommandTokeniser.h"

ConfigureCommandTokeniser::ConfigureCommandTokeniser(void) {
	// nothing here
}

ConfigureCommandTokeniser::~ConfigureCommandTokeniser(void) {
	// nothing here
}

bool ConfigureCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isConfigureSaveLocation(userInput)) {
		return true;
	}
	return false;
}

CommandTokens ConfigureCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Configure);

	if (isConfigureSaveLocation(userInput)) {
		tokeniseConfigureSaveLocation(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool ConfigureCommandTokeniser::isConfigureSaveLocation(std::string userInput) {
	return isRegexMatch(&userInput, "CONFIGURE SAVE LOCATION .+");
}

void ConfigureCommandTokeniser::tokeniseConfigureSaveLocation(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::SaveLocation);

	std::smatch matchResults = getRegexMatches(&userInput, "CONFIGURE SAVE LOCATION (.+)");

	std::string saveLocation = matchResults[1];
	outputCommandTokens->setOtherCommandParameter(saveLocation);
}
