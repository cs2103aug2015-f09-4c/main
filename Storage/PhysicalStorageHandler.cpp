//@@author A0124439E
#include "PhysicalStorageHandler.h"
#include "Logger/Logger.h"


INVALID_FILE_EXCEPTION::INVALID_FILE_EXCEPTION(const std::string eMessage) : std::exception(eMessage.c_str()) {
}


INVALID_PATH_EXCEPTION::INVALID_PATH_EXCEPTION(const std::string eMessage) : std::exception(eMessage.c_str()) {
}


PhysicalStorageHandler::PhysicalStorageHandler() {
	_logger = Logger::getInstance();

	configSaveLocation();
}


PhysicalStorageHandler::~PhysicalStorageHandler(void) {
}

void PhysicalStorageHandler::loadFromFile(std::vector<API::Task>& tasks, std::string filePath) {
	std::ifstream loadFile;
	boost::posix_time::ptime notDateTime;
	std::string identityString = "";
	std::string taskText;
	std::string startDateTimeString;
	std::string endDateTimeString;
	std::string isCompleteString;
	std::string tag;

	_logger->logDEBUG("Loading from file...");

	if (NO_FILE_PATH_SPECIFIED == filePath) {
		loadFile.open(_filePath.c_str());
	} else {
		loadFile.open(filePath.c_str());
	}

	if (!loadFile.is_open()) {
		throw INVALID_FILE_EXCEPTION(INVALID_FILE_ERROR_MESSAGE);
	}
	tasks.clear();

	try {
		while (!loadFile.eof()) {
			API::Task *taskToAdd;

			_logger->logDEBUG("Loading Task...");

			while (!loadFile.eof() && TASK_IDENTITY_STRING != identityString) {
				std::getline(loadFile, identityString);
			}

			std::getline(loadFile, taskText);
			if (TASK_IDENTITY_STRING == taskText) {
				identityString = taskText;
				continue;
			}

			std::getline(loadFile, startDateTimeString);
			if (TASK_IDENTITY_STRING == startDateTimeString) {
				identityString = startDateTimeString;
				taskToAdd = new API::Task(taskText);
				tasks.push_back(*taskToAdd);
				continue;
			}

			std::getline(loadFile, endDateTimeString);
			if (TASK_IDENTITY_STRING == endDateTimeString) {
				identityString = endDateTimeString;
				taskToAdd = new API::Task(taskText);
				tasks.push_back(*taskToAdd);
				continue;
			}

			boost::posix_time::ptime startDateTime;
			if (startDateTimeString != "not-a-date-time") {
				try {
					startDateTime = boost::posix_time::time_from_string(startDateTimeString);
				} catch (boost::exception const & e) {
					_logger->logERROR(startDateTimeString + " is not a format for boost::posix_time");
				}
			}

			boost::posix_time::ptime endDateTime;
			if (endDateTimeString != "not-a-date-time") {
				try {
					endDateTime = boost::posix_time::time_from_string(endDateTimeString);
				} catch (boost::exception const & e) {
					_logger->logERROR(endDateTimeString + " is not a format for boost::posix_time");
				}
			}

			try {
				taskToAdd = new API::Task(taskText, startDateTime, endDateTime);
			} catch (std::exception &e) {
				_logger->logERROR(e.what());

				taskToAdd = new API::Task(taskText, notDateTime, notDateTime);
			}

			std::getline(loadFile, isCompleteString);
			if (isCompleteString == "1") {
				taskToAdd->toggleComplete();
			}

			std::getline(loadFile, tag);
			while (!loadFile.eof() && TASK_IDENTITY_STRING != tag) {
				try {
					taskToAdd->addTag(tag);
				} catch (std::exception &e) {
					_logger->logDEBUG("Tag: " + tag + " Message: " + e.what());
				}
				std::getline(loadFile, tag);
			}
			identityString = tag;

			tasks.push_back(*taskToAdd);
			delete taskToAdd;
		}
	} catch (std::exception e) {
		std::string errorMessage = e.what();

		remove(_filePath.c_str());

		_logger->logERROR("ERROR: " + errorMessage);
		_logger->logERROR("Deleted savedFile");
	}

	return;
}

void PhysicalStorageHandler::saveToFile(std::vector<API::Task>& tasks, std::string filePath) {
	std::ofstream saveFile;

	if (NO_FILE_PATH_SPECIFIED == filePath) {
		saveFile.open(_filePath.c_str());
	} else {
		saveFile.open(filePath.c_str());
	}

	if (!saveFile.is_open()) {
		throw INVALID_PATH_EXCEPTION(INVALID_PATH_ERROR_MESSAGE);
	}

	for (size_t i = 0 ; i < tasks.size() ; ++i) {
		saveFile << TASK_IDENTITY_STRING << std::endl;

		saveFile << tasks[i].getTaskText() << std::endl;

		saveFile << boost::posix_time::to_simple_string(tasks[i].getStartDateTime()) << std::endl;

		saveFile << boost::posix_time::to_simple_string(tasks[i].getEndDateTime()) << std::endl;

		if (tasks[i].isComplete()) {
			saveFile << true << std::endl;
		} else {
			saveFile << false << std::endl;
		}

		std::set<std::string> tags = tasks[i].getTags();
		std::set<std::string>::iterator iter;
		for (iter = tags.begin() ; iter != tags.end() ; ++iter) {
			saveFile << *iter << std::endl;
		}
	}

	return;
}

void PhysicalStorageHandler::setSaveLocation(std::string filePath) {
	std::string path = "";
	std::string file = "";

	splitFileName(filePath, path, file);

	int validExtensionSize = VALID_FILE_EXTENSION.size();
	if (file.size() <= validExtensionSize ||
		0 != file.compare(file.size() - validExtensionSize, validExtensionSize, VALID_FILE_EXTENSION)) {
			throw INVALID_FILE_EXCEPTION(INVALID_FILE_ERROR_MESSAGE);
	}

	std::fstream dataFile(filePath.c_str());

	if (dataFile.good()) {
		_filePath = filePath;
	} else if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {

		_filePath = filePath;

		std::ofstream configFile(CONFIG_FILE.c_str());

		if (configFile.is_open()) {
			configFile.clear();
			configFile << filePath;
		}

		configFile.close();
	} else {
		throw INVALID_PATH_EXCEPTION(INVALID_PATH_ERROR_MESSAGE);
	}

	return;
}

void PhysicalStorageHandler::configSaveLocation() {
	std::ifstream configFile(CONFIG_FILE.c_str());
	bool isSuccessful = true;

	_logger->logDEBUG("Configuring _filePath from CONFIG_FILE...");

	if (configFile.is_open()) {
		std::string filePath;
		std::getline(configFile, filePath);

		try {
			setSaveLocation(filePath);
		} catch (INVALID_FILE_EXCEPTION e) {
			_logger->logERROR(e.what());
			isSuccessful = false;
		} catch (INVALID_PATH_EXCEPTION e) {
			_logger->logERROR(e.what());
			isSuccessful = false;
		}

		if (isSuccessful) {
			return;
		}
	}

	try {
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);

		std::string currentLocation(buffer);
		std::string path = "";
		std::string file = "";
		splitFileName(currentLocation, path, file);
		file = DEFAULT_FILE;
		setSaveLocation(path + file);
	} catch (INVALID_FILE_EXCEPTION e) {
		assert(false);
	} catch (INVALID_PATH_EXCEPTION e) {
		assert(false);
	}

	return;
}

void PhysicalStorageHandler::splitFileName(std::string fileName, std::string &path ,std::string &file) {
	std::size_t found = fileName.find_last_of("/\\");

	path = fileName.substr(0, found + 1);
	file = fileName.substr(found + 1);

	return;
}

std::string PhysicalStorageHandler::getFilePath(void) {
	return _filePath;
}
