#pragma once
#include "Task_trigger.h"

class Task_trigger_monthly :
	public Task_trigger
{
public:
	Task_trigger_monthly(Time time_, unsigned int priority_, const std::vector<boost::date_time::months_of_year> &month_list_, const std::vector<unsigned int> &days_list_);

	void calculate_time_left(Time c_time);

private:
	std::vector<boost::date_time::months_of_year> month_list;
	std::vector<unsigned int> days_list;

};

