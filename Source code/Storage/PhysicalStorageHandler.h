//@@author A0124439E
#pragma once

#include <assert.h>
#include <fstream>
#include <string>
#include <vector>
#include "Logger\Logger.h"
#include "../Logic/Task.h"
#include "../boost/date_time/posix_time/posix_time.hpp"

const std::string INVALID_FILE_ERROR_MESSAGE = "Error: File name is not acceptable";
const std::string INVALID_PATH_ERROR_MESSAGE = "Failed to create directory. Please check file path entered";

const std::string DEFAULT_FILE = "defaultSaveFile.txt";
const std::string CONFIG_FILE = "config.txt";
const std::string VALID_FILE_EXTENSION = ".txt";
const std::string TASK_IDENTITY_STRING = "--task--";
const std::string NO_FILE_PATH_SPECIFIED = "No file specified";

class INVALID_FILE_EXCEPTION : public std::exception {
public:
	explicit INVALID_FILE_EXCEPTION(const std::string eMessage);
};

class INVALID_PATH_EXCEPTION : public std::exception {
public:
	explicit INVALID_PATH_EXCEPTION(const std::string eMessage);
};

class PhysicalStorageHandler {
public:
	PhysicalStorageHandler();

	// Loads parameter tasks from data stored in the file at filePath specified. If 
	// filePath is not specified, loads tasks from file at _filePath. If file does 
	// not exist no tasks are loaded.
	//
	// Throws INVALID_FILE_EXCEPTION when filePath is specified and file cannot be opened
	void loadFromFile(std::vector<API::Task> &tasks, std::string filePath = NO_FILE_PATH_SPECIFIED);

	// Saves information about API::Task objects from parameter tasks into the file 
	// at the filePath specified. If filePath is not specified, _filePath is used. 
	// If file does not exist, a new file is created. Tasks data will OVERWRITE 
	// existing file
	//
	// Throws INVALID_PATH_EXCEPTION when file does not exist and cannot be created
	void saveToFile(std::vector<API::Task> &tasks, std::string filePath = NO_FILE_PATH_SPECIFIED);

	// Setter function for filePath of data storage file. Accepts filePath even if 
	// the file already exist. _filePath attribute is updated. filePath is saved at 
	// CONFIG_FILE in the same directory as program.
	//
	// Throws INVALID_FILE_EXCEPTION if the file name is invalid.
	// Throws INVALID_PATH_EXCEPTION if the path is invalid or unable to create folder
	void setSaveLocation(std::string filePath = "");

	std::string getFilePath(void);

	static void setToTestMode() {
		isTestMode = true;
	}

	virtual ~PhysicalStorageHandler(void);

private:
	Logger* _logger;

	std::string _filePath;

	// Gets filePath from CONFIG_FILE and store it in _filePath. If CONFIG_FILE cannot
	// be opened or filePath gotten is invalid, sets _filePath as DEFAULT_FILE instead.
	void configSaveLocation();

	void splitFileName(std::string fileName, std::string &path, std::string &file);

	static bool isTestMode;
};

