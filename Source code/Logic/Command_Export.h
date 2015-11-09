//@@author A0112218W
#pragma once
#include "Command.h"

const std::string MESSAGE_EXPORT_INVALID_FILEPATH = "Invalid file path. Export cannot be done.";
const std::string MESSAGE_EXPORT_SUCCESS = "Data have been exported to %s.";

/**
 *	Command sub class responsible for exporting save file
 */
class ExportCommand : public Command {
private:
	/**
	 *	File path for export location
	 */
	std::string _filePath;
public:
	/**
	 *	Constructor
	 *	@param filePath File path for export location.
	 */
	ExportCommand(std::string filePath);

	/**
	 *	Execution method of ExportCommand.
	 *	Export save file to target location.
	 */
	UIFeedback Command::execute(RunTimeStorage*);

	UIFeedback Command::undo();
	/**
	 *	Return false all the time.
	 */
	bool Command::canUndo();

	/**
	 *	Destructor
	 */
	~ExportCommand(void);
};

