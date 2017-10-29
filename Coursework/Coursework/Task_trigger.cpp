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
