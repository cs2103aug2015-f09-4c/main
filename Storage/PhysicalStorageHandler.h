//@@author A0124439E
#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "../Logic/Task.h"
#include "../boost/date_time/posix_time/posix_time.hpp"

const std::string INVALID_EXTENSION_ERROR_MESSAGE = "Error: File extension is not .txt";
const std::string INVALID_PATH_ERROR_MESSAGE = "Failed to create directory. Please check file path entered";

const std::string DEFAULT_PATH = "defaultSaveFile.txt";
const std::string CONFIG_PATH = "config.txt";
const std::string TASK_IDENTITY_STRING = "--task--";

class INVALID_EXTENSION_EXCEPTION : public std::exception {
public:
	explicit INVALID_EXTENSION_EXCEPTION(const std::string errorMessage);
};

class INVALID_PATH_EXCEPTION : public std::exception {
public:
	explicit INVALID_PATH_EXCEPTION(const std::string errorMessage);
};

class PhysicalStorageHandler {
public:
	PhysicalStorageHandler();

	// Loads parameter tasks from data stored in the file at filePath specified. If 
	// filePath is not specified, loads tasks from file at DEFAULT_PATH. If file does 
	// not exist no tasks are loaded.
	void loadFromFile(std::vector<API::Task> &tasks, std::string filePath = DEFAULT_PATH);

	// Saves information about API::Task objects from parameter tasks into the file 
	// at the filePath specified. If filePath is not specified, DEFAULT_PATH is used. 
	// If file does not exist, a new file is created. Tasks data will be appended in 
	// existing files
	void saveToFile(std::vector<API::Task> &tasks, std::string filePath = DEFAULT_PATH);

	// Setter function for filePath of data storage file
	// Accepts filePath even if the file already exist. filePath is saved in config.txt
	// in the same directory as program.
	// Throws an exception if the path is invalid.
	// Throws an exception if extension of path is not .txt
	void setSaveLocation(std::string filePath);

	virtual ~PhysicalStorageHandler(void);

private:
	// Getter function for filePath of data storage file
	// Gets filePath stored in config.txt
	// Throws an exception if file does not exist
	std::string getSaveLocation();
};

