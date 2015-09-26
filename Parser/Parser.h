#pragma once

#include "../APIContracts/CommandTokens.h"

// used to parse user input into CommandTokens for Logic to execute appropriate
// commands; this class is not mean to be instantiated
class Parser
{
public:
	static CommandTokens parse(std::string);

private:
	Parser(void);
};