#ifndef COMMAND_H_
#define COMMAND_H_

#include "StorageHandler.h"
using namespace API;

//abstract parent class for command supported. 
class Command {
protected:
	PrimaryCommandType _type1;
	SecondaryCommandType _type2;

	StorageHandler* _storageHandlerExecuted;
	bool _statusExecuted;
public:
	Command(PrimaryCommandType type);
	PrimaryCommandType getPrimaryCommandType(void);
	SecondaryCommandType getSecondaryCommandType(void);
	bool isValid(void);
	bool isExecutedSuccessfully(void);
	virtual UIFeedback execute(StorageHandler* a) = 0;
	virtual UIFeedback undo(void) = 0;
	virtual bool canUndo(void) = 0;
	~Command() {}
};
#endif