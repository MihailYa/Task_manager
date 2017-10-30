#include "Task_trigger.h"

Task_trigger::Task_trigger(Trigger_type_t type_, Time time_, unsigned int priority_)
	: type(type_), time(time_), priority(priority_), time_left(INF)
{
}

Task_trigger::Task_trigger()
{
}

Task_trigger::~Task_trigger()
{
}

const bool Task_trigger::operator<(const Task_trigger &right) const
{
	if (time_left < right.time_left || (time_left == right.time_left && priority < right.priority))
		return true;
	
	return false;
}
