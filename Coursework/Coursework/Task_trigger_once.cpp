#include "Task_trigger_once.h"

Task_trigger_once::Task_trigger_once(Time time_, unsigned int priority_)
	: Task_trigger(ONCE, time_, priority_)
{
}

bool Task_trigger_once::calculate_time_left(Time c_time)
{
	if (c_time <= time)
		time_left = time - c_time;
	else
		return false;

	return true;
}
