// No longer needed
// Pending deletion
#include "LogicStub.h"

int main(void) {
	return 0;
}

Logic::Logic(void) {
}


Logic::~Logic(void) {
}

Feedback Logic::executeCommand(std::string userInput) {
	Feedback feedback;
	feedback.results = "\"" + userInput + "\" has been executed";
	return feedback;
}