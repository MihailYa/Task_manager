#pragma once
#include "Task_trigger.h"

class Task_trigger_monthly :
	public Task_trigger
{
public:
	Task_trigger_monthly(Time time_, unsigned int priority_, const std::vector<boost::date_time::months_of_year> &month_list_, const std::vector<unsigned int> &days_list_);

	/**
	* Caclulate time left
	* @param c_time - time for which calculations must be done
	* @return false if trigger must be deleted(because it would never work)
	*/
	bool calculate_time_left(Time c_time);

	const std::vector<boost::date_time::months_of_year> Get_month_list() const { return month_list; }
	const std::vector<unsigned int> Get_days_list() const { return days_list; }

private:
	std::vector<boost::date_time::months_of_year> month_list;
	std::vector<unsigned int> days_list;

};

