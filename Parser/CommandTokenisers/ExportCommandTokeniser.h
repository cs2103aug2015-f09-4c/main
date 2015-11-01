//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class ExportCommandTokeniser : public CommandTokeniser {
public:
	ExportCommandTokeniser(void);
	virtual ~ExportCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isExportToLocalDisk(std::string userInput);
	void tokeniseExportToLocalDisk(std::string userInput, CommandTokens* outputCommandTokens);
};
