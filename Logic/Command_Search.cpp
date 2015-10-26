#include "Command_Search.h"

SearchCommand::SearchCommand(void) : Command(CommandTokens::Search) {
}

UIFeedback SearchCommand::undo() {
	assert(false);
	return UIFeedback();
}

bool SearchCommand::canUndo() {
	return false;
}

SearchCommand::~SearchCommand(void) {
}

SearchStartCommand::SearchStartCommand(ptime start) : SearchCommand() {
	assert(!start.is_special());
	_start = start;
}

SearchStartCommand::~SearchStartCommand(void) {
}

SearchStartBeforeCommand::SearchStartBeforeCommand(ptime start) : SearchStartCommand(start) {
	_type2 = CommandTokens::SecondaryCommandType::StartBefore;
}

UIFeedback SearchStartBeforeCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage!=NULL);
	runTimeStorage->setTimeForCompare(_start);
	runTimeStorage->changeDisplayType(Display_Type::displayStartBefore);
	runTimeStorage->changeSortType(Sort_Type::sortByStart);
	std::vector<Task>& tasksToDisplay = runTimeStorage->getTasksToDisplay();
	if (tasksToDisplay.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), tasksToDisplay.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchStartBeforeCommand::~SearchStartBeforeCommand(void) {
}

SearchStartAfterCommand::SearchStartAfterCommand(ptime start) : SearchStartCommand(start) {
	_type2 = CommandTokens::SecondaryCommandType::StartAfter;
}

UIFeedback SearchStartAfterCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage!=NULL);
	runTimeStorage->setTimeForCompare(_start);
	runTimeStorage->changeDisplayType(Display_Type::displayStartAfter);
	runTimeStorage->changeSortType(Sort_Type::sortByStart);
	std::vector<Task>& tasksToDisplay = runTimeStorage->getTasksToDisplay();
	if (tasksToDisplay.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), tasksToDisplay.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchStartAfterCommand::~SearchStartAfterCommand(void) {
}

SearchEndCommand::SearchEndCommand(ptime end) : SearchCommand() {
	assert(!end.is_special());
	_end = end;
}

SearchEndCommand::~SearchEndCommand(void) {
}

SearchEndBeforeCommand::SearchEndBeforeCommand(ptime end) : SearchEndCommand(end) {
	_type2 = CommandTokens::SecondaryCommandType::EndBefore;
}

UIFeedback SearchEndBeforeCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage!=NULL);
	runTimeStorage->setTimeForCompare(_end);
	runTimeStorage->changeDisplayType(Display_Type::displayEndBefore);
	runTimeStorage->changeSortType(Sort_Type::sortByEnd);
	std::vector<Task>& tasksToDisplay = runTimeStorage->getTasksToDisplay();
	if (tasksToDisplay.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), tasksToDisplay.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchEndBeforeCommand::~SearchEndBeforeCommand(void) {
}

SearchEndAfterCommand::SearchEndAfterCommand(ptime end) : SearchEndCommand(end) {
	_type2 = CommandTokens::SecondaryCommandType::EndAfter;
}

UIFeedback SearchEndAfterCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage!=NULL);
	runTimeStorage->setTimeForCompare(_end);
	runTimeStorage->changeDisplayType(Display_Type::displayEndAfter);
	runTimeStorage->changeSortType(Sort_Type::sortByEnd);
	std::vector<Task>& tasksToDisplay = runTimeStorage->getTasksToDisplay();
	if (tasksToDisplay.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), tasksToDisplay.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchEndAfterCommand::~SearchEndAfterCommand(void) {
}