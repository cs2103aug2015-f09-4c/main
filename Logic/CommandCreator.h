#pragma once

#include <cstdio>
#include "..\Parser\Parser.h"
#include "CommandHeader.h"

class INVALID_COMMAND_EXCEPTION : public std::exception{
	std::string _message;

public:
	INVALID_COMMAND_EXCEPTION(std::string message) : std::exception() {
		_message = message;
	}

	const char* what() const throw() {
		return _message.c_str();
	}
};

class CommandCreator {
private:
	static Command* processByPrimaryCommandType(CommandTokens commandTokens);

	static AddCommand* processAddCommand(CommandTokens commandTokens);

	static DeleteCommand* processDeleteCommand(CommandTokens commandTokens);

	static EditCommand* processEditCommand(CommandTokens commandTokens);

	static SetCompleteCommand* processSetCompleteCommand(CommandTokens commandTokens);
public:
	CommandCreator();
	Command* process(CommandTokens commandTokens);

	//Methods below are for unit testing which allows private method to be called when TESTMODE is defined

#ifdef TESTMODE

	AddCommand* testProcessAddCommand(CommandTokens commandTokens) {
		return processAddCommand(commandTokens);
	}

	DeleteCommand* testProcessDeleteCommand(CommandTokens commandTokens) {
		return processDeleteCommand(commandTokens);
	}

	EditCommand* testProcessEditCommand(CommandTokens commandTokens) {
		return processEditCommand(commandTokens);
	}

#endif
};