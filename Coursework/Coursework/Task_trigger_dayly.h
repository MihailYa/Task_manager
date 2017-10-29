#pragma once
#include "Task_trigger.h"

class Task_trigger_dayly :
	public Task_trigger
{
public:
	Task_trigger_dayly(Trigger_type_t type_, Time time_, unsigned int priority_);

	void calculate_time_left(Time c_time);
};

