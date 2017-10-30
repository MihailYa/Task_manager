#include "Task_trigger_once.h"

Task_trigger_once::Task_trigger_once(Time time_, unsigned int priority_)
	: Task_trigger(ONCE, time_, priority_)
{
}

void Task_trigger_once::calculate_time_left(Time c_time)
{
	if (time < c_time)
		time_left = -1;
	else
		time_left = time - c_time;
}
