#pragma once

#include "Command.h"

const std::string MESSAGE_SEARCH_SUCCESS = "%i task(s) have been found.";
const std::string MESSAGE_NO_TASK_FOUND = "There is no task fulfilling the search criteria.";

class SearchCommand : public Command {
protected:
	std::vector<Task> _searchResult;
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
public:
	SearchStartBeforeCommand(ptime);
	UIFeedback SearchStartCommand::execute(RunTimeStorage*);
	virtual ~SearchStartBeforeCommand(void);
};

class SearchStartAfterCommand : public SearchStartCommand {
public:
	SearchStartAfterCommand(ptime);
	UIFeedback SearchStartCommand::execute(RunTimeStorage*);
	virtual ~SearchStartAfterCommand(void);
};

class SearchEndCommand : public SearchCommand {
protected:
	ptime _end;
public:
	SearchEndCommand(ptime);
	virtual UIFeedback SearchCommand::execute(RunTimeStorage*) = 0;
	virtual ~SearchEndCommand(void);
};

class SearchEndBeforeCommand : public SearchEndCommand {
public:
	SearchEndBeforeCommand(ptime);
	UIFeedback SearchEndCommand::execute(RunTimeStorage*);
	virtual ~SearchEndBeforeCommand(void);
};

class SearchEndAfterCommand : public SearchEndCommand {
public:
	SearchEndAfterCommand(ptime);
	UIFeedback SearchEndCommand::execute(RunTimeStorage*);
	virtual ~SearchEndAfterCommand(void);
};

class SearchTagCommand : public SearchCommand {
private:
	std::set<std::string> _tags;
public:
	SearchTagCommand(std::vector<std::string> tags);
	UIFeedback SearchCommand::execute(RunTimeStorage*);
	virtual ~SearchTagCommand(void);
};