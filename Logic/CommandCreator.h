#ifndef COMMAND_CREATOR_H
#define COMMAND_CREATOR_H

#include <cstdio>
#include "StorageHandler.h"


const std::string MESSAGE_INVALID = "Invalid command line. Please key in another command";
const std::string MESSAGE_ADD_SUCCESS = "\"%s\" have been added succesfully.\nStart Date Time: %s\nEnd Date Time: %s"; 
const std::string MESSAGE_ADD_EMPTY = "Task text cannot be empty.";

class Command {
protected:
	PrimaryCommandType _type1;
	SecondaryCommandType _type2;
public:
	Command(PrimaryCommandType type) {
		_type1 = type;
	}

	PrimaryCommandType getPrimaryCommandType() {
		return _type1;
	}

	SecondaryCommandType getSecondaryCommandType() {
		return _type2;
	}

	bool isValid() {
		if (_type1 == PrimaryCommandType::Invalid) {
			return false;
		} else {
			return true;
		}
	}

	virtual UIFeedback execute(StorageHandler* a) = 0;
};

class InvalidCommand: public Command {
public:
	InvalidCommand () : Command(PrimaryCommandType::Invalid) {
	}

	UIFeedback execute(StorageHandler* storageHandler) {
		UIFeedback feedback(storageHandler->getAllTask(), MESSAGE_INVALID);
		return feedback;
	}
};

class AddCommand: public Command {
private:
	Task _task;

public:
	AddCommand (SecondaryCommandType type2, Task task) : Command(PrimaryCommandType::Add) {
		_type2 = type2;
		_task = task;
	}

	UIFeedback Command::execute(StorageHandler* storageHandler) {
		UIFeedback* feedback;
		if (_task.getTaskText().size() < 1) {
			feedback = new UIFeedback(storageHandler->getAllTask(), MESSAGE_ADD_EMPTY);
		} else {
			storageHandler->add(_task);
			std::string taskText = _task.getTaskText();
			std::string startDateTime = boost::posix_time::to_simple_string(_task.getStartDateTime());
			std::string endDateTime = boost::posix_time::to_simple_string(_task.getEndDateTime());
			char buffer[255];
			sprintf_s(buffer, MESSAGE_ADD_SUCCESS.c_str(), taskText, startDateTime, endDateTime);
			feedback = new UIFeedback(storageHandler->getAllTask(), std::string(buffer));
		}
		return *feedback;
	}

	bool isValid() {
		if (_type2 == SecondaryCommandType::None) {
			return false;
		} else {
			return Command::isValid();
		}
	}

	Task getTask() {
		return _task;
	}

};

class CommandCreator {
private:
	static Command* processByPrimaryCommandType(CommandTokens commandTokens) {
		PrimaryCommandType command1 = commandTokens.getPrimaryCommand();
		Command* returnCommand = NULL;
		switch (command1) {
		case PrimaryCommandType::Add:
			returnCommand = new AddCommand(processAddCommand(commandTokens));
			break;
		case PrimaryCommandType::Invalid:
			returnCommand = new InvalidCommand();
			break;
		}
		return returnCommand;
	}

	static AddCommand processAddCommand(CommandTokens commandTokens) {
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

		return *returnCommand;
	}
public:
	CommandCreator() {
	}

	Command* process(CommandTokens commandTokens) {
		return processByPrimaryCommandType(commandTokens);
	}

#ifdef TESTMODE

	AddCommand testProcessAddCommand(CommandTokens commandTokens) {
		return processAddCommand(commandTokens);
	}

#endif
};

#endif