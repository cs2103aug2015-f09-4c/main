#include "Logic.h"

Logic::Logic()  {
	_commandExecutor = new CommandExecutor();
	logger = Logger::getInstance();
	logger->logINFO("Logic is initialized.");
}

UIFeedback Logic::executeCommand(std::string userString) {
	UIFeedback feedback;

	logger->logTRACE("\"" + userString + "\" is sent to parser for parsing.");

	CommandTokens commandTokens = _parser.parse(userString);
	try {
		if (commandTokens.getPrimaryCommand() == CommandTokens::PrimaryCommandType::Undo) {
			return _commandExecutor->undo();
		}
		Command* command = _commandCreator.process(commandTokens);
		feedback = _commandExecutor->execute(command);
	} catch (std::exception e) {
		throw e.what();
	}
	return feedback;
}

Logic::~Logic() {
	delete _commandExecutor;
}