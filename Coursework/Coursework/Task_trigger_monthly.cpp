#include "Task_trigger_monthly.h"



Task_trigger_monthly::Task_trigger_monthly(Time time_, unsigned int priority_, const std::vector<boost::date_time::months_of_year> &month_list_, const std::vector<unsigned int> &days_list_)
	: Task_trigger(MONTHLY, time_, priority_), month_list(month_list_), days_list(days_list_)
{
	if (month_list.size() == 0)
		throw WrongMonthlyTriggerMonthsVecSize_ex();
	if (days_list.size() == 0)
		throw WrongMonthlyTriggerDaysVecSize_ex();

	std::sort(month_list.begin(), month_list.end());
	std::unique(month_list.begin(), month_list.end());

	std::sort(days_list.begin(), days_list.end());
	std::unique(days_list.begin(), days_list.end());
}

bool Task_trigger_monthly::calculate_time_left(Time c_time)
{
	if (time < c_time || is_not_calculated)
	{
		is_not_calculated = false;
		Time_t tmp = time.Get_time();
		time = Time(c_time.Get_dat(), tmp.hours, tmp.minutes);
		if (time < c_time)
			time += 1;
		time.Set_next_month_day(month_list, days_list);
	}
	time_left = time - c_time;

	return true;
}
