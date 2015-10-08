#include "Command_Add.h"

AddCommand::AddCommand (SecondaryCommandType type2, Task task) : Command(PrimaryCommandType::Add) {
	_type2 = type2;
	_task = task;
}

UIFeedback AddCommand::execute(StorageHandler* storageHandler) {
	UIFeedback feedback;
	if (_task.getTaskText().size() < 1) {
		feedback = UIFeedback(storageHandler->getTasksToDisplay(), MESSAGE_ADD_EMPTY);
	} else if (storageHandler->isDuplicate(_task)) {
		feedback = UIFeedback(storageHandler->getTasksToDisplay(), MESSAGE_ADD_DUPLICATE);
	} else {
		storageHandler->add(_task);
		std::string taskText = _task.getTaskText();
		std::string startDateTime = boost::posix_time::to_simple_string(_task.getStartDateTime());
		std::string endDateTime = boost::posix_time::to_simple_string(_task.getEndDateTime());
		char buffer[255];
		sprintf_s(buffer, MESSAGE_ADD_SUCCESS.c_str(), taskText.c_str(), startDateTime.c_str(), endDateTime.c_str());
		std::string feedbackMessage(buffer);
		feedback = UIFeedback(storageHandler->getTasksToDisplay(), feedbackMessage);
		_statusExecuted = true;
	}
	return feedback;
}

UIFeedback AddCommand::undo() {
	//TODO
	return UIFeedback();
}

bool AddCommand::canUndo() {
	return true;
}

AddCommand::~AddCommand(void) {	
}
