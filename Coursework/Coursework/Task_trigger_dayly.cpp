#include "Task_trigger_dayly.h"

Task_trigger_dayly::Task_trigger_dayly(Time time_, unsigned int priority_)
	: Task_trigger(DAYLY, time_, priority_)
{
}

bool Task_trigger_dayly::calculate_time_left(Time c_time)
{
	if (time < c_time || is_not_calculated)
	{
		is_not_calculated = false;
		time.Set_dat(c_time.Get_dat());
	}

	time_left = time - c_time;

	return true;
}
