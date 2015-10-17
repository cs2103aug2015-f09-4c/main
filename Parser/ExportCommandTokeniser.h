#pragma once
#include "CommandTokeniser.h"

class ExportCommandTokeniser : public CommandTokeniser {
public:
	ExportCommandTokeniser(void);
	virtual ~ExportCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	void tokeniseExportCommand(std::string userInput);
};
