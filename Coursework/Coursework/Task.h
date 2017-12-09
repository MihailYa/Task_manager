#pragma once
// Task triggers:
#include "Task_trigger_dayly.h"
#include "Task_trigger_weekly.h"
#include "Task_trigger_monthly.h"
#include "Task_trigger_once.h"
#include "Task_trigger_entrance.h"
// Task acts:
#include "Task_act_prog.h"
#include "Task_act_alert.h"

struct Task_header_t
{
	unsigned int id;
	std::string name;
	std::string desc;
};

class Task
{
public:
	Task(Task_header_t header_, Task_trigger *&trigger_, Task_act *&act_);

	Task(const Task &right);

	~Task();

	/**
	* Caclulate time left for trigger
	* @param c_time - time for which calculations must be done
	* @return false if task must be deleted(because it would never be done)
	*/
	bool calculate_time_left(Time c_time);
	void make_act();
	
	static const bool compare(const Task *left, const Task *right);

	//
	// Getters
	//
	unsigned int Get_id() const { return header.id; }
	int Get_time_left() const { return trigger->Get_time_left(); }
	Trigger_type_t Get_trigger_type() const { return trigger->Get_type(); }
	Task_header_t Get_header() const { return header; }

#ifdef DEBUG
	Task_trigger* Get_trigger() const { return trigger; }
#endif // DEBUG


	//
	// Setters
	//
	void Set_last_time(Time last_time_) { last_time = last_time_; }
	void Set_was_maked(bool was_maked) { m_was_maked = was_maked; }

	const Task& operator--();

#ifdef DEBUG
	void output();
#endif // DEBUG

private:
	Task_header_t header;
	Task_trigger *trigger;
	Task_act *act;

	Time last_time; // Last time when task has been done
	bool m_was_maked;
};

