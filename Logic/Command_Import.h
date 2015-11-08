//@@author A0112218W
#pragma once
#include "Command.h"

const std::string MESSAGE_IMPORT_INVALID_FILEPATH = "Invalid file path. Import cannot be done.";
const std::string MESSAGE_IMPORT_SUCCESS = "Data have been imported from %s.";

/**
 *	Command sub class responsible for importing save file
 */
class ImportCommand : public Command {
private:
	/**
	 *	File path of save file to be loaded
	 */
	std::string _filePath;
public:
	/**
	 *	Constructor
	 *	@param filePath File path of save file to be loaded
	 */
	ImportCommand(std::string filePath);

	/**
	 *	Execution method of ImportCommand.
	 *	Import data from save file at target location.
	 */
	UIFeedback Command::execute(RunTimeStorage*);

	UIFeedback Command::undo();

	/**
	 *	Return true all the time.
	 */
	bool Command::canUndo();

	/**
	 *	Destructor
	 */
	~ImportCommand(void);
};