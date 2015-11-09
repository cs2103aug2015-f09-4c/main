//@@author A0112218W
#pragma once

#include "Command.h"

const std::string MESSAGE_SEARCH_SUCCESS = "%i task(s) have been found.";
const std::string MESSAGE_NO_TASK_FOUND = "There is no task fulfilling the search criteria.";
const std::string SEARCH_FORMAT_STRING = "(%s)([^ ]*)";

/**
 *	Virtual Command sub class responsible for searching tasks
 */
class SearchCommand : public Command {
protected:
	/**
	 *	Vector responsible to store searchResult
	 */
	std::vector<Task> _searchResult;
public:
	/**
	 *	Constructor
	 */
	SearchCommand(void);
	virtual UIFeedback Command::execute(RunTimeStorage*) = 0;
	UIFeedback Command::undo();

	/**
	 *	Return false all the time.
	 */
	bool canUndo();

	/**
	 *	Destructor.
	 */
	virtual ~SearchCommand(void);
};

/**
 *	Virtual SearchCommand sub class responsible for searching tasks based on start date time.
 */
class SearchStartCommand : public SearchCommand {
protected:
	/**
	 *	Start date time to be used for comparison
	 */
	ptime _start;
public:
	/**
	 *	Constructor.
	 *	@param start Start date time to be used for comparison.
	 */
	SearchStartCommand(ptime start);

	virtual UIFeedback SearchCommand::execute(RunTimeStorage*) = 0;
	
	/**
	 *	Destructor
	 */
	virtual ~SearchStartCommand(void);
};

/**
 *	SearchStartCommand sub class responsible for searching tasks before start date time specified.
 */
class SearchStartBeforeCommand : public SearchStartCommand {
public:
	/**
	 *	Constructor.
	 *	@param start Start date time to be used for comparison.
	 */
	SearchStartBeforeCommand(ptime start);

	/**
	 *	Execution method of SearchStartBeforeCommand
	 *	Search for all tasks before _start
	 */
	UIFeedback SearchStartCommand::execute(RunTimeStorage*);

	/**
	 *	Destructor.
	 */
	virtual ~SearchStartBeforeCommand(void);
};

/**
 *	SearchStartCommand sub class responsible for searching tasks after start date time specified.
 */
class SearchStartAfterCommand : public SearchStartCommand {
public:
	/**
	 *	Constructor.
	 *	@param start Start date time to be used for comparison.
	 */
	SearchStartAfterCommand(ptime start);

	/**
	 *	Execution method of SearchStartAfterCommand
	 *	Search for all tasks after _start
	 */
	UIFeedback SearchStartCommand::execute(RunTimeStorage*);

	/**
	 *	Destructor.
	 */
	virtual ~SearchStartAfterCommand(void);
};

/**
 *	Virtual SearchCommand sub class responsible for searching tasks based on end date time.
 */
class SearchEndCommand : public SearchCommand {
protected:
	/**
	 *	End date time to be used for comparison
	 */
	ptime _end;
public:
	/**
	 *	Constructor.
	 *	@param end End date time to be used for comparison.
	 */
	SearchEndCommand(ptime end);
	
	virtual UIFeedback SearchCommand::execute(RunTimeStorage*) = 0;

	/**
	 *	Destructor
	 */
	virtual ~SearchEndCommand(void);
};

/**
 *	SearchEndCommand sub class responsible for searching tasks before date time specified.
 */
class SearchEndBeforeCommand : public SearchEndCommand {
public:
	/**
	 *	Constructor.
	 *	@param end End date time to be used for comparison.
	 */
	SearchEndBeforeCommand(ptime);

	/**
	 *	Execution method of SearchEndBeforeCommand
	 *	Search for all tasks before _end
	 */
	UIFeedback SearchEndCommand::execute(RunTimeStorage*);

	/**
	 *	Destructor.
	 */
	virtual ~SearchEndBeforeCommand(void);
};

/**
 *	SearchEndCommand sub class responsible for searching tasks after date time specified.
 */
class SearchEndAfterCommand : public SearchEndCommand {
public:
	/**
	 *	Constructor.
	 *	@param end End date time to be used for comparison.
	 */
	SearchEndAfterCommand(ptime);

	/**
	 *	Execution method of SearchEndBeforeCommand
	 *	Search for all tasks after _end
	 */
	UIFeedback SearchEndCommand::execute(RunTimeStorage*);

	/**
	 *	Destructor.
	 */
	virtual ~SearchEndAfterCommand(void);
};

/**
 *	SearchCommand sub class responsible for searching tasks based on tags
 */
class SearchTagsCommand : public SearchCommand {
private:
	/**
	 *	Tags to be used for searching tasks.
	 */
	std::set<std::string> _tags;
public:
	/**
	 *	Constructor
	 *	@param tags Tags to be used for searching tasks.
	 */
	SearchTagsCommand(std::vector<std::string> tags);

	/**
	 *	Execution method of SearchTagsCommand
	 *	Search for all tasks with at least 1 matching tag.
	 */
	UIFeedback SearchCommand::execute(RunTimeStorage*);

	/**
	 *	Destructor.
	 */
	virtual ~SearchTagsCommand(void);
};

/**
 *	SearchCommand sub class responsible for searching tasks based on name
 */
class SearchNameCommand : public SearchCommand {
private:
	/**
	 *	Name to be used for searching tasks.
	 */
	std::string _searchString;
public:
	/**
	 *	Constructor
	 *	@param searchString Name to be used for searching tasks.
	 */
	SearchNameCommand(std::string searchString);

	/**
	 *	Execution method of SearchNameCommand
	 *	Search for all tasks with _searchString as substring (Case insensitive).
	 */
	UIFeedback SearchCommand::execute(RunTimeStorage*);

	/**
	 *	Destructor.
	 */
	virtual ~SearchNameCommand(void);
};

/**
 *	SearchCommand sub class responsible for searching all tasks between start and end date time specified.
 */
class SearchFromToCommand : public SearchCommand {
private:
	/**
	 *	Start date time to be used for comparison.
	 */
	ptime _startDateTime;

	/**
	 *	End date time to be used for comparison.
	 */
	ptime _endDateTime;
public:
	/**
	 *	Constructor.
	 *	@param start Start date time to be used for comparison.
	 *	@param end End date time to be used for comparison.
	 */
	SearchFromToCommand(ptime start, ptime end);

	/**
	 *	Execution method of SearchFromToCommand.
	 *	Search for all tasks that start after _startDateTime and end before _endDateTime
	 */
	UIFeedback SearchCommand::execute(RunTimeStorage*);

	/**
	 *	Destructor.
	 */
	virtual ~SearchFromToCommand(void);
};