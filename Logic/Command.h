#pragma once

#include <cstdio>
#include "RunTimeStorage.h"
using namespace API;

class COMMAND_EXECUTION_EXCEPTION : public std::exception {
public:
	explicit COMMAND_EXECUTION_EXCEPTION(const char* e);

	explicit COMMAND_EXECUTION_EXCEPTION(std::string errorMessage);
};

//abstract parent class for command supported. 
class Command {
protected:
	CommandTokens::PrimaryCommandType _type1;
	CommandTokens::SecondaryCommandType _type2;
	RunTimeStorage* _runTimeStorageExecuted;
	bool _statusExecuted;
public:
	Command(CommandTokens::PrimaryCommandType type);
	CommandTokens::PrimaryCommandType getPrimaryCommandType(void);
	CommandTokens::SecondaryCommandType getSecondaryCommandType(void);
	bool isValid(void);
	bool isExecuted(void);
	RunTimeStorage* getRunTimeStorageExecuted();
	virtual UIFeedback execute(RunTimeStorage* a) = 0;
	virtual UIFeedback undo(void) = 0;
	virtual bool canUndo(void) = 0;
	~Command() {}
};