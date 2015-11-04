//@@author A0124439E
#include "PhysicalStorageHandler.h"
#include "Logger/Logger.h"


INVALID_EXTENSION_EXCEPTION::INVALID_EXTENSION_EXCEPTION(const std::string eMessage) : std::exception(eMessage.c_str()) {
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
	tasks.clear();
	std::ifstream loadFile(_filePath.c_str());
	boost::posix_time::ptime notDateTime;
	std::string identityString = "";
	std::string taskText;
	std::string startDateTimeString;
	std::string endDateTimeString;
	std::string isCompleteString;
	std::string tag;

	_logger->logDEBUG("Loading from file...");

	try {
		if (loadFile.is_open() && !loadFile.eof()) {
			while (!loadFile.eof()) {
				API::Task *taskToAdd;

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
		}
	} catch (std::exception e) {
		std::string errorMessage = e.what();

		remove(_filePath.c_str());

		_logger->logERROR("ERROR: " + errorMessage);
		_logger->logERROR("Deleted savedFile");
	}
}

void PhysicalStorageHandler::saveToFile(std::vector<API::Task>& tasks, std::string filePath) {
	std::ofstream saveFile(_filePath.c_str());

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
}

void PhysicalStorageHandler::setSaveLocation(std::string filePath) {
	if (CreateDirectory(filePath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		int validExtensionSize = VALID_FILE_EXTENSION.size();
		if (0 != filePath.compare(filePath.size() - validExtensionSize, validExtensionSize, VALID_FILE_EXTENSION)) {
			throw INVALID_EXTENSION_EXCEPTION(INVALID_EXTENSION_ERROR_MESSAGE);
		}

		_filePath = filePath;

		remove(filePath.c_str());
		std::ofstream configFile(CONFIG_PATH.c_str());
		configFile.clear();

		if (configFile.is_open()) {
			configFile << filePath;
		}

		configFile.close();
	} else {
		throw INVALID_PATH_EXCEPTION(INVALID_PATH_ERROR_MESSAGE);
	}

	return;
}

void PhysicalStorageHandler::configSaveLocation() {
	std::ifstream configFile(CONFIG_PATH.c_str());
	bool isSuccessful = true;

	_logger->logDEBUG("Configuring _filePath from config.txt...");

	if (configFile.is_open()) {
		std::string filePath;
		std::getline(configFile, filePath);

		try {
			setSaveLocation(filePath);
		} catch (INVALID_EXTENSION_EXCEPTION e) {
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
		setSaveLocation(DEFAULT_PATH);
	} catch (INVALID_EXTENSION_EXCEPTION e) {
		assert(false);
	} catch (INVALID_PATH_EXCEPTION e) {
		assert(false);
	}

	return;
}

