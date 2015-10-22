#pragma once
#include "Command.h"

const std::string MESSAGE_TAG_SUCCESS = "Task at index %i have %i new tags added.";
const std::string MESSAGE_TAG_UNDO = "Previous tag operation have been undoed.";

class TagCommand : public Command {
private:
	size_t _index;
	std::vector<std::string> _tags;
	std::vector<std::string> _successTags;
	int _tagIndex;
public:
	TagCommand(size_t, std::vector<std::string>);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo();
	bool canUndo();
	~TagCommand(void);
};

