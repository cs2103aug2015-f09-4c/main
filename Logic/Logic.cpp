#include "Logic.h"

Logic::Logic()  {
	_commandExecutor = new CommandExecutor();
	logger = Logger::getInstance();
	logger->logINFO("Logic is initialized.");
}

UIFeedback Logic::executeCommand(std::string userString) {
	logger->logTRACE("\"" + userString + "\" is sent to parser for parsing.");
	CommandTokens commandTokens = _parser.parse(userString);
	
	Command* command = _commandCreator.process(commandTokens);

	UIFeedback feedback = _commandExecutor->execute(command);
	
	return feedback;
}

Logic::~Logic() {
	delete _commandExecutor;
}