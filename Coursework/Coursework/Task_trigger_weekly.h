#pragma once
#include "Task_trigger.h"

class Task_trigger_weekly :
	public Task_trigger
{
public:
	Task_trigger_weekly(Trigger_type_t type_, Time time_, unsigned int priority_, short week_day_, unsigned int every_n_week_);

	void calculate_time_left(Time c_time);

private:
	short week_day;
	unsigned int every_n_week;
};

