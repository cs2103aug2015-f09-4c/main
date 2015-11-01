#include "PhysicalStorageHandler.h"
#include "Logger/Logger.h"


PhysicalStorageHandler::PhysicalStorageHandler() {
}


PhysicalStorageHandler::~PhysicalStorageHandler(void) {
}

void PhysicalStorageHandler::loadFromFile(std::vector<API::Task>& tasks, std::string filePath) {
	tasks.clear();
	std::string identityString = "";
	std::ifstream loadFile(filePath.c_str());

	Logger* logger = Logger::getInstance();
	logger->logDEBUG("Loading from file...");

	try {
		if (loadFile.is_open() && !loadFile.eof()) {
			while (!loadFile.eof() && identityString != start) {
				std::getline(loadFile, identityString);
			}

			while (!loadFile.eof()) {
				std::string taskText;
				std::string startDateTimeString;
				std::string endDateTimeString;
				std::string isCompleteString;
				API::Task *taskToAdd;

				std::getline(loadFile,taskText);

				std::getline(loadFile,startDateTimeString);
				boost::posix_time::ptime startDateTime;
				if (startDateTimeString != "not-a-date-time") {
					try {
						startDateTime = boost::posix_time::time_from_string(startDateTimeString);
					} catch (boost::exception const & e) {
						logger->logERROR(startDateTimeString + " is not a format for boost::posix_time");
					}
				}

				std::getline(loadFile,endDateTimeString);
				boost::posix_time::ptime endDateTime;
				if (endDateTimeString != "not-a-date-time") {
					try {
						endDateTime = boost::posix_time::time_from_string(endDateTimeString);
					} catch (boost::exception const & e) {
						logger->logERROR(endDateTimeString + " is not a format for boost::posix_time");
					}
				}

				std::getline(loadFile, isCompleteString);

				try {
					taskToAdd = new API::Task(taskText, startDateTime, endDateTime);
				} catch (std::exception e) {
					logger->logERROR(e.what());

					boost::posix_time::ptime notDateTime;
					taskToAdd = new API::Task(taskText, notDateTime, notDateTime);
				}

				if (isCompleteString == "1") {
					taskToAdd->toggleComplete();
				}

				std::getline(loadFile, identityString);
				while (!loadFile.eof() && identityString != start) {
					try {
						taskToAdd->addTag(identityString);
					} catch (std::exception e) {
						logger->logDEBUG("Tag: " + identityString + " not added");
					}
					std::getline(loadFile, identityString);
				}
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
		saveFile << start << "\n";
		saveFile << tasks[i].getTaskText() << "\n";
		saveFile << boost::posix_time::to_simple_string(tasks[i].getStartDateTime()) << "\n";
		saveFile << boost::posix_time::to_simple_string(tasks[i].getEndDateTime()) << "\n";
		if (tasks[i].isComplete()) {
			saveFile << "1\n";
		} else {
			saveFile << "0\n";
		}
		std::set<std::string> tags = tasks[i].getTags();
		std::set<std::string>::iterator iter;
		for (iter = tags.begin() ; iter != tags.end() ; ++iter) {
			saveFile << *iter << "\n";
		}
	}
}
