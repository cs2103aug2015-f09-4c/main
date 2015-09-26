#pragma once

#include <vector>
#include "Task.h"

class UIFeedback{
private:
	std::vector<Task> _tasksForDisplay;
	std::string _feedbackMessage;
public:
	UIFeedback(std::vector<Task>& tasksForDisplay, std::string feedbackMessage) {
		_tasksForDisplay = tasksForDisplay;
		_feedbackMessage = feedbackMessage;
	}

	std::vector<Task>& getTasksForDisplay() {
		return _tasksForDisplay;
	}

	std::string getFeedbackMessage() {
		return _feedbackMessage;
	}
};

