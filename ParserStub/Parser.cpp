#include "Parser.h"

CommandTokens Parser::parse(std::string userInput) {
	if (userInput == "Add Task 1") {
		std::vector<std::string> details;
		details.push_back("Task 1");
		return CommandTokens(PrimaryCommandType::Add, SecondaryCommandType::Floating, details);
	} else if (userInput == "Delete 1") {
		std::vector<std::string> details;
		details.push_back("1");
		return CommandTokens(PrimaryCommandType::Delete, SecondaryCommandType::None, details);
	} else {
		return CommandTokens();
	}
}