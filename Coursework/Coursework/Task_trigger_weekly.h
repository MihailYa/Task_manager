#pragma once
#include "Task_trigger.h"

class Task_trigger_weekly :
	public Task_trigger
{
public:
	Task_trigger_weekly(Time time_, unsigned int priority_, boost::date_time::weekdays week_day_, unsigned int every_n_week_);

	void calculate_time_left(Time c_time);

private:
	boost::date_time::weekdays week_day;
	unsigned int every_n_week;
};

