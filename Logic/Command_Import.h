//@@author A0112218W
#pragma once
#include "Command.h"

const std::string MESSAGE_IMPORT_INVALID_FILEPATH = "Invalid file path. Import cannot be done.";
const std::string MESSAGE_IMPORT_SUCCESS = "Data have been imported from %s.";

class ImportCommand : public Command {
private:
	std::string _filePath;
public:
	ImportCommand(std::string);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo();
	bool Command::canUndo();
	~ImportCommand(void);
};