#ifndef COMMAND_H_
#define COMMAND_H_

#include "StorageHandler.h"
using namespace API;

const std::string MESSAGE_INVALID = "Invalid command line. Please key in another command";

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
		UIFeedback feedback(storageHandler->getAllTasks(), MESSAGE_INVALID);
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
			feedback = new UIFeedback(storageHandler->getAllTasks(), MESSAGE_ADD_EMPTY);
		} else {
			std::string feedbackMessage = storageHandler->add(_task);
			feedback = new UIFeedback(storageHandler->getAllTasks(), feedbackMessage);
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

#endif