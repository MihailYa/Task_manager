#include "Task_Exception.h"



Task_Exception::Task_Exception(Task_Exception_error_code_t error_code_)
	: error_code(error_code_)
{
}


Task_Exception::~Task_Exception()
{
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
	case WrongExceptionErrorCode:
		return std::string("Wrong exception error code");
		break;
	default:
		throw Task_Exception(WrongExceptionErrorCode);
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
		return std::string("Erro: Configuration file was corrupted\nSolution: Restart task manager");
		break;
	case CanNotOpenConfigFile:
		return std::string("Erro: Can't open configuration file\nSolution: Restart task manager");
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
	case WrongExceptionErrorCode:
		return std::string("Error: Wrong exception error code\nSolution: Restart task manager");
		break;
	default:
		throw Task_Exception(WrongExceptionErrorCode);
		break;
	}
}
