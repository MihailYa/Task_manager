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
	std::string name;
	std::string desc;
};

class Task
{
public:
	Task(Task_header_t header_, Task_trigger *&trigger_, Task_act *&act_);
	~Task();

	void calculate_time_left(Time c_time);
	void make_act();

	static const bool compare(const Task &left, const Task &right);
private:
	Task_header_t header;
	Task_trigger *trigger;
	Task_act *act;
};

