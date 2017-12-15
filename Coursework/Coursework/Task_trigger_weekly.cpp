#include "Task_trigger_weekly.h"

Task_trigger_weekly::Task_trigger_weekly(Time time_, unsigned int priority_, boost::date_time::weekdays week_day_, unsigned int every_n_week_)
	: Task_trigger(WEEKLY, time_, priority_), week_day(week_day_), every_n_week(every_n_week_)
{
	if (every_n_week <= 0)
		throw WrongWeeklyTriggerEveryNWeek_ex();
}

bool Task_trigger_weekly::calculate_time_left(Time c_time)
{
	if (time < c_time)
		time.Set_next_weekday(week_day);

	if (time < c_time)
	{
		int num_of_weeks = c_time%time;
		int num_of_weeks_add = (num_of_weeks / every_n_week)*every_n_week;
		time += num_of_weeks_add * 7;
	}
	if (time < c_time)
		time += every_n_week * 7;

	time_left = time - c_time;

	return true;
}
