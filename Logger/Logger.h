#pragma once
#include "easylogging++.h"

class Logger {
public:
	static Logger* getInstance();
	static Logger* _loggerInstance;

	void logTRACE(std::string logMessage);
	void logDEBUG(std::string logMessage);
	void logFATAL(std::string logMessage);
	void logERROR(std::string logMessage);
	void logWARNING(std::string logMessage);
	void logINFO(std::string logMessage);

private:
	Logger(void);
};
