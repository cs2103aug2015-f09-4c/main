#include "Logic.h"

Logic::Logic(std::string fileName)  {
	_fileName = fileName;
	_commandExecutor = new CommandExecutor(fileName);
}

UIFeedback Logic::executeCommand(std::string userString) {
	CommandTokens commandTokens= _parser.parse(userString);
	
	Command* command= _commandCreator.process(commandTokens);

	UIFeedback feedback = _commandExecutor->execute(command);
	
	return feedback;
}

Logic::~Logic() {
	delete _commandExecutor;
}