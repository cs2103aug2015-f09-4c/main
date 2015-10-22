#include "CommandCreator.h"

INVALID_COMMAND_EXCEPTION::INVALID_COMMAND_EXCEPTION(std::string message) : std::exception(message.c_str()){
}

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
		case CommandTokens::PrimaryCommandType::Export:
			returnCommand = processExportCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Refresh:
			returnCommand = processRefreshCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Invalid:
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
			break;
		default:
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
		}
	} catch (INVALID_COMMAND_EXCEPTION e) {
		throw e;
	} catch (COMMAND_CREATION_EXCEPTION e) {
		throw e;
	}

	return returnCommand;
}

AddCommand* CommandCreator::processAddCommand(CommandTokens commandTokens) {
	AddCommand* returnCommand = NULL;
	CommandTokens::SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	Task task;
	std::vector<std::string> tags = commandTokens.getTags();

	std::string taskName = commandTokens.getTaskName();
	try {
		switch (command2) {
		case CommandTokens::SecondaryCommandType::Floating:
			task = Task(taskName);
			for (size_t i = 0 ; i < tags.size() ; ++i) {
				task.addTag(tags[i]);
			}
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::Floating,task);
			break;
		case CommandTokens::SecondaryCommandType::Todo:
			task = Task(taskName,commandTokens.getEndDateTime());
			for (size_t i = 0 ; i < tags.size() ; ++i) {
				task.addTag(tags[i]);
			}
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::Todo,task);
			break;
		case CommandTokens::SecondaryCommandType::Timed:
			task = Task(taskName,commandTokens.getStartDateTime(), commandTokens.getEndDateTime());
			for (size_t i = 0 ; i < tags.size() ; ++i) {
				task.addTag(tags[i]);
			}
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::Timed, task);
			break;
		default:
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
		}
	} catch (TASK_EXCEPTION e) {
		throw INVALID_COMMAND_EXCEPTION(e.what());
	} catch (INVALID_COMMAND_EXCEPTION e) {
		throw e;
	}
	return returnCommand;
}

DeleteCommand* CommandCreator::processDeleteCommand(CommandTokens commandTokens) {
	DeleteCommand* returnCommand = NULL;
	CommandTokens::SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	int index = commandTokens.getIndex(); 
	boost::posix_time::ptime startDateTime = commandTokens.getStartDateTime();
	boost::posix_time::ptime endDateTime = commandTokens.getEndDateTime();
	switch (command2) {
	case CommandTokens::SecondaryCommandType::Index:
		if (index < 1) {
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
		} else {
			returnCommand = new DeleteIndexCommand(index);
		}
		break;
	case CommandTokens::SecondaryCommandType::All:
		returnCommand = new DeleteAllCommand();
		break;
	case CommandTokens::SecondaryCommandType::Todo:
		if (endDateTime.is_special()) {
			throw INVALID_COMMAND_EXCEPTION (MESSAGE_INVALID_DATE_TIME);
		}
		returnCommand = new DeleteBeforeCommand(endDateTime);
		break;
	case CommandTokens::SecondaryCommandType::Timed:
		if (startDateTime > endDateTime) {
			throw INVALID_COMMAND_EXCEPTION (MESSAGE_END_LESS_THAN_START);
		} else if (startDateTime.is_special() || endDateTime.is_special()) {
			throw INVALID_COMMAND_EXCEPTION (MESSAGE_INVALID_DATE_TIME);
		}
		returnCommand = new DeleteFromToCommand(startDateTime, endDateTime);
		break;
	default:
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
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
	} catch (INVALID_COMMAND_EXCEPTION e) {
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

ExportCommand* CommandCreator::processExportCommand(CommandTokens commandTokens) {
	std::string filePath = commandTokens.getOtherCommandParameter();
	ExportCommand* returnCommand = new ExportCommand(filePath);
	return returnCommand;
}

RefreshCommand* CommandCreator::processRefreshCommand(CommandTokens commandTokens) {
	RefreshCommand* returnCommand = new RefreshCommand();
	return returnCommand;
}

CommandCreator::CommandCreator() {
}

Command* CommandCreator::process(CommandTokens commandTokens) {
	Command* returnCommand;
	try {
		returnCommand = processByPrimaryCommandType(commandTokens);
	} catch (std::exception e) {
		throw e;
	}
	return returnCommand;
}