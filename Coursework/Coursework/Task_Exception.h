#pragma once
#include "stdafx.h"

enum Task_Exception_error_code_t
{
	ConfigFileNotFound,
	ConfigFileAlreadyOpened,
	ConfigFileAlreadyDeleted,
	ConfigFileCorrupted,
	CanNotOpenConfigFile,
	CanNotOpenFile,
	FileCorrupted,
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
	AlertManagerDoesNotExist,
	AlertManagerAlreadyCreated,
	WrongExceptionErrorCode
};

class Task_Exception
{
public:
	Task_Exception(Task_Exception_error_code_t error_code_);
	virtual ~Task_Exception();

	static void delete_(Task_Exception *&ex_);

	operator std::string() const;
	
	std::string Get_as_string_with_solution() const;
	Task_Exception_error_code_t Get_error_code() const { return error_code; }

protected:
	Task_Exception_error_code_t error_code;
};

class ConfigFileNotFound_ex : public Task_Exception
{
public:
	ConfigFileNotFound_ex() : Task_Exception(ConfigFileNotFound) {}
};

class ConfigFileAlreadyOpened_ex : public Task_Exception
{
public:
	ConfigFileAlreadyOpened_ex() : Task_Exception(ConfigFileAlreadyOpened) {}
};

class ConfigFileAlreadyDeleted_ex : public Task_Exception
{
public:
	ConfigFileAlreadyDeleted_ex() : Task_Exception(ConfigFileAlreadyDeleted) {}
};

class ConfigFileCorrupted_ex : public Task_Exception
{
public:
	ConfigFileCorrupted_ex() : Task_Exception(ConfigFileCorrupted) {}
};

class CanNotOpenConfigFile_ex : public Task_Exception
{
public:
	CanNotOpenConfigFile_ex() : Task_Exception(CanNotOpenConfigFile) {}
};

class CanNotOpenFile_ex : public Task_Exception
{
public:
	CanNotOpenFile_ex() : Task_Exception(CanNotOpenFile) {}
};

class FileCorrupted_ex : public Task_Exception
{
public:
	FileCorrupted_ex() : Task_Exception(FileCorrupted) {}
};

class TaskAlreadyDeleted_ex : public Task_Exception
{
public:
	TaskAlreadyDeleted_ex() : Task_Exception(TaskAlreadyDeleted) {}
};

class WaiterThreadCycleAlreadyDeleted_ex : public Task_Exception
{
public:
	WaiterThreadCycleAlreadyDeleted_ex() : Task_Exception(WaiterThreadCycleAlreadyDeleted) {}
};

class TaskIdDoesNotExist_ex : public Task_Exception
{
public:
	TaskIdDoesNotExist_ex() : Task_Exception(TaskIdDoesNotExist) {}
};

class TaskIdDoesNotFound_ex : public Task_Exception
{
public:
	TaskIdDoesNotFound_ex() : Task_Exception(TaskIdDoesNotFound) {}
};

class EndOfFileWasReached_ex : public Task_Exception
{
public:
	EndOfFileWasReached_ex() : Task_Exception(EndOfFileWasReached) {}
};

class TryAgain_ex : public Task_Exception
{
public:
	TryAgain_ex() : Task_Exception(TryAgain) {}
};

class WrongTriggerType_ex : public Task_Exception
{
public:
	WrongTriggerType_ex() : Task_Exception(WrongTriggerType) {}
};

class WrongActType_ex : public Task_Exception
{
public:
	WrongActType_ex() : Task_Exception(WrongActType) {}
};

class WrongTimeFormat_ex : public Task_Exception
{
public:
	WrongTimeFormat_ex() : Task_Exception(WrongTimeFormat) {}
};

class WrongTime_ex : public Task_Exception
{
public:
	WrongTime_ex() : Task_Exception(WrongTime) {}
};

class AlertManagerDoesNotExist_ex : public Task_Exception
{
public:
	AlertManagerDoesNotExist_ex() : Task_Exception(AlertManagerDoesNotExist) {}
};

class AlertManagerAlreadyCreated_ex : public Task_Exception
{
public:
	AlertManagerAlreadyCreated_ex() : Task_Exception(AlertManagerAlreadyCreated) {}
};

class WrongExceptionErrorCode_ex : public Task_Exception
{
public:
	WrongExceptionErrorCode_ex() : Task_Exception(WrongExceptionErrorCode) {}
};
