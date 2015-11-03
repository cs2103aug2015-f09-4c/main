#include "PhysicalStorageHandler.h"
#include "Logger/Logger.h"


PhysicalStorageHandler::PhysicalStorageHandler() {
}


PhysicalStorageHandler::~PhysicalStorageHandler(void) {
}

void PhysicalStorageHandler::loadFromFile(std::vector<API::Task>& tasks, std::string filePath) {
	tasks.clear();
	std::ifstream loadFile(filePath.c_str());
	boost::posix_time::ptime notDateTime;
	std::string identityString = "";
	std::string taskText;
	std::string startDateTimeString;
	std::string endDateTimeString;
	std::string isCompleteString;
	std::string tag;

	Logger* logger = Logger::getInstance();
	logger->logDEBUG("Loading from file...");

	try {
		if (loadFile.is_open() && !loadFile.eof()) {
			while (!loadFile.eof()) {
				API::Task *taskToAdd;

				while (!loadFile.eof() && taskIdentityString != identityString) {
					std::getline(loadFile, identityString);
				}

				std::getline(loadFile, taskText);
				if (taskIdentityString == taskText) {
					identityString = taskText;
					continue;
				}

				std::getline(loadFile, startDateTimeString);
				if (taskIdentityString == startDateTimeString) {
					identityString = startDateTimeString;
					taskToAdd = new API::Task(taskText);
					continue;
				}

				std::getline(loadFile, endDateTimeString);
				if (taskIdentityString == endDateTimeString) {
					identityString = endDateTimeString;
					continue;
				}

				std::getline(loadFile, isCompleteString);
				if (taskIdentityString == isCompleteString) {
					identityString = isCompleteString;
					continue;
				}

				boost::posix_time::ptime startDateTime;
				if (startDateTimeString != "not-a-date-time") {
					try {
						startDateTime = boost::posix_time::time_from_string(startDateTimeString);
					} catch (boost::exception const & e) {
						logger->logERROR(startDateTimeString + " is not a format for boost::posix_time");
					}
				}

				boost::posix_time::ptime endDateTime;
				if (endDateTimeString != "not-a-date-time") {
					try {
						endDateTime = boost::posix_time::time_from_string(endDateTimeString);
					} catch (boost::exception const & e) {
						logger->logERROR(endDateTimeString + " is not a format for boost::posix_time");
					}
				}

				try {
					taskToAdd = new API::Task(taskText, startDateTime, endDateTime);
				} catch (std::exception e) {
					logger->logERROR(e.what());

					taskToAdd = new API::Task(taskText, notDateTime, notDateTime);
				}

				if (isCompleteString == "1") {
					taskToAdd->toggleComplete();
				}

				std::getline(loadFile, tag);
				while (!loadFile.eof() && taskIdentityString != tag) {
					try {
						taskToAdd->addTag(tag);
					} catch (std::exception e) {
						logger->logDEBUG("Tag: " + tag + " Message: " + e.what());
					}
					std::getline(loadFile, tag);
				}
				identityString = tag;

				tasks.push_back(*taskToAdd);
			}
		}
	} catch (std::exception e) {
		std::string errorMessage = e.what();

		remove(filePath.c_str());

		logger->logERROR("ERROR: " + errorMessage);
		logger->logERROR("Deleted savedFile");
	}
}

void PhysicalStorageHandler::saveToFile(std::vector<API::Task>& tasks, std::string filePath) {
	std::ofstream saveFile(filePath.c_str());
	for (size_t i = 0 ; i < tasks.size() ; ++i) {
		saveFile << taskIdentityString << std::endl;
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
