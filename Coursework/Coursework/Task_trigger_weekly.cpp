#include "Task_trigger_weekly.h"

Task_trigger_weekly::Task_trigger_weekly(Time time_, unsigned int priority_, boost::date_time::weekdays week_day_, unsigned int every_n_week_)
	: Task_trigger(WEEKLY, time_, priority_), week_day(week_day_), every_n_week(every_n_week_)
{
}

void Task_trigger_weekly::calculate_time_left(Time c_time)
{
	if (time < c_time)
		time.Set_next_weekday(week_day);

	// TO DO: make more effectively
#ifdef RELESE
	printf("Make more effectively: Task_trigger_weekly.cpp calculate_time_left()");
	getch();
	exit(EXIT_FAILURE);
#endif // RELESE
	while (time < c_time)
	{
		time += 7 * every_n_week;
	}

	time_left = time - c_time;
}
