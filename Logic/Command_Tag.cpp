#include "Command_Tag.h"


TagCommand::TagCommand(size_t index, std::vector<std::string> tags) : Command(CommandTokens::PrimaryCommandType::Tag) {
	_index = index;
	_tags = tags;
	_type2 = CommandTokens::Index;
}

UIFeedback TagCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage!=NULL);
	std::string feedbackMessage;
	try {
		Task& taskToTag = runTimeStorage->find(_index);
		_tagIndex = runTimeStorage->find(taskToTag);
		for (size_t i = 0 ; i < _tags.size() ; ++i) {
			try {
				taskToTag.addTag(_tags[i]);
				_successTags.push_back(_tags[i]);
			} catch (TAG_LIMIT_EXCEPTION e) {
				throw e;
			} catch (TASK_EXCEPTION e){
				feedbackMessage += "\n";
				feedbackMessage += std::string(e.what());
			}
		}
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	} catch (TASK_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}

	if (_successTags.size() > 0) {
		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;
		char buffer[255];
		sprintf_s(buffer, MESSAGE_TAG_SUCCESS.c_str(), _index, _successTags.size());
		feedbackMessage += std::string(buffer);
	}

	return UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
}

UIFeedback TagCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	Task& taskToUntag = _runTimeStorageExecuted->getEntry(_tagIndex);
	for (size_t i = 0 ; i < _successTags.size() ; ++i) {
		taskToUntag.removeTag(_successTags[i]);
	}
	return UIFeedback(_runTimeStorageExecuted->getTasksToDisplay(), MESSAGE_TAG_UNDO);
}

bool TagCommand::canUndo() {
	return true;
}

TagCommand::~TagCommand(void) {
}
