#include "Task_trigger_monthly.h"



Task_trigger_monthly::Task_trigger_monthly(Time time_, unsigned int priority_, const std::vector<boost::date_time::months_of_year> &month_list_, const std::vector<unsigned int> &days_list_)
	: Task_trigger(MONTHLY, time_, priority_), month_list(month_list_), days_list(days_list_)
{
}

bool Task_trigger_monthly::calculate_time_left(Time c_time)
{
	time.Set_dat(c_time.Get_dat());
	time.Set_next_month_day(month_list, days_list);

	time_left = time - c_time;

	return true;
}
