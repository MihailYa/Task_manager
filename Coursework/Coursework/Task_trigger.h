#pragma once
#include "stdafx.h"
#include "globals.h"

#include "_Time.h"

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
	virtual ~Task_trigger();

	Task_trigger(Trigger_type_t type_, Time time_, unsigned int priority_);

	const bool operator<(const Task_trigger &right) const;

	/**
	* Caclulate time left
	* @param c_time - time for which calculations must be done
	* @return false if trigger must be deleted(because it would never work)
	*/
	virtual bool calculate_time_left(Time c_time) = 0;

	//
	//	Getters
	//
	unsigned int Get_time_left() const { return time_left; }
	unsigned int Get_priority() const { return priority; }
	Trigger_type_t Get_type() const { return type; }
	Time Get_time() const { return time; }

	//
	// Setters
	//
	void Set_time_left(int time_left_) { time_left = time_left_; }

#ifdef DEBUG
	void output();
#endif // DEBUG
		
protected:
	Trigger_type_t type;
	Time time;		 // Time of next triggering
	Time time_begin; // Time from which begin triggering
	unsigned int priority;
	unsigned int time_left; // In minutes
	bool is_not_calculated;
};

