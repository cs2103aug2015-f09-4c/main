//@@author A0112218W

#pragma once

#include "Command.h"

const std::string MESSAGE_CONFIG_SAVE_PATH_SUCCESS = "Default save path have been changed to %s";
const std::string MESSAGE_CONFIG_SAVE_PATH_UNDO = "Default save path have been reverted back.";

class ConfigureSaveLocationCommand : public Command {
private:
	std::string _newSavePath;
	std::string _oldSavePath;
public:
	ConfigureSaveLocationCommand(std::string);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo();
	bool Command::canUndo();
	virtual ~ConfigureSaveLocationCommand(void);
};

