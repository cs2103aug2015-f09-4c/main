#include "Command_Refresh.h"


RefreshCommand::RefreshCommand(void) : Command(CommandTokens::PrimaryCommandType::Export)
{
}

UIFeedback RefreshCommand::execute(RunTimeStorage* runTimeStorage) {
	return UIFeedback(runTimeStorage->getTasksToDisplay(), "");
}

UIFeedback RefreshCommand::undo() {
	assert(false);
	return UIFeedback();
}


RefreshCommand::~RefreshCommand(void){
}