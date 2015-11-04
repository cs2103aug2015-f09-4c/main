//@@author A0124439E
#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "../Logic/Task.h"
#include "../boost/date_time/posix_time/posix_time.hpp"
// TODO: conform macro global macro names to C++ standard
const std::string INVALID_PATH_ERROR_MESSAGE = "Failed to create directory. Please check file path entered";

const std::string defaultPath = "defaultSaveFile.txt";
const std::string configPath = "config.txt";
const std::string taskIdentityString = "--task--";

class INVALID_EXTENSION_EXCEPTION : public std::exception {
public:
	explicit INVALID_EXTENSION_EXCEPTION(const char* errorMessage);
	explicit INVALID_EXTENSION_EXCEPTION(std::string errorMessage);
};

class INVALID_PATH_EXCEPTION : public std::exception {
public:
	explicit INVALID_PATH_EXCEPTION(const char* errorMessage);
	explicit INVALID_PATH_EXCEPTION(std::string errorMessage);
};

class PhysicalStorageHandler {
public:
	PhysicalStorageHandler();

	// Loads parameter tasks from data stored in the file at filePath specified. If 
	// filePath is not specified, loads tasks from file at defaultPath. If file does 
	// not exist no tasks are loaded.
	void loadFromFile(std::vector<API::Task> &tasks, std::string filePath = defaultPath);

	// Saves information about API::Task objects from parameter tasks into the file 
	// at the filePath specified. If filePath is not specified, defaultPath is used. 
	// If file does not exist, a new file is created. Tasks data will be appended in 
	// existing files
	void saveToFile(std::vector<API::Task> &tasks, std::string filePath = defaultPath);

	// Setter function for filePath (.txt)
	// Accepts filePath even if a file already exist. A
	// Throws an exception if the path is invalid
	void setSaveLocation(std::string filePath);
	
	void getSaveLocation();

	virtual ~PhysicalStorageHandler(void);
};

