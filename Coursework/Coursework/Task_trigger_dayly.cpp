#include "Task_trigger_dayly.h"

Task_trigger_dayly::Task_trigger_dayly(Time time_, unsigned int priority_)
	: Task_trigger(DAYLY, time_, priority_)
{
}

void Task_trigger_dayly::calculate_time_left(Time c_time)
{
	time.Set_dat(c_time.Get_dat());
	time_left = time - c_time;
}
