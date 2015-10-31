//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class EditCommandTokeniser : public CommandTokeniser {
public:
	EditCommandTokeniser(void);
	virtual ~EditCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isEditName(std::string userInput);
	bool isEditStartDate(std::string userInput);
	bool isEditEndDate(std::string userInput);

	void tokeniseEditName(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseEditStartDate(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseEditEndDate(std::string userInput, CommandTokens* outputCommandTokens);
};
