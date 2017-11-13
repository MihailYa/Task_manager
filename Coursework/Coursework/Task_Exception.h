#pragma once
#include "stdafx.h"

enum Task_Exception_error_code_t
{
	ConfigFileNotFound,
	ConfigFileAlreadyOpened,
	ConfigFileAlreadyDeleted,
	ConfigFileCorrupted,
	CanNotOpenConfigFile,
	TaskAlreadyDeleted,
	WaiterThreadCycleAlreadyDeleted,
	TaskIdDoesNotExist,
	TaskIdDoesNotFound,
	EndOfFileWasReached,
	TryAgain,
	WrongTriggerType,
	WrongActType,
	WrongTimeFormat,
	WrongTime,
	WrongExceptionErrorCode
};

class Task_Exception
{
public:
	Task_Exception(Task_Exception_error_code_t error_code_);
	~Task_Exception();

	operator std::string() const;
	
	std::string Get_as_string_with_solution() const;
	Task_Exception_error_code_t Get_error_code() const { return error_code; }

protected:
	Task_Exception_error_code_t error_code;
};

