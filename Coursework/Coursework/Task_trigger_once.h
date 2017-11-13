#pragma once
#include "Task_trigger.h"

class Task_trigger_once :
	public Task_trigger
{
public:
	Task_trigger_once(Time time_, unsigned int priority_);

	/**
	* Caclulate time left
	* @param c_time - time for which calculations must be done
	* @return false if trigger must be deleted(because it would never work)
	*/
	bool calculate_time_left(Time c_time);
};

