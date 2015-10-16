#include "Logger.h"

INITIALIZE_EASYLOGGINGPP

Logger* Logger::_loggerInstance = nullptr;

Logger::Logger(void) {
	el::Configurations logConfig;
	logConfig.setToDefault();
	logConfig.parseFromText("*GLOBAL:\n FILENAME = \"Swiftask.log\"\n ENABLED = true\n TO_FILE = true\n TO_STANDARD_OUTPUT = true");
	el::Loggers::reconfigureAllLoggers(logConfig);
}

Logger* Logger::getInstance() {
	if (_loggerInstance == nullptr) {
		_loggerInstance = new Logger();
	}
	return _loggerInstance;
}

void Logger::log(LogLevel logLevel, std::string logMessage) {
	switch (logLevel) {
		case Trace:
			LOG(TRACE) << logMessage;
			break;
		case Debug:
			LOG(DEBUG) << logMessage;
			break;
		case Fatal:
			LOG(FATAL) << logMessage;
			break;
		case Error:
			LOG(ERROR) << logMessage;
			break;
		case Warning:
			LOG(WARNING) << logMessage;
			break;
		case Info:
		default:
			LOG(INFO) << logMessage;
			break;
	}
}

void Logger::logTRACE(std::string logMessage) {
	LOG(TRACE) << logMessage;
}

void Logger::logDEBUG(std::string logMessage) {
	LOG(DEBUG) << logMessage;
}

void Logger::logFATAL(std::string logMessage) {
	LOG(FATAL) << logMessage;
}

void Logger::logERROR(std::string logMessage) {
	LOG(ERROR) << logMessage;
}

void Logger::logWARNING(std::string logMessage) {
	LOG(WARNING) << logMessage;
}

void Logger::logINFO(std::string logMessage) {
	LOG(INFO) << logMessage;
}
