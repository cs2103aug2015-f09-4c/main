#pragma once

#include "RunTimeStorage.h"
using namespace API;

//abstract parent class for command supported. 
class Command {
protected:
	PrimaryCommandType _type1;
	SecondaryCommandType _type2;
	RunTimeStorage* _runTimeStorageExecuted;
	bool _statusExecuted;
public:
	Command(PrimaryCommandType type);
	PrimaryCommandType getPrimaryCommandType(void);
	SecondaryCommandType getSecondaryCommandType(void);
	bool isValid(void);
	bool isExecuted(void);
	RunTimeStorage* getRunTimeStorageExecuted();
	virtual UIFeedback execute(RunTimeStorage* a) = 0;
	virtual UIFeedback undo(void) = 0;
	virtual bool canUndo(void) = 0;
	~Command() {}
};