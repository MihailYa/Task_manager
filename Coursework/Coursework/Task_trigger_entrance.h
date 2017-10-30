#pragma once
#include "Task_trigger.h"

class Task_trigger_entrance :
	public Task_trigger
{
public:
	Task_trigger_entrance();
	void calculate_time_left(Time c_time);
};

