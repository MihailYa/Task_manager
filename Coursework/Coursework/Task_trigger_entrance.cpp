#include "Task_trigger_entrance.h"

Task_trigger_entrance::Task_trigger_entrance(Time time_, unsigned int priority_)
	: Task_trigger(ENTRANCE, time_, priority_)
{
}

void Task_trigger_entrance::calculate_time_left(Time c_time)
{
	if (c_time >= time)
		time_left = 0;
	else
		time_left = INF;
}
