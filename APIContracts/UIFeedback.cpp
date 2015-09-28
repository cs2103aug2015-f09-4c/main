#include "UIFeedback.h"

UIFeedback::UIFeedback() {
	_feedbackMessage = "";
}

UIFeedback::UIFeedback(std::vector<Task>& tasksForDisplay, std::string feedbackMessage) {
	_tasksForDisplay = tasksForDisplay;
	_feedbackMessage = feedbackMessage;
}

std::vector<Task>& UIFeedback::getTasksForDisplay() {
	return _tasksForDisplay;
}

std::string UIFeedback::getFeedbackMessage() {
	return _feedbackMessage;
}
