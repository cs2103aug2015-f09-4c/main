#pragma once

#include <cstdio>
#include "..\Parser\Parser.h"
#include "..\Logger\Logger.h"
#include "CommandHeader.h"

const std::string MESSAGE_INVALID_COMMAND = "Invalid Command. No change is made.";
const std::string MESSAGE_NON_POSITIVE_INDEX = "Only positive index is allowed. No change is made.";
const std::string MESSAGE_INVALID_DATE_TIME = "Invalid date time is found. Please use the following format for date time : dd-mm-yyyy hhmm";

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

	static ExportCommand* processExportCommand(CommandTokens commandTokens);
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