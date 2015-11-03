//@@ author A0097681N
#include "ExportCommandTokeniser.h"

ExportCommandTokeniser::ExportCommandTokeniser(void) {
	// nothing here
}

ExportCommandTokeniser::~ExportCommandTokeniser(void) {
	// nothing here
}

bool ExportCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isExportToLocalDisk(userInput)) {
		return true;
	}
	return false;
}

CommandTokens ExportCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Export);

	if (isExportToLocalDisk(userInput)) {
		tokeniseExportToLocalDisk(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool ExportCommandTokeniser::isExportToLocalDisk(std::string userInput) {
	return isRegexMatch(userInput,"EXPORT [^ ]+");
}

void ExportCommandTokeniser::tokeniseExportToLocalDisk(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::None);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("EXPORT ([^ ]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string exportPath = matchResults[1];
	outputCommandTokens->setOtherCommandParameter(exportPath);
}
