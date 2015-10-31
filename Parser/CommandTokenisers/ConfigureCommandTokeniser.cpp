//@@ author A0097681N
#include "ConfigureCommandTokeniser.h"

ConfigureCommandTokeniser::ConfigureCommandTokeniser(void) {
	// nothing here
}

ConfigureCommandTokeniser::~ConfigureCommandTokeniser(void) {
	// nothing here
}

bool ConfigureCommandTokeniser::isValidCommand(std::string userInput) {
	if (isConfigureSaveLocation(userInput)) {
		return true;
	}
	return false;
}

CommandTokens ConfigureCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(isValidCommand(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Configure);

	if (isConfigureSaveLocation(userInput)) {
		tokeniseConfigureSaveLocation(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool ConfigureCommandTokeniser::isConfigureSaveLocation(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("Configure Save Location [^ ]+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void ConfigureCommandTokeniser::tokeniseConfigureSaveLocation(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::SaveLocation);

	std::smatch matchResults;
	std::regex_match(userInput,
	                 std::regex("Configure Save Location ([^ ]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string saveLocation = matchResults[1];
	outputCommandTokens->setOtherCommandParameter(saveLocation);
}
