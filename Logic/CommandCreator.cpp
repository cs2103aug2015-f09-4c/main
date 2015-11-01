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
		case CommandTokens::PrimaryCommandType::MarkAsComplete:
			returnCommand = processSetCompleteCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Export:
			returnCommand = processExportCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Import:
			returnCommand = processImportCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Refresh:
			returnCommand = processRefreshCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Tag:
			returnCommand = processTagCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Untag:
			returnCommand = processUntagCommand(commandTokens);
			break;
		case CommandTokens::PrimaryCommandType::Search:
			returnCommand = processSearchCommand(commandTokens);
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
		case CommandTokens::SecondaryCommandType::By:
			task = Task(taskName,commandTokens.getEndDateTime());
			for (size_t i = 0 ; i < tags.size() ; ++i) {
				task.addTag(tags[i]);
			}
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::By,task);
			break;
		case CommandTokens::SecondaryCommandType::FromTo:
			task = Task(taskName,commandTokens.getStartDateTime(), commandTokens.getEndDateTime());
			for (size_t i = 0 ; i < tags.size() ; ++i) {
				task.addTag(tags[i]);
			}
			returnCommand = new AddCommand(CommandTokens::SecondaryCommandType::FromTo, task);
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

	ptime startDateTime = commandTokens.getStartDateTime();
	ptime endDateTime = commandTokens.getEndDateTime();
	try{
		switch (command2) {
		case CommandTokens::SecondaryCommandType::Index:
			returnCommand = processDeleteIndexCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::All:
			returnCommand = processDeleteAllCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::By:
			returnCommand = processDeleteBeforeCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::FromTo:
			returnCommand = processDeleteFromToCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::Completed:
			returnCommand = processDeleteCompleteCommand(commandTokens);
			break;
		default:
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
		}
	} catch (INVALID_COMMAND_EXCEPTION e) {
		throw e;
	}
	return returnCommand;
}

DeleteIndexCommand* CommandCreator::processDeleteIndexCommand(CommandTokens commandTokens) {
	DeleteIndexCommand* returnCommand = NULL;
	int index = commandTokens.getIndex(); 
	if (index < 1) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
	} else {
		returnCommand = new DeleteIndexCommand(index);
	}
	return returnCommand;
}

DeleteBeforeCommand* CommandCreator::processDeleteBeforeCommand(CommandTokens commandTokens) {
	DeleteBeforeCommand* returnCommand = NULL;
	ptime endDateTime = commandTokens.getEndDateTime();
	if (endDateTime.is_special()) {
		throw INVALID_COMMAND_EXCEPTION (MESSAGE_INVALID_DATE_TIME);
	}
	returnCommand = new DeleteBeforeCommand(endDateTime);
	return returnCommand;
}

DeleteFromToCommand* CommandCreator::processDeleteFromToCommand(CommandTokens commandTokens) {
	DeleteFromToCommand* returnCommand = NULL;
	ptime startDateTime = commandTokens.getStartDateTime();
	ptime endDateTime = commandTokens.getEndDateTime();
	if (startDateTime.is_special() || endDateTime.is_special()) {
		throw INVALID_COMMAND_EXCEPTION (MESSAGE_INVALID_DATE_TIME);
	} else if (startDateTime > endDateTime) {
		throw INVALID_COMMAND_EXCEPTION (MESSAGE_END_LESS_THAN_START);
	}
	returnCommand = new DeleteFromToCommand(startDateTime, endDateTime);
	return returnCommand;
}

DeleteAllCommand* CommandCreator::processDeleteAllCommand(CommandTokens commandTokens) {
	DeleteAllCommand* returnCommand = new DeleteAllCommand();
	return returnCommand;
}

DeleteCompleteCommand* CommandCreator::processDeleteCompleteCommand(CommandTokens commandTokens) {
	DeleteCompleteCommand* returnCommand = new DeleteCompleteCommand();
	return returnCommand;
}

EditCommand* CommandCreator::processEditCommand(CommandTokens commandTokens) {
	EditCommand* returnCommand = NULL;
	CommandTokens::SecondaryCommandType command2 = commandTokens.getSecondaryCommand();

	try {
		switch (command2) {
		case CommandTokens::SecondaryCommandType::Name:
			returnCommand = processEditNameCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::Start:
			returnCommand = processEditStartCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::End:
			returnCommand = processEditEndCommand(commandTokens);
			break;
		default:
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
		}
	} catch (INVALID_COMMAND_EXCEPTION e) {
		throw e;
	}
	return returnCommand;
}

EditNameCommand* CommandCreator::processEditNameCommand(CommandTokens commandTokens) {
	EditNameCommand* returnCommand = NULL;
	int index = commandTokens.getIndex();
	if (index < 1) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
	}
	std::string newName = commandTokens.getTaskName();
	if (newName.empty()) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_EDIT_NAME_EMPTY);
	} else {
		returnCommand = new EditNameCommand(index, newName);
	}
	return returnCommand;
}

EditStartCommand* CommandCreator::processEditStartCommand(CommandTokens commandTokens) {
	EditStartCommand* returnCommand = NULL;
	int index = commandTokens.getIndex();
	if (index < 1) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
	}
	ptime newStart = commandTokens.getStartDateTime();
	returnCommand = new EditStartCommand(index, newStart);
	return returnCommand;
}

EditEndCommand* CommandCreator::processEditEndCommand(CommandTokens commandTokens) {
	EditEndCommand* returnCommand = NULL;
	int index = commandTokens.getIndex();
	if (index < 1) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
	}
	ptime newEnd = commandTokens.getEndDateTime();
	returnCommand = new EditEndCommand(index, newEnd);
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

ImportCommand* CommandCreator::processImportCommand(CommandTokens commandTokens) {
	std::string filePath = commandTokens.getOtherCommandParameter();
	ImportCommand* returnCommand = new ImportCommand(filePath);
	return returnCommand;
}

RefreshCommand* CommandCreator::processRefreshCommand(CommandTokens commandTokens) {
	RefreshCommand* returnCommand = new RefreshCommand();
	return returnCommand;
}

TagCommand* CommandCreator::processTagCommand(CommandTokens commandTokens) {
	int index = commandTokens.getIndex();
	if (index < 1) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
	}
	std::vector<std::string> tags = commandTokens.getTags();
	TagCommand* returnCommand = new TagCommand(index, tags);
	return returnCommand;
}

UntagCommand* CommandCreator::processUntagCommand(CommandTokens commandTokens) {
	int index = commandTokens.getIndex();
	if (index < 1) {
		throw INVALID_COMMAND_EXCEPTION(MESSAGE_NON_POSITIVE_INDEX);
	}
	std::vector<std::string> untags = commandTokens.getTags();
	UntagCommand* returnCommand = new UntagCommand(index, untags);
	return returnCommand;
}

SearchCommand* CommandCreator::processSearchCommand(CommandTokens commandTokens) {
	CommandTokens::SecondaryCommandType type2 = commandTokens.getSecondaryCommand();
	SearchCommand* returnCommand;
	try {
		switch (type2) {
		case CommandTokens::SecondaryCommandType::StartBefore:
			returnCommand = processSearchStartBeforeCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::StartAfter:
			returnCommand = processSearchStartAfterCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::EndBefore:
			returnCommand = processSearchEndBeforeCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::EndAfter:
			returnCommand = processSearchEndAfterCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::Tags:
			returnCommand = processSearchTagsCommand(commandTokens);
			break;
		case CommandTokens::SecondaryCommandType::Name:
			returnCommand = processSearchNameCommand(commandTokens);
			break;
		default:
			throw INVALID_COMMAND_EXCEPTION(MESSAGE_INVALID_COMMAND);
		}
	} catch (INVALID_COMMAND_EXCEPTION e) {
		throw e;
	}

	return returnCommand;
}

SearchStartBeforeCommand* CommandCreator::processSearchStartBeforeCommand(CommandTokens commandTokens) {
	SearchStartBeforeCommand* returnCommand;
	ptime start = commandTokens.getStartDateTime();
	returnCommand = new SearchStartBeforeCommand(start);
	return returnCommand;
}

SearchStartAfterCommand* CommandCreator::processSearchStartAfterCommand(CommandTokens commandTokens) {
	SearchStartAfterCommand* returnCommand;
	ptime start = commandTokens.getStartDateTime();
	returnCommand = new SearchStartAfterCommand(start);
	return returnCommand;
}

SearchEndBeforeCommand* CommandCreator::processSearchEndBeforeCommand(CommandTokens commandTokens) {
	SearchEndBeforeCommand* returnCommand;
	ptime end = commandTokens.getEndDateTime();
	returnCommand = new SearchEndBeforeCommand(end);
	return returnCommand;
}

SearchEndAfterCommand* CommandCreator::processSearchEndAfterCommand(CommandTokens commandTokens) {
	SearchEndAfterCommand* returnCommand;
	ptime end = commandTokens.getEndDateTime();
	returnCommand = new SearchEndAfterCommand(end);
	return returnCommand;
}

SearchTagsCommand* CommandCreator::processSearchTagsCommand(CommandTokens commandTokens) {
	SearchTagsCommand* returnCommand;
	std::vector<std::string> tags = commandTokens.getTags();
	returnCommand = new SearchTagsCommand(tags);
	return returnCommand;
}

SearchNameCommand* CommandCreator::processSearchNameCommand(CommandTokens commandTokens) {
	SearchNameCommand* returnCommand;
	std::string searchString = commandTokens.getTaskName();
	returnCommand = new SearchNameCommand(searchString);
	return returnCommand;
}

CommandCreator::CommandCreator() {
}

Command* CommandCreator::process(CommandTokens commandTokens) {
	Command* returnCommand;
	try {
		returnCommand = processByPrimaryCommandType(commandTokens);
	} catch (INVALID_COMMAND_EXCEPTION e) {
		throw e;
	} catch (COMMAND_CREATION_EXCEPTION e) {
		throw e;
	}
	return returnCommand;
}