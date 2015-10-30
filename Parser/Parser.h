#pragma once
#include <regex>
#include "CommandTokens.h"
#include "CommandTokeniser.h"
#include "Logger\Logger.h"
#include "CommandTokenisers\AddCommandTokeniser.h"
#include "CommandTokenisers\ConfigureCommandTokeniser.h"
#include "CommandTokenisers\CompleteCommandTokeniser.h"
#include "CommandTokenisers\DeleteCommandTokeniser.h"
#include "CommandTokenisers\DisplayCommandTokeniser.h"
#include "CommandTokenisers\ExportCommandTokeniser.h"
#include "CommandTokenisers\EditCommandTokeniser.h"
#include "CommandTokenisers\ImportCommandTokeniser.h"
#include "CommandTokenisers\RefreshCommandTokeniser.h"
#include "CommandTokenisers\SearchCommandTokeniser.h"
#include "CommandTokenisers\TagCommandTokeniser.h"
#include "CommandTokenisers\UndoCommandTokeniser.h"
#include "CommandTokenisers\UntagCommandTokeniser.h"

// facade class to provide uniform way to assess the various CommandTokenisers
class Parser {
public:
	Parser(void);
	CommandTokens parse(std::string userInput);

private:
	Logger* _logger;

	CommandTokeniser* _commandTokeniser;
	CommandTokens _invalidCommandTokens;

	AddCommandTokeniser _addCommandTokeniser;
	ConfigureCommandTokeniser _configureCommandTokeniser;
	CompleteCommandTokeniser _completeCommandTokeniser;
	DeleteCommandTokeniser _deleteCommandTokeniser;
	DisplayCommandTokeniser _displayCommandTokeniser;
	ExportCommandTokeniser _exportCommandTokeniser;
	EditCommandTokeniser _editCommandTokeniser;
	ImportCommandTokeniser _importCommandTokeniser;
	RefreshCommandTokeniser _refreshCommandTokeniser;
	SearchCommandTokeniser _searchCommandTokeniser;
	TagCommandTokeniser _tagCommandTokeniser;
	UndoCommandTokeniser _undoCommandTokeniser;
	UntagCommandTokeniser _untagCommandTokeniser;

	void selectCommandTokeniser(std::string userInput);

	bool isAddCommand(std::string& userInput);
	bool isConfigureCommand(std::string& userInput);
	bool isCompleteCommand(std::string& userInput);
	bool isDeleteCommand(std::string& userInput);
	bool isEditCommand(std::string& userInput);
	bool isDisplayCommand(std::string& userInput);
	bool isExportCommand(std::string& userInput);
	bool isImportCommand(std::string& userInput);
	bool isRefreshCommand(std::string& userInput);
	bool isSearchCommand(std::string& userInput);
	bool isTagCommand(std::string& userInput);
	bool isUndoCommand(std::string& userInput);
	bool isUntagCommand(std::string& userInput);
};
