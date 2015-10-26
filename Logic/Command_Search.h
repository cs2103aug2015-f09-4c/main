#pragma once

#include "Command.h"

const std::string MESSAGE_SEARCH_SUCCESS = "%i task(s) have been found.";
const std::string MESSAGE_NO_TASK_FOUND = "There is no task fulfilling the search criteria.";

class SearchCommand : public Command {
public:
	SearchCommand(void);
	virtual UIFeedback Command::execute(RunTimeStorage*) = 0;
	UIFeedback Command::undo();
	bool canUndo();
	virtual ~SearchCommand(void);
};

class SearchStartCommand : public SearchCommand {
protected:
	ptime _start;
public:
	SearchStartCommand(ptime);
	virtual UIFeedback SearchCommand::execute(RunTimeStorage*) = 0;
	virtual ~SearchStartCommand(void);
};

class SearchStartBeforeCommand : public SearchStartCommand {
private:
	bool isBefore(ptime time) {
		//Special date time is not valid for comparison.
		if (time.is_special()) {
			return false;
		} else {
			return time < _start;
		}
	}
public:
	SearchStartBeforeCommand(ptime);
	UIFeedback SearchStartCommand::execute(RunTimeStorage*);
	virtual ~SearchStartBeforeCommand(void);
};

