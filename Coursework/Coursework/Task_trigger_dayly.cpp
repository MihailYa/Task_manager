#include "Task_trigger_dayly.h"

Task_trigger_dayly::Task_trigger_dayly(Trigger_type_t type_, Time time_, unsigned int priority_)
	: Task_trigger(type_, time_, priority_)
{
}

void Task_trigger_dayly::calculate_time_left(Time c_time)
{
	time.Set_dat(c_time.Get_dat());
	time_left = time - c_time;
}
