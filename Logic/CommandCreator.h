#ifndef COMMAND_CREATOR_H
#define COMMAND_CREATOR_H

#include <cstdio>
#include "..\Parser\Parser.h"
#include "Command.h"
;
class CommandCreator {
private:
	static Command* processByPrimaryCommandType(CommandTokens commandTokens);

	static AddCommand* processAddCommand(CommandTokens commandTokens);

	static DeleteCommand* processDeleteCommand(CommandTokens commandTokens);
public:
	CommandCreator();
	Command* process(CommandTokens commandTokens);

#ifdef TESTMODE

	AddCommand* testProcessAddCommand(CommandTokens commandTokens) {
		return processAddCommand(commandTokens);
	}

	DeleteCommand* testProcessDeleteCommand(CommandTokens commandTokens) {
		return processDeleteCommand(commandTokens);
	}

#endif
};

#endif