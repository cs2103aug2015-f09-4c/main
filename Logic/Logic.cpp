//@@author A0112218W

#include "Logic.h"

Logic::Logic()  {
	_commandExecutor = new CommandExecutor();
	logger = Logger::getInstance();
	logger->logINFO("Logic is initialized.");
}

UIFeedback Logic::executeCommand(std::string userString) {
	UIFeedback feedback;

	logger->logINFO("\"" + userString + "\" is sent to parser for parsing.");

	CommandTokens commandTokens = _parser.parse(userString);
	try {
		if (commandTokens.getPrimaryCommand() == CommandTokens::PrimaryCommandType::Undo) {
			return _commandExecutor->undo();
		}
		Command* command = _commandCreator.process(commandTokens);
		feedback = _commandExecutor->execute(command);
	} catch (INVALID_COMMAND_EXCEPTION e) {
		throw std::string(e.what());
	} catch (COMMAND_CREATION_EXCEPTION e) {
		throw std::string(e.what());
	} catch (COMMAND_EXECUTION_EXCEPTION e) {
		throw std::string(e.what());
	}
	return feedback;
}

Logic::~Logic() {
	delete _commandExecutor;
}