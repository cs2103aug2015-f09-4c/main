//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class DeleteCommandTokeniser : public CommandTokeniser {
public:
	DeleteCommandTokeniser(void);
	virtual ~DeleteCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isDeleteAll(std::string userInput);
	bool isDeleteCompleted(std::string userInput);
	bool isDeleteIndex(std::string userInput);
	bool isDeleteBy(std::string userInput);
	bool isDeleteFromTo(std::string userInput);
	bool isDeleteFrom(std::string userInput);

	void tokeniseDeleteAll(CommandTokens* outputCommandTokens);
	void tokeniseDeleteCompleted(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseDeleteIndex(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseDeleteBy(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseDeleteFromTo(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseDeleteFrom(std::string userInput, CommandTokens* outputCommandTokens);
};
