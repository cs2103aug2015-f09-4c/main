#include "CommandCreator.h"

Command* CommandCreator::processByPrimaryCommandType(CommandTokens commandTokens) {
	PrimaryCommandType command1 = commandTokens.getPrimaryCommand();
	Command* returnCommand = NULL;
	switch (command1) {
	case PrimaryCommandType::Add:
		returnCommand = processAddCommand(commandTokens);
		break;
	case PrimaryCommandType::Delete:
		returnCommand = processDeleteCommand(commandTokens);
		break;
	case PrimaryCommandType::Invalid:
		returnCommand = new InvalidCommand();
		break;
	}
	return returnCommand;
}

AddCommand* CommandCreator::processAddCommand(CommandTokens commandTokens) {
	AddCommand* returnCommand = NULL;
	SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	Task* task = NULL;
	switch (command2) {
	case SecondaryCommandType::Floating:
		task = new Task((commandTokens.getDetails())[0]);
		returnCommand = new AddCommand(SecondaryCommandType::Floating,*task);
		break;
	case SecondaryCommandType::Todo:
		task = new Task((commandTokens.getDetails())[0],commandTokens.getEndDateTime());
		returnCommand = new AddCommand(SecondaryCommandType::Todo,*task);
		break;
	case SecondaryCommandType::Timed:
		task = new Task((commandTokens.getDetails())[0],commandTokens.getStartDateTime(), commandTokens.getEndDateTime());
		returnCommand = new AddCommand(SecondaryCommandType::Timed, *task);
		break;
	case SecondaryCommandType::None:
		returnCommand = new AddCommand(SecondaryCommandType::None, *task);
	}
	return returnCommand;
}

DeleteCommand* CommandCreator::processDeleteCommand(CommandTokens commandTokens) {
	DeleteCommand* returnCommand = NULL;
	SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
	std::vector<std::string> details = commandTokens.getDetails(); 
	switch (command2) {
	case SecondaryCommandType::Index:
		if (std::stoi(details[0]) < 1) {
			returnCommand = new InvalidDeleteCommand();
		} else {
			size_t index = std::stoi(details[0]); 
			returnCommand = new IndexDeleteCommand(index);
		}
		break;
	}
	return returnCommand;
}



CommandCreator::CommandCreator() {
}

Command* CommandCreator::process(CommandTokens commandTokens) {
	return processByPrimaryCommandType(commandTokens);
}