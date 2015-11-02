#pragma once
#include "Command.h"

const std::string MESSAGE_SORT_SUCCESS = "Sort mode have been changed successfully.";
const std::string MESSAGE_SORT_UNDO = "Sort mode have been changed back successfully";

class SortCommand : public Command {
private:
	Sort_Type _newSortType;
	Sort_Type _oldSortType;
public:
	SortCommand(Sort_Type);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo();
	bool canUndo();
	virtual ~SortCommand(void);
};

