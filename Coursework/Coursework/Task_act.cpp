#include "Task_act.h"

Task_act::Task_act(Task_act_type_t type_)
	: type(type_)
{
}

#ifdef DEBUG
void Task_act::output()
{
	printf("Act type: ");
	switch (type)
	{
	case PROG:
		printf("PROG");
		break;
	case ALERT:
		printf("ALERT");
		break;
	default:
		printf("ERROR");
		break;
	}
}
#endif // DEBUG