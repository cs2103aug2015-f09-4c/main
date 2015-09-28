#ifndef PARSER_H_
#define PARSER_H_

#include "../APIContracts/CommandTokens.h"

class Parser{
public:
	CommandTokens parse(std::string userInput);
};

#endif