//@@author A0112218W
#pragma once

#include <cstdio>
#include "..\Parser\Parser.h"
#include "..\Logger\Logger.h"
#include "CommandHeader.h"

const std::string MESSAGE_INVALID_COMMAND = "Invalid Command. No change is made.";
const std::string MESSAGE_NON_POSITIVE_INDEX = "Only positive index is allowed. No change is made.";
const std::string MESSAGE_INVALID_DATE_TIME = "Invalid date time is found. Please use the following format for date time : dd-mm-yyyy hhmm";

const std::string ASCENDING_ORDER = "Ascending";
const std::string DESCENDING_ORDER = "Descending";

class INVALID_COMMAND_EXCEPTION : public std::exception{
public:
	explicit INVALID_COMMAND_EXCEPTION(std::string message);
};

class CommandCreator {
private:
	static Logger* logger;

	static Command* processByPrimaryCommandType(CommandTokens);

	static AddCommand* processAddCommand(CommandTokens);

	static ConfigureSaveLocationCommand* processConfigureCommand(CommandTokens);

	static DeleteCommand* processDeleteCommand(CommandTokens);
	static DeleteIndexCommand* processDeleteIndexCommand(CommandTokens);
	static DeleteBeforeCommand* processDeleteBeforeCommand(CommandTokens);
	static DeleteFromToCommand* processDeleteFromToCommand(CommandTokens);
	static DeleteAllCommand* processDeleteAllCommand(CommandTokens);
	static DeleteCompleteCommand* processDeleteCompleteCommand(CommandTokens);

	static DisplayCommand* processDisplayCommand(CommandTokens);

	static EditCommand* processEditCommand(CommandTokens);
	static EditNameCommand* processEditNameCommand(CommandTokens);
	static EditStartCommand* processEditStartCommand(CommandTokens);
	static EditEndCommand* processEditEndCommand(CommandTokens);

	static ExportCommand* processExportCommand(CommandTokens);

	static ImportCommand* processImportCommand(CommandTokens);

	static RefreshCommand* processRefreshCommand(CommandTokens);

	static SearchCommand* processSearchCommand(CommandTokens);
	static SearchStartBeforeCommand* processSearchStartBeforeCommand(CommandTokens);
	static SearchStartAfterCommand* processSearchStartAfterCommand(CommandTokens);
	static SearchEndBeforeCommand* processSearchEndBeforeCommand(CommandTokens);
	static SearchEndAfterCommand* processSearchEndAfterCommand(CommandTokens);
	static SearchTagsCommand* processSearchTagsCommand(CommandTokens);
	static SearchNameCommand* processSearchNameCommand(CommandTokens);

	static SetCompleteCommand* processSetCompleteCommand(CommandTokens);

	static SortCommand* processSortCommand(CommandTokens);

	static TagCommand* processTagCommand(CommandTokens);

	static UntagCommand* processUntagCommand(CommandTokens);
public:
	CommandCreator();
	Command* process(CommandTokens);

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