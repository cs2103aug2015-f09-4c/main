#include "Parser.h"

CommandTokens Parser::parse(std::string userInput) {
	CommandTokens commandTokens;

	PrimaryCommandType primaryCommand = extractPrimaryCommand(userInput);
	commandTokens.setPrimaryCommand(primaryCommand);
	
	switch (primaryCommand) {
	case Add:
		extractTaskName(userInput);
	case Delete:
	case Edit:
	case Display:
	case Invalid:
	}

	SecondaryCommandType secondaryCommand = extractSecondaryCommand(userInput);

	return commandTokens;
}


Parser::Parser(void) {
	// nothing
}
