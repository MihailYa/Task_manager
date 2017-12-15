#include "Task_Exception.h"


Task_Exception::Task_Exception(Task_Exception_error_code_t error_code_)
	: error_code(error_code_)
{
}


Task_Exception::~Task_Exception()
{
}

void Task_Exception::delete_(Task_Exception *&ex_)
{
	exit(EXIT_FAILURE); // Not supported function
	//WrongWeeklyTriggerEveryNWeek
	switch (ex_->Get_error_code())
	{
	case ConfigFileNotFound:
		delete ((ConfigFileNotFound_ex*)ex_);
		break;
	case ConfigFileAlreadyOpened:
		delete ((ConfigFileAlreadyOpened_ex*)ex_);
		break;
	case ConfigFileAlreadyDeleted:
		delete ((ConfigFileAlreadyDeleted_ex*)ex_);
		break;
	case ConfigFileCorrupted:
		delete ((ConfigFileCorrupted_ex*)ex_);
		break;
	case CanNotOpenConfigFile:
		delete ((CanNotOpenConfigFile_ex*)ex_);
		break;
	case CanNotOpenFile:
		delete ((CanNotOpenFile_ex*)ex_);
		break;
	case FileCorrupted:
		delete ((FileCorrupted_ex*)ex_);
		break;
	case TaskAlreadyDeleted:
		delete ((TaskAlreadyDeleted_ex*)ex_);
		break;
	case WaiterThreadCycleAlreadyDeleted:
		delete ((WaiterThreadCycleAlreadyDeleted_ex*)ex_);
		break;
	case TaskIdDoesNotExist:
		delete ((TaskIdDoesNotExist_ex*)ex_);
		break;
	case TaskIdDoesNotFound:
		delete ((TaskIdDoesNotFound_ex*)ex_);
		break;
	case EndOfFileWasReached:
		delete ((EndOfFileWasReached_ex*)ex_);
		break;
	case TryAgain:
		delete ((TryAgain_ex*)ex_);
		break;
	case WrongTriggerType:
		delete ((WrongTriggerType_ex*)ex_);
		break;
	case WrongActType:
		delete ((WrongActType_ex*)ex_);
		break;
	case WrongTimeFormat:
		delete ((WrongTimeFormat_ex*)ex_);
		break;
	case WrongTime:
		delete ((WrongTime_ex*)ex_);
		break;
	case AlertManagerDoesNotExist:
		delete ((AlertManagerDoesNotExist_ex*)ex_);
		break;
	case AlertManagerAlreadyCreated:
		delete ((AlertManagerAlreadyCreated_ex*)ex_);
		break;
	case WrongExceptionErrorCode:
		delete ((WrongExceptionErrorCode_ex*)ex_);
		break;
	default:
		break;
	}
}

Task_Exception::operator std::string() const 
{
	switch (error_code)
	{
	case ConfigFileNotFound:
		return std::string("Configuration file does not found");
		break;
	case ConfigFileAlreadyOpened:
		return std::string("Configuration file was already opened");
		break;
	case ConfigFileAlreadyDeleted:
		return std::string("Configuration file was already deleted");
		break;
	case ConfigFileCorrupted:
		return std::string("Configuration file was corrupted");
		break;
	case CanNotOpenConfigFile:
		return std::string("Can't open configuration file");
		break;
	case CanNotOpenFile:
		return std::string("Can't open file");
		break;
	case FileCorrupted:
		return std::string("File was corrupted");
		break;
	case TaskAlreadyDeleted:
		return std::string("Task was already deleted");
		break;
	case WaiterThreadCycleAlreadyDeleted:
		return std::string("Waiter cycle thread was already deleted");
		break;
	case TaskIdDoesNotExist:
		return std::string("Task with current id does not exist");
		break;
	case TaskIdDoesNotFound:
		return std::string("Can't found task with current id");
		break;
	case EndOfFileWasReached:
		return std::string("End of file was reached");
		break;
	case TryAgain:
		return std::string("Something went wrong");
		break;
	case WrongTriggerType:
		return std::string("Wrong trigger type");
		break;
	case WrongActType:
		return std::string("Wrong act type");
		break;
	case WrongTimeFormat:
		return std::string("Wrong time format");
		break;
	case WrongTime:
		return std::string("Wrong time was specified");
		break;
	case WrongWeeklyTriggerEveryNWeek:
		return std::string("Wrong \"Every n week\" was specified");
		break;
	case WrongMonthlyTriggerDaysVecSize:
		return std::string("Wrong number of days was specified for monthly trigger");
		break;
	case WrongMonthlyTriggerMonthsVecSize:
		return std::string("Wrong number of months was specified for monthly trigger");
		break;
	case AlertManagerDoesNotExist:
		return std::string("Alert Manager does not exist");
		break;
	case AlertManagerAlreadyCreated:
		return std::string("Alert Manager was already created");
		break;
	case WrongExceptionErrorCode:
		return std::string("Wrong exception error code");
		break;
	default:
		throw WrongExceptionErrorCode_ex();
		break;
	}
}

std::string Task_Exception::Get_as_string_with_solution() const
{
	switch (error_code)
	{
	case ConfigFileNotFound:
		return std::string("Error: Configuration file does not found\nSolution: Restart task manager");
		break;
	case ConfigFileAlreadyOpened:
		return std::string("Error: Configuration file was already opened\nSolution: Restart task manager");
		break;
	case ConfigFileAlreadyDeleted:
		return std::string("Error: Config file was already deleted\nSolution: Restart task manager");
		break;
	case ConfigFileCorrupted:
		return std::string("Error: Configuration file was corrupted\nSolution: Restart task manager");
		break;
	case CanNotOpenConfigFile:
		return std::string("Error: Can't open configuration file\nSolution: Restart task manager");
		break;
	case CanNotOpenFile:
		return std::string("Error: Can't open file\nSolution: Close file and retry");
		break;
	case FileCorrupted:
		return std::string("Error: File was corrupted\nSolution: Choose another file");
		break;
	case TaskAlreadyDeleted:
		return std::string("Error: Task was already deleted\nSolution: Restart task manager");
		break;
	case WaiterThreadCycleAlreadyDeleted:
		return std::string("Error: Waiter cycle thread was already deleted\nSolution: Restart task manager");
		break;
	case TaskIdDoesNotExist:
		return std::string("Error: Task with current id does not exist\nSolution: Restart task manager");
		break;
	case TaskIdDoesNotFound:
		return std::string("Error: Can't found task with current id\nSolution: Restart task manager");
		break;
	case EndOfFileWasReached:
		return std::string("Error: End of file was reached\nSolution: Restart task manager");
		break;
	case TryAgain:
		return std::string("Error: Something went wrong\nSolution: Restart task manager");
		break;
	case WrongTriggerType:
		return std::string("Error: Wrong trigger type\nSolution: Restart task manager");
		break;
	case WrongActType:
		return std::string("Error: Wrong act type\nSolution: Restart task manager");
		break;
	case WrongTimeFormat:
		return std::string("Error: Wrong time format\nSolution: Input another time");
		break;
	case WrongTime:
		return std::string("Error: Wrong time was specified\nSolution: Input another time");
		break;
	case WrongWeeklyTriggerEveryNWeek:
		return std::string("Error: Wrong \"Every n week\" was specified\nSolution: Input number which is more then zero");
		break;
	case WrongMonthlyTriggerDaysVecSize:
		return std::string("Error: Wrong number of days was specified for monthly trigger\nSolution: input at least one day");
		break;
	case WrongMonthlyTriggerMonthsVecSize:
		return std::string("Error: Wrong number of months was specified for monthly trigger\nSolution: input at least one month");
		break;
	case AlertManagerDoesNotExist:
		return std::string("Error: Alert Manager does not exist\nSolution:\n\tFor user: Restart task manager\n\tFor developer: Create Alert_Manager before calling this function");
		break;
	case AlertManagerAlreadyCreated:
		return std::string("Error: Alert Manager was already created\nSolution:\n\tFor user: Restrart task manager\n\tFor developer: Be sure you don't create a few Alert_Manager objects");
		break;
	case WrongExceptionErrorCode:
		return std::string("Error: Wrong exception error code\nSolution: Restart task manager");
		break;
	default:
		throw WrongExceptionErrorCode_ex();
		break;
	}
}
