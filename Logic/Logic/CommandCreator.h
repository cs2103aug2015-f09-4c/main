#include <cstdio>
#include "Logic.h"
#include "Swiftask.h"

const std::string MESSAGE_ADD = "\"%s\" have been added succesfully.\nStart Date Time: %s\nEnd Date Time: %s"; 


virtual class Command {
private:

public:
	Command();
	UIFeedback executeCommand(StorageHandler);
};

class addCommand: public Command {
private:
	Task task;
	static buffer[255];
public:
	Command::executeCommand(StorageHandler storageHandler) {
		storageHandler.add(task);
		std::string taskText = task.getTaskText();
		std::string startDateTime = task.getStartDateTime();
		std::string endDateTime = task.getEndDateTime();
		std::sprintf(buffer, MESSAGE_ADD.c_str(), taskText, startDateTime, endDateTime);
		UIFeedback feedback(storageHandler.getAllTask(), std::string(buffer));
		return feedback;
	}
};


class CommandCreator {
private:

public:
	CommandCreator() {
	}

	Command process(CommandTokens commandTokens) {
		
	}
};