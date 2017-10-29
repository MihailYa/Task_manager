#include "Task_trigger_weekly.h"

Task_trigger_weekly::Task_trigger_weekly(Trigger_type_t type_, Time time_, unsigned int priority_, short week_day_, unsigned int every_n_week_)
	: Task_trigger(type_, time_, priority_), week_day(week_day_), every_n_week(every_n_week_)
{
}

void Task_trigger_weekly::calculate_time_left(Time c_time)
{
	if (time < c_time)
		time.Set_next_weekday(week_day);

	// TO DO: make more effectively
	while (time < c_time)
	{
		time += 7 * every_n_week;
	}

	time_left = time - c_time;
}
