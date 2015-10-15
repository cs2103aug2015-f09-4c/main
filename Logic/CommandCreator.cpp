#include "CommandCreator.h"

Logger* CommandCreator::logger = Logger::getInstance();

Command* CommandCreator::processByPrimaryCommandType(CommandTokens commandTokens) {
	PrimaryCommandType command1 = commandTokens.getPrimaryCommand();
	Command* returnCommand = NULL;
	try {
		switch (command1) {
		case PrimaryCommandType::Add:
			logger->logINFO("Command type: Add");
			returnCommand = processAddCommand(commandTokens);
			break;
		case PrimaryCommandType::Delete:
			logger->logINFO("Command type: Delete");
			returnCommand = processDeleteCommand(commandTokens);
			break;
		case PrimaryCommandType::Edit:
			logger->logINFO("Command type: Edit");
			returnCommand = processEditCommand(commandTokens);
			break;
		case PrimaryCommandType::Complete:
			logger->logINFO("Command type: Complete");
			returnCommand = processSetCompleteCommand(commandTokens);
			break;
		case PrimaryCommandType::Undo:
			logger->logINFO("Command type: Undo");
			returnCommand = new UndoCommand();
			break;
		case PrimaryCommandType::Invalid:
			logger->logINFO("Command type: Invalid");
			returnCommand = new InvalidCommand(MESSAGE_INVALID_COMMAND);
			break;
		default:
			logger->logERROR("Unsupported command type. Create Invalid Command.");
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
		}
	} catch (INVALID_COMMAND_EXCEPTION e) {
		returnCommand = new InvalidCommand(e.what());
	}

	return returnCommand;
}

AddCommand* CommandCreator::processAddCommand(CommandTokens commandTokens) {
	AddCommand* returnCommand = NULL;
	SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	Task task;

	std::string taskName = commandTokens.getTaskName();
	try {
		switch (command2) {
		case SecondaryCommandType::Floating:
			task = Task(taskName);
			returnCommand = new AddCommand(SecondaryCommandType::Floating,task);
			break;
		case SecondaryCommandType::Todo:
			task = Task(taskName,commandTokens.getEndDateTime());
			returnCommand = new AddCommand(SecondaryCommandType::Todo,task);
			break;
		case SecondaryCommandType::Timed:
			task = Task(taskName,commandTokens.getStartDateTime(), commandTokens.getEndDateTime());
			returnCommand = new AddCommand(SecondaryCommandType::Timed, task);
			break;
		case SecondaryCommandType::None:
			returnCommand = new AddCommand(SecondaryCommandType::None, task);
		}
	} catch (std::exception e) {
		throw e;
	}
	return returnCommand;
}

DeleteCommand* CommandCreator::processDeleteCommand(CommandTokens commandTokens) {
	DeleteCommand* returnCommand = NULL;
	SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	int index = commandTokens.getIndex(); 

	switch (command2) {
	case SecondaryCommandType::Index:
		if (index < 1) {
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
		} else {
			returnCommand = new IndexDeleteCommand(index);
		}
		break;
	}
	return returnCommand;
}

EditCommand* CommandCreator::processEditCommand(CommandTokens commandTokens) {
	EditCommand* returnCommand = NULL;
	SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	int index = commandTokens.getIndex();

	if (index < 1) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
	}

	std::string newName = commandTokens.getTaskName();
	boost::posix_time::ptime newStart = commandTokens.getStartDateTime();
	boost::posix_time::ptime newEnd = commandTokens.getEndDateTime();
	try {
		switch (command2) {
		case SecondaryCommandType::Name:
			if (newName.empty()) {
				throw INVALID_COMMAND_EXCEPTION(MESSAGE_EDIT_NAME_EMPTY);
			} else {
				returnCommand = new EditNameCommand(index, newName);
			}
			break;
		case SecondaryCommandType::Start:
			returnCommand = new EditStartCommand(index, newStart);
			break;
		case SecondaryCommandType::End:
			returnCommand = new EditEndCommand(index, newEnd);
			break;
		default:
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
		}
	} catch (std::exception e) {
		throw e;
	}
	return returnCommand;
}

SetCompleteCommand* CommandCreator::processSetCompleteCommand(CommandTokens commandTokens) {
	SetCompleteCommand* returnCommand = NULL;
	SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	int index = commandTokens.getIndex();
	switch (command2) {
	case SecondaryCommandType::Index:
		if (index < 1) {
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
		} else {
			returnCommand = new SetCompleteCommand(index);
		}
		break;
	default:
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
	}
	return returnCommand;
}

CommandCreator::CommandCreator() {
}

Command* CommandCreator::process(CommandTokens commandTokens) {

	logger->logTRACE("Creating Command Object");
	return processByPrimaryCommandType(commandTokens);
}