#include "Task_trigger.h"

Task_trigger::Task_trigger(Trigger_type_t type_, Time time_, unsigned int priority_)
	: type(type_), time(time_), time_begin(time_), priority(priority_), time_left(INF),
	is_not_calculated(true)
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

#ifdef DEBUG
void Task_trigger::output()
{
	printf("Trigger type: ");
	switch (type)
	{
	case DAYLY:
		printf("DAYLY");
		break;
	case WEEKLY:
		printf("WEEKLY");
		break;
	case MONTHLY:
		printf("MONTHLY");
		break;
	case ONCE:
		printf("ONCE");
		break;
	case ENTRANCE:
		printf("ENTRANCE");
		break;
	default:
		printf("ERROR");
		break;
	}
	printf("\nTime:");
	time.output();
	printf("\nPriotiry: %u\nTime left: %d", priority, time_left);
}
#endif // DEBUG