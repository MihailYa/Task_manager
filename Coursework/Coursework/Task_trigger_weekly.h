#pragma once
#include "Task_trigger.h"

class Task_trigger_weekly :
	public Task_trigger
{
public:
	Task_trigger_weekly(Time time_, unsigned int priority_, boost::date_time::weekdays week_day_, unsigned int every_n_week_);

	/**
	* Caclulate time left
	* @param c_time - time for which calculations must be done
	* @return false if trigger must be deleted(because it would never work)
	*/
	bool calculate_time_left(Time c_time);

	//
	//	Getters
	//
	boost::date_time::weekdays Get_week_day() const { return week_day; }
	unsigned int Get_every_n_week() const { return every_n_week; }

private:
	boost::date_time::weekdays week_day;
	unsigned int every_n_week;
};

