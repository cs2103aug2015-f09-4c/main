#include "CommandCreator.h"

Command* CommandCreator::processByPrimaryCommandType(CommandTokens commandTokens) {
	CommandTokens::PrimaryCommandType command1 = commandTokens.getPrimaryCommand();
	Command* returnCommand = NULL;
	try {
		switch (command1) {
		case CommandTokens::PrimaryCommandType::Add:
			returnCommand = processAddCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Delete:
			returnCommand = processDeleteCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Edit:
			returnCommand = processEditCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Complete:
			returnCommand = processSetCompleteCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Invalid:
			returnCommand = new InvalidCommand(MESSAGE_INVALID_COMMAND);
			break;
		default:
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
		}
	} catch (INVALID_COMMAND_EXCEPTION e) {
		returnCommand = new InvalidCommand(e.what());
	}

	return returnCommand;
}

AddCommand* CommandCreator::processAddCommand(CommandTokens commandTokens) {
	AddCommand* returnCommand = NULL;
	CommandTokens::SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	Task task;

	std::string taskName = commandTokens.getTaskName();
	try {
		switch (command2) {
		case CommandTokens::SecondaryCommandType::Floating:
			task = Task(taskName);
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::Floating,task);
			break;
		case CommandTokens::SecondaryCommandType::Todo:
			task = Task(taskName,commandTokens.getEndDateTime());
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::Todo,task);
			break;
		case CommandTokens::SecondaryCommandType::Timed:
			task = Task(taskName,commandTokens.getStartDateTime(), commandTokens.getEndDateTime());
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::Timed, task);
			break;
		case CommandTokens::SecondaryCommandType::None:
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::None, task);
		}
	} catch (std::exception e) {
		throw e;
	}
	return returnCommand;
}

DeleteCommand* CommandCreator::processDeleteCommand(CommandTokens commandTokens) {
	DeleteCommand* returnCommand = NULL;
	CommandTokens::SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	int index = commandTokens.getIndex(); 

	switch (command2) {
	case CommandTokens::SecondaryCommandType::Index:
		if (index < 1) {
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
		} else {
			returnCommand = new IndexDeleteCommand(index);
		}
		break;
	case CommandTokens::SecondaryCommandType::All:
		returnCommand = new DeleteAllCommand();
		break;
	default:
		throw std::exception(MESSAGE_INVALID_COMMAND.c_str());
	}
	return returnCommand;
}

EditCommand* CommandCreator::processEditCommand(CommandTokens commandTokens) {
	EditCommand* returnCommand = NULL;
	CommandTokens::SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	int index = commandTokens.getIndex();

	if (index < 1) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
	}

	std::string newName = commandTokens.getTaskName();
	boost::posix_time::ptime newStart = commandTokens.getStartDateTime();
	boost::posix_time::ptime newEnd = commandTokens.getEndDateTime();
	try {
		switch (command2) {
		case CommandTokens::SecondaryCommandType::Name:
			if (newName.empty()) {
				throw INVALID_COMMAND_EXCEPTION(MESSAGE_EDIT_NAME_EMPTY);
			} else {
				returnCommand = new EditNameCommand(index, newName);
			}
			break;
		case CommandTokens::SecondaryCommandType::Start:
			returnCommand = new EditStartCommand(index, newStart);
			break;
		case CommandTokens::SecondaryCommandType::End:
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
	CommandTokens::SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	int index = commandTokens.getIndex();
	switch (command2) {
	case CommandTokens::SecondaryCommandType::Index:
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
	return processByPrimaryCommandType(commandTokens);
}