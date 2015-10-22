#pragma once
#include <regex>
#include "CommandTokens.h"
#include "CommandTokeniser.h"
#include "Logger\Logger.h"
#include "AddCommandTokeniser.h"
#include "CompleteCommandTokeniser.h"
#include "DeleteCommandTokeniser.h"
#include "DisplayCommandTokeniser.h"
#include "ExportCommandTokeniser.h"
#include "EditCommandTokeniser.h"
#include "RefreshCommandTokeniser.h"
#include "TagCommandTokeniser.h"
#include "UndoCommandTokeniser.h"
#include "UntagCommandTokeniser.h"

// tokenises user input for Logic to do the necessary processing
class Parser {
public:
	Parser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokeniser* _commandTokeniser;
	CommandTokens _invalidCommandTokens;

	AddCommandTokeniser _addCommandTokeniser;
	CompleteCommandTokeniser _completeCommandTokeniser;
	DeleteCommandTokeniser _deleteCommandTokeniser;
	DisplayCommandTokeniser _displayCommandTokeniser;
	ExportCommandTokeniser _exportCommandTokeniser;
	EditCommandTokeniser _editCommandTokeniser;
	RefreshCommandTokeniser _refreshCommandTokeniser;
	TagCommandTokeniser _tagCommandTokeniser;
	UndoCommandTokeniser _undoCommandTokeniser;
	UntagCommandTokeniser _untagCommandTokeniser;


	Logger* _logger;

	void selectCommandTokeniser(std::string userInput);

	bool isAddCommand(std::string& userInput);
	bool isCompleteCommand(std::string& userInput);
	bool isDeleteCommand(std::string& userInput);
	bool isEditCommand(std::string& userInput);
	bool isDisplayCommand(std::string& userInput);
	bool isExportCommand(std::string& userInput);
	bool isRefreshCommand(std::string& userInput);
	bool isTagCommand(std::string& userInput);
	bool isUndoCommand(std::string& userInput);
	bool isUntagCommand(std::string& userInput);
};
