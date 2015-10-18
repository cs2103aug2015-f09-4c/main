#pragma once

#include <cstdio>
#include "..\Parser\Parser.h"
#include "..\Logger\Logger.h"
#include "CommandHeader.h"

const std::string MESSAGE_NON_POSITIVE_INDEX = "Only positive index is allowed. No change is made.";

class INVALID_COMMAND_EXCEPTION : public std::exception{
public:
	explicit INVALID_COMMAND_EXCEPTION(std::string message);
};

class CommandCreator {
private:
	static Logger* logger;

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