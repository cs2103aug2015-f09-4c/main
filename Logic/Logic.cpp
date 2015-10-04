#include "Logic.h"

Logic::Logic(std::string fileName)  {
	_fileName = fileName;
	_commandExecutor = new CommandExecutor(fileName);
}

UIFeedback Logic::executeCommand(std::string userString) {
	CommandTokens commandTokens= _parser.parse(userString);
	if (commandTokens.isValid()) {
		Command* command= _commandCreator.process(commandTokens);

		UIFeedback feedback = _commandExecutor->execute(command);
		return feedback;
	} else {
		UIFeedback feedback = _commandExecutor->execute(&InvalidCommand());
		return feedback;
	}
}