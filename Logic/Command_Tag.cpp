#include "Command_Tag.h"


TagCommand::TagCommand(size_t index, std::vector<std::string> tags) : Command(CommandTokens::PrimaryCommandType::Tag) {
	_index = index;
	_tags = tags;
}

UIFeedback TagCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage!=NULL);
	try {
		Task& taskToTag = runTimeStorage->find(_index);
		_tagIndex = runTimeStorage->find(taskToTag);
		for (size_t i = 0 ; i < _tags.size() ; ++i) {
			if (taskToTag.addTag(_tags[i])) {
				_successTags.push_back(_tags[i]);
			}
		}
		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}
	char buffer[255];
	sprintf_s(buffer, MESSAGE_TAG_SUCCESS.c_str(), _index, _successTags.size());
	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

UIFeedback TagCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	Task& taskToUntag = _runTimeStorageExecuted->getEntry(_tagIndex);
	for (int i = 0 ; i < _successTags.size() ; ++i) {
		taskToUntag.removeTag(_successTags[i]);
	}
	return UIFeedback(_runTimeStorageExecuted->getTasksToDisplay(), MESSAGE_TAG_UNDO);
}

bool TagCommand::canUndo() {
	return true;
}

TagCommand::~TagCommand(void)
{
}
