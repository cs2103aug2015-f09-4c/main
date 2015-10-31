//@@ author A0097681N
#include "ExportCommandTokeniser.h"

ExportCommandTokeniser::ExportCommandTokeniser(void) {
	// nothing here
}

ExportCommandTokeniser::~ExportCommandTokeniser(void) {
	// nothing here
}

bool ExportCommandTokeniser::isValidCommand(std::string userInput) {
	if (isExportToLocalDisk(userInput)) {
		return true;
	}
	return false;
}

CommandTokens ExportCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(isValidCommand(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Export);

	if (isExportToLocalDisk(userInput)) {
		tokeniseExportToLocalDisk(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool ExportCommandTokeniser::isExportToLocalDisk(std::string userInput) {
	return std::regex_match(userInput, std::regex("EXPORT [^ ]+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
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
