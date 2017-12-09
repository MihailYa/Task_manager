#pragma once
#include "stdafx.h"

namespace TaskManagerForm
{

	enum Form_Exception_error_code_t
	{
		TaskHeaderNotFound,
		TaskDescNotFound,
		TrigTimeNotFound,
		TrigTimeWrongFormat,
		WeeklyTrigEveryNWeekNotFound,
		WeeklyTrigWDaysNotFound,
		MonthlyTrigMonthsNotFound,
		MonthlyTrigDaysNotFound,
		MessageActHeaderNotFound,
		MessageActTextNotFound,
		ProgActNameNotFound,
		WrongExceptionErrorCode
	};

	class Form_Exception
	{
	public:
		Form_Exception(Form_Exception_error_code_t error_code_);
		~Form_Exception();

		static void delete_(Form_Exception *&ex_);

		operator std::string() const;

		std::string Get_as_string_with_solution() const;
		Form_Exception_error_code_t Get_error_code() const { return error_code; }

	protected:
		Form_Exception_error_code_t error_code;
	};
		
	class TaskHeaderNotFound_ex : public Form_Exception
	{
	public:
		TaskHeaderNotFound_ex() : Form_Exception(TaskHeaderNotFound) {}
	};

	class TaskDescNotFound_ex : public Form_Exception
	{
	public:
		TaskDescNotFound_ex() : Form_Exception(TaskDescNotFound) {}
	};

	class TrigTimeNotFound_ex : public Form_Exception
	{
	public:
		TrigTimeNotFound_ex() : Form_Exception(TrigTimeNotFound) {}
	};
	
	class TrigTimeWrongFormat_ex : public Form_Exception
	{
	public:
		TrigTimeWrongFormat_ex() : Form_Exception(TrigTimeWrongFormat) {}
	};

	class WeeklyTrigEveryNWeekNotFound_ex : public Form_Exception
	{
	public:
		WeeklyTrigEveryNWeekNotFound_ex() : Form_Exception(WeeklyTrigEveryNWeekNotFound) {}
	};

	class WeeklyTrigWDaysNotFound_ex : public Form_Exception
	{
	public:
		WeeklyTrigWDaysNotFound_ex() : Form_Exception(WeeklyTrigWDaysNotFound) {}
	};

	class MonthlyTrigMonthsNotFound_ex : public Form_Exception
	{
	public:
		MonthlyTrigMonthsNotFound_ex() : Form_Exception(MonthlyTrigMonthsNotFound) {}
	};

	class MonthlyTrigDaysNotFound_ex : public Form_Exception
	{
	public:
		MonthlyTrigDaysNotFound_ex() : Form_Exception(MonthlyTrigDaysNotFound) {}
	};

	class MessageActHeaderNotFound_ex : public Form_Exception
	{
	public:
		MessageActHeaderNotFound_ex() : Form_Exception(MessageActHeaderNotFound) {}
	};

	class MessageActTextNotFound_ex : public Form_Exception
	{
	public:
		MessageActTextNotFound_ex() : Form_Exception(MessageActTextNotFound) {}
	};

	class ProgActNameNotFound_ex : public Form_Exception
	{
	public:
		ProgActNameNotFound_ex() : Form_Exception(ProgActNameNotFound) {}
	};

	class WrongExceptionErrorCode_ex : public Form_Exception
	{
	public:
		WrongExceptionErrorCode_ex() : Form_Exception(WrongExceptionErrorCode) {}
	};

}