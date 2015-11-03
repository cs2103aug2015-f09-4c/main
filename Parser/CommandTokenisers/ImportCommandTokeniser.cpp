#include "ImportCommandTokeniser.h"

ImportCommandTokeniser::ImportCommandTokeniser(void) {
	// nothing
}

ImportCommandTokeniser::~ImportCommandTokeniser(void) {
	// nothing
}

bool ImportCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isImportLocal(userInput)) {
		return true;
	}
	return false;
}

CommandTokens ImportCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Import);

	if (isImportLocal(userInput)) {
		tokeniseImportLocal(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool ImportCommandTokeniser::isImportLocal(std::string userInput) {
	return isRegexMatch(&userInput, "IMPORT [^ ]+");
}

void ImportCommandTokeniser::tokeniseImportLocal(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::None);

	std::smatch matchResults = getRegexMatches(&userInput, "IMPORT ([^ ]+)");

	std::string importFilePath = matchResults[1];
	outputCommandTokens->setOtherCommandParameter(importFilePath);
}
