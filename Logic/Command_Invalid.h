#pragma once
#include "Command.h"

class InvalidCommand: public Command {
private:
	//to specify the reason it is invalid
	std::string _message; 
public:
	InvalidCommand (std::string _message);
	UIFeedback execute(StorageHandler* storageHandler);
};

