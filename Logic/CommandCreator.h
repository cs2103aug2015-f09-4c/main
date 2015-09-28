#ifndef COMMAND_CREATOR_H
#define COMMAND_CREATOR_H

#include <cstdio>
#include "Command.h"

class CommandCreator {
private:
	static Command* processByPrimaryCommandType(CommandTokens commandTokens) {
		PrimaryCommandType command1 = commandTokens.getPrimaryCommand();
		Command* returnCommand = NULL;
		switch (command1) {
		case PrimaryCommandType::Add:
			returnCommand = new AddCommand(processAddCommand(commandTokens));
			break;
		case PrimaryCommandType::Invalid:
			returnCommand = new InvalidCommand();
			break;
		}
		return returnCommand;
	}

	static AddCommand processAddCommand(CommandTokens commandTokens) {
		AddCommand* returnCommand = NULL;
		SecondaryCommandType command2 = commandTokens.getSecondaryCommand();
		Task* task = NULL;
		switch (command2) {
		case SecondaryCommandType::Floating:
			task = new Task((commandTokens.getDetails())[0]);
			returnCommand = new AddCommand(SecondaryCommandType::Floating,*task);
			break;
		case SecondaryCommandType::Todo:
			task = new Task((commandTokens.getDetails())[0],commandTokens.getEndDateTime());
			returnCommand = new AddCommand(SecondaryCommandType::Todo,*task);
			break;
		case SecondaryCommandType::Timed:
			task = new Task((commandTokens.getDetails())[0],commandTokens.getStartDateTime(), commandTokens.getEndDateTime());
			returnCommand = new AddCommand(SecondaryCommandType::Timed, *task);
			break;
		case SecondaryCommandType::None:
			returnCommand = new AddCommand(SecondaryCommandType::None, *task);
		}

		return *returnCommand;
	}
public:
	CommandCreator() {
	}

	Command* process(CommandTokens commandTokens) {
		return processByPrimaryCommandType(commandTokens);
	}

#ifdef TESTMODE

	AddCommand testProcessAddCommand(CommandTokens commandTokens) {
		return processAddCommand(commandTokens);
	}

#endif
};

#endif