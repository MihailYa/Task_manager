#include "Task_trigger_monthly.h"



Task_trigger_monthly::Task_trigger_monthly(Trigger_type_t type_, Time time_, unsigned int priority_, const std::vector<unsigned int> &month_list_, const std::vector<unsigned int> &days_list_)
	: Task_trigger(type_, time_, priority_), month_list(month_list_), days_list(days_list_)
{
}

void Task_trigger_monthly::calculate_time_left(Time c_time)
{
	Time tmp = c_time;
	tmp.Set_next_month_day(month_list, days_list);
	time = tmp;

	time_left = time - c_time;
}
