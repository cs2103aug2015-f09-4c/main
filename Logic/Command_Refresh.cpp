#include "Command_Refresh.h"


RefreshCommand::RefreshCommand(void) : Command(CommandTokens::PrimaryCommandType::Refresh)
{
}

UIFeedback RefreshCommand::execute(RunTimeStorage* runTimeStorage) {
	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), "");
}

UIFeedback RefreshCommand::undo() {
	assert(false);
	return UIFeedback();
}


RefreshCommand::~RefreshCommand(void){
}
