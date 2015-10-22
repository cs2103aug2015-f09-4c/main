#pragma once

#include <cstdio>
#include "RunTimeStorage.h"
using namespace API;

/**
 *	Exception to be thrown for all exception in constructor.
 *	Usage is the same as std::exception.
 *  Support constructor with std::string
 */
class COMMAND_CREATION_EXCEPTION : public std::exception {
public:
	/**
	 *	Constructor with C-string
	 */
	explicit COMMAND_CREATION_EXCEPTION (const char* errorMessage);

	/**
	 *	Constructor with std::string
	 */
	explicit COMMAND_CREATION_EXCEPTION (std::string errorMessage);
};

/**
 *	Exception to be thrown for all exception during execution of command.
 *	Usage is the same as std::exception.
 *	Support constructor with std::string.
 */
class COMMAND_EXECUTION_EXCEPTION : public std::exception {
public:
	/**
	 *	Constructor with C-string
	 */
	explicit COMMAND_EXECUTION_EXCEPTION(const char* errorMessage);

	/**
	 *	Constructor with std::string
	 */
	explicit COMMAND_EXECUTION_EXCEPTION(std::string errorMessage);
};

/**
 *	Super class for all Command sub-classes.
 *	All command sub class inherit this class need to define execute(RunTimeStorage*), canUndo() and undo()
 *	canUndo() is a method determine whether the command can be undo or not by returning a boolean value.
 *	If canUndo() return false, then assert (false) in its undo() method to ensure undo can never be called.
 */
class Command {
protected:

	CommandTokens::PrimaryCommandType _type1;
	CommandTokens::SecondaryCommandType _type2;
	
	/**
	 *	Needed for undo
	 *	If it is NULL, undo cannot be performed. 
	 *  assert(_runTimeStorageExecuted != NULL) is needed for all undo method.
	 */
	RunTimeStorage* _runTimeStorageExecuted;

	/**
	 *	Flag variable about whether the command object have been executed before.
	 *  At the end of all execute method, it should be set to true when it is executed successfully.
	 *	Undo method need to assert this variable is true before it can proceed to execution.
	 */
	bool _statusExecuted;
public:
	/**
	 *	Constructor 
	 *  @param type PrimaryCommandType which correspond to the sub-classes inherited from it.
	 */
	Command(CommandTokens::PrimaryCommandType type);

	/**
	 *	Getter function for PrimaryCommandType of a Command.
	 */
	CommandTokens::PrimaryCommandType getPrimaryCommandType(void);

	/**
	 *	Getter function for SecondaryCommandType of a Command.
	 */
	CommandTokens::SecondaryCommandType getSecondaryCommandType(void);

	/**
	 *	Getter function for RunTimeStorage* the Command have executed on.
	 */
	RunTimeStorage* getRunTimeStorageExecuted();

	/**
	 *	Identifier method whether the Command object is valid for execution or not.
	 */
	bool isValid(void);

	/**
	 *	Identifier method whether the Command object have been executed before or not.
	 */
	bool isExecuted(void);

	/**
	 *	Execution method of a command. Need to be implemented by all sub classes.
	 *	@param runTimeStorage The RunTimeStorage object that the Command are supposed to give instruction to.
	 *	@return UIFeedback An object which contains a vector of tasks to display and a feedback message
	 */
	virtual UIFeedback execute(RunTimeStorage* runTimeStorage) = 0;

	/**
	 *	Undo method of a command. Need to be implemented by all sub classes.
	 *	If the command is not undoable, implement undo method of that sub class as follows: \n
	 *	\code {.cpp}
	 *  UIFeedback undo(void) {
	 *		assert (false); //To ensure it is never called.
	 *		return UIFeedback(); //To return a dummy UIFeedback so that it is compilable.
	 *	}
	 *	\endcode
	 */
	virtual UIFeedback undo(void) = 0;

	/**
	 *	Identifier method about whether the command is undoable or not.
	 *	Undo method should only be called if and only if this method return true
	 */
	virtual bool canUndo(void) = 0;

	/**
	 *	destructor
	 */
	~Command() {}

};
