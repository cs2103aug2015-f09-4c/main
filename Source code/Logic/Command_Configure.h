//@@author A0112218W

#pragma once

#include "Command.h"

const std::string MESSAGE_CONFIG_SAVE_PATH_SUCCESS = "Default save path have been changed to %s";
const std::string MESSAGE_CONFIG_SAVE_PATH_UNDO = "Default save path have been reverted back.";

/**
 *	Command sub class responsible to configure default save location of Swiftask
 */
class ConfigureSaveLocationCommand : public Command {
private:
	/**
	 *	New save path to overwrite the current default save path
	 */
	std::string _newSavePath;

	/**
	 *	Old save path to overwrite the current default save path during undo
	 */
	std::string _oldSavePath;
public:
	/**
	 *	Constructor
	 *	@param savePath Save path that want to be set as default save path
	 */
	ConfigureSaveLocationCommand(std::string savePath);

	/**
	 *	Execution method of ConfigureSaveLocationCommand
	 *	Current default save path will be overwrite by the new one.
	 */
	UIFeedback Command::execute(RunTimeStorage*);

	/**
	 *	Undo method of ConfigureSaveLocationCommand
	 *	Revert the default save path to the previous one.
	 */
	UIFeedback Command::undo();

	/**
	 *	Return true all the time
	 */
	bool Command::canUndo();

	/**
	 *	Destructor
	 */
	virtual ~ConfigureSaveLocationCommand(void);
};

