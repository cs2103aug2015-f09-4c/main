#ifndef PARSER_H_
#define PARSER_H_

#include "..\..\Swiftask.h"

class Parser{
public:
	CommandTokens parse(std::string userInput);
};

#endif