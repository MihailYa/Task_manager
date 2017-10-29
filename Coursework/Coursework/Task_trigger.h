#pragma once
#include "stdafx.h"
#include "globals.h"

#include "Time.h"

enum Trigger_type_t
{
	DAYLY,
	WEEKLY,
	MONTHLY,
	ONCE,
	ENTRANCE
};

class Task_trigger
{
public:
	Task_trigger();
	~Task_trigger();

	Task_trigger(Trigger_type_t type_, Time time_, unsigned int priority_);
	virtual void calculate_time_left(Time c_time) = 0;
	unsigned int Get_time_left() const { return time_left; }
		
protected:
	Trigger_type_t type;
	Time time;
	unsigned int priority;
	int time_left; // In minutes
};

