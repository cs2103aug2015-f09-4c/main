#pragma once
#include "..\CommandTokeniser.h"

class AddCommandTokeniser : public CommandTokeniser {
public:
	AddCommandTokeniser(void);
	virtual ~AddCommandTokeniser(void);

	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	virtual bool isValidCommand(std::string userInput) override;

private:
	bool isAddFromTo(std::string userInput);
	bool isAddBy(std::string userInput);
	bool isAddFloating(std::string userInput);

	void tokeniseAddFromTo(std::string userInput);
	void tokeniseAddBy(std::string userInput);
	void tokeniseAddFloating(std::string userInput);

	bool isTagged(std::string userInput);
	void tokeniseTags(std::string userInput);	
	std::string trimTags(std::string userInput);
};
