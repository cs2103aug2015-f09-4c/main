#pragma once
#include "Command.h"

const std::string MESSAGE_UNTAG_SUCCESS = "Task at index %i have %i tag(s) removed.";
const std::string MESSAGE_UNTAG_UNDO = "Previous untag operation have been undoed.";

class UntagCommand : public Command {
private:
	std::vector<std::string> _untags;
	std::vector<std::string> _successUntags;
	size_t _index;
	size_t _untagIndex;

public:
	UntagCommand(size_t, std::vector<std::string>);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo();
	bool Command::canUndo();
	~UntagCommand(void);
};

