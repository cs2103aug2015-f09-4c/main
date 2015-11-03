//@@author A0112218W
#pragma once
#include "Command.h"

const std::string MESSAGE_EXPORT_INVALID_FILEPATH = "Invalid file path. Export cannot be done.";
const std::string MESSAGE_EXPORT_SUCCESS = "Data have been exported to %s.";

class ExportCommand : public Command {
private:
	std::string _filePath;
public:
	ExportCommand(std::string);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo();
	bool Command::canUndo();
	~ExportCommand(void);
};

