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

	static DeleteIndexCommand* processDeleteIndexCommand(CommandTokens commandTokens);
	static DeleteBeforeCommand* processDeleteBeforeCommand(CommandTokens commandTokens);
	static DeleteFromToCommand* processDeleteFromToCommand(CommandTokens commandTokens);
	static DeleteAllCommand* processDeleteAllCommand(CommandTokens commandTokens);

	static EditCommand* processEditCommand(CommandTokens commandTokens);

	static EditNameCommand* processEditNameCommand(CommandTokens commandTokens);
	static EditStartCommand* processEditStartCommand(CommandTokens commandTokens);
	static EditEndCommand* processEditEndCommand(CommandTokens commandTokens);

	static SetCompleteCommand* processSetCompleteCommand(CommandTokens commandTokens);

	static ExportCommand* processExportCommand(CommandTokens commandTokens);

	static RefreshCommand* processRefreshCommand(CommandTokens commandTokens);

	static TagCommand* processTagCommand(CommandTokens commandTokens);

	static UntagCommand* processUntagCommand(CommandTokens commandTokens);
public:
	CommandCreator();
	Command* process(CommandTokens commandTokens);

	//Methods below are for unit testing which allows private method to be called when TESTMODE is defined

#ifdef TESTMODE

	AddCommand* testProcessAddCommand(CommandTokens commandTokens) {
		return processAddCommand(commandTokens);
	}

	DeleteIndexCommand* testProcessDeleteIndexCommand(CommandTokens commandTokens) {
		return processDeleteIndexCommand(commandTokens);
	}

	DeleteBeforeCommand* testProcessDeleteBeforeCommand(CommandTokens commandTokens) {
		return processDeleteBeforeCommand(commandTokens);
	}

	DeleteFromToCommand* testProcessDeleteFromToCommand(CommandTokens commandTokens) {
		return processDeleteFromToCommand(commandTokens);
	}

	DeleteAllCommand* testProcessDeleteAllCommand(CommandTokens commandTokens) {
		return processDeleteAllCommand(commandTokens);
	}
	
	EditCommand* testProcessEditCommand(CommandTokens commandTokens) {
		return processEditCommand(commandTokens);
	}

	EditNameCommand* testProcessEditNameCommand(CommandTokens commandTokens) {
		return processEditNameCommand(commandTokens);
	}

	EditStartCommand* testProcessEditStartCommand(CommandTokens commandTokens) {
		return processEditStartCommand(commandTokens);
	}

	EditEndCommand* testProcessEditEndCommand(CommandTokens commandTokens) {
		return processEditEndCommand(commandTokens);
	}

#endif
};