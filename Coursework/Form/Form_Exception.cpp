#include "stdafx.h"
#include "Form_Exception.h"


namespace TaskManagerForm
{

	Form_Exception::Form_Exception(Form_Exception_error_code_t error_code_)
		: error_code(error_code_)
	{
	}


	Form_Exception::~Form_Exception()
	{
	}

	void Form_Exception::delete_(Form_Exception *&ex_)
	{
		switch (ex_->Get_error_code())
		{
		case TaskManagerForm::TaskHeaderNotFound:
			delete (TaskManagerForm::TaskHeaderNotFound_ex*)ex_;
			break;
		case TaskManagerForm::TaskDescNotFound:
			delete (TaskManagerForm::TaskDescNotFound_ex*)ex_;
			break;
		case TaskManagerForm::TrigTimeNotFound:
			delete (TaskManagerForm::TrigTimeNotFound_ex*)ex_;
			break;
		case TaskManagerForm::TrigTimeWrongFormat:
			delete (TaskManagerForm::TrigTimeWrongFormat_ex*)ex_;
			break;
		case TaskManagerForm::WeeklyTrigEveryNWeekNotFound:
			delete (TaskManagerForm::WeeklyTrigEveryNWeekNotFound_ex*)ex_;
			break;
		case TaskManagerForm::WeeklyTrigWDaysNotFound:
			delete (TaskManagerForm::WeeklyTrigWDaysNotFound_ex*)ex_;
			break;
		case TaskManagerForm::MonthlyTrigMonthsNotFound:
			delete (TaskManagerForm::MonthlyTrigMonthsNotFound_ex*)ex_;
			break;
		case TaskManagerForm::MonthlyTrigDaysNotFound:
			delete (TaskManagerForm::MonthlyTrigDaysNotFound_ex*)ex_;
			break;
		case TaskManagerForm::MessageActHeaderNotFound:
			delete (TaskManagerForm::MessageActHeaderNotFound_ex*)ex_;
			break;
		case TaskManagerForm::MessageActTextNotFound:
			delete (TaskManagerForm::MessageActTextNotFound_ex*)ex_;
			break;
		case TaskManagerForm::ProgActNameNotFound:
			delete (TaskManagerForm::ProgActNameNotFound_ex*)ex_;
			break;
		case TaskManagerForm::WrongExceptionErrorCode:
			delete (TaskManagerForm::WrongExceptionErrorCode_ex*)ex_;
			break;
		default:
			throw new TaskManagerForm::WrongExceptionErrorCode_ex;
			break;
		}
	}

	Form_Exception::operator std::string() const
	{
		switch (error_code)
		{
		case TaskManagerForm::TaskHeaderNotFound:
			return std::string("Task name not found");
			break;
		case TaskManagerForm::TaskDescNotFound:
			return std::string("Task description not found");
			break;
		case TaskManagerForm::TrigTimeNotFound:
			return std::string("Task trigger time not found");
			break;
		case TaskManagerForm::TrigTimeWrongFormat:
			return std::string("Wrong trigger time format");
			break;
		case TaskManagerForm::WeeklyTrigEveryNWeekNotFound:
			return std::string("\"Every N week\" not found");
			break;
		case TaskManagerForm::WeeklyTrigWDaysNotFound:
			return std::string("Trigger weekdays not found");
			break;
		case TaskManagerForm::MonthlyTrigMonthsNotFound:
			return std::string("Trigger months not found");
			break;
		case TaskManagerForm::MonthlyTrigDaysNotFound:
			return std::string("Trigger days not found");
			break;
		case TaskManagerForm::MessageActHeaderNotFound:
			return std::string("Message header not found");
			break;
		case TaskManagerForm::MessageActTextNotFound:
			return std::string("Message text not found");
			break;
		case TaskManagerForm::ProgActNameNotFound:
			return std::string("Program name not found");
			break;
		case TaskManagerForm::WrongExceptionErrorCode:
			return std::string("Wrong exception error code");
			break;
		default:
			throw new TaskManagerForm::WrongExceptionErrorCode_ex;
			break;
		}
	}

	std::string Form_Exception::Get_as_string_with_solution() const
	{
		switch (error_code)
		{
		case TaskManagerForm::TaskHeaderNotFound:
			return std::string("Error: Task name not found\nSolution: Input task name");
			break;
		case TaskManagerForm::TaskDescNotFound:
			return std::string("Error: Task description not found\nSolution: Input task description");
			break;
		case TaskManagerForm::TrigTimeNotFound:
			return std::string("Error: Trigger time not found\nSolution: Input trigger time");
			break;
		case TaskManagerForm::TrigTimeWrongFormat:
			return std::string("Error: Wrong trigger time format\nSolution: Input time in format dd.mm.yyyy HH:MM");
			break;
		case TaskManagerForm::WeeklyTrigEveryNWeekNotFound:
			return std::string("Error: \"Every N week\" not found\nSolution: Input \"Every N week\"");
			break;
		case TaskManagerForm::WeeklyTrigWDaysNotFound:
			return std::string("Error: Trigger weekdays not found\nSolution: Choose at least one weekday");
			break;
		case TaskManagerForm::MonthlyTrigMonthsNotFound:
			return std::string("Error: Trigger months not found\nSolution: Choose at least one month");
			break;
		case TaskManagerForm::MonthlyTrigDaysNotFound:
			return std::string("Error: Trigger days not found\nSolution: Choose at least one day");
			break;
		case TaskManagerForm::MessageActHeaderNotFound:
			return std::string("Error: Message header not found\nSolution: Input message header");
			break;
		case TaskManagerForm::MessageActTextNotFound:
			return std::string("Error: Message text not found\nSolution: Input message text");
			break;
		case TaskManagerForm::ProgActNameNotFound:
			return std::string("Error: Program name not found\nSolution: Input program name");
			break;
		case TaskManagerForm::WrongExceptionErrorCode:
			return std::string("Error: Wrong exception error code\nSolution: Restart program");
			break;
		default:
			throw new TaskManagerForm::WrongExceptionErrorCode_ex;
			break;
		}
	}

}