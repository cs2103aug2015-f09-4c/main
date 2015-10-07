#ifndef COMMAND_H_
#define COMMAND_H_

#include "StorageHandler.h"
using namespace API;

//Feedback message for invalid command type
const std::string MESSAGE_INVALID_COMMAND = "Invalid Command. No change is made.";

class Command {
protected:
	PrimaryCommandType _type1;
	SecondaryCommandType _type2;
	bool _statusExecuted;
public:
	Command(PrimaryCommandType type);
	PrimaryCommandType getPrimaryCommandType();
	SecondaryCommandType getSecondaryCommandType();
	bool isValid();
	bool isExecutedSuccessfully();
	virtual UIFeedback execute(StorageHandler* a) = 0;
	~Command() {}
};
#endif