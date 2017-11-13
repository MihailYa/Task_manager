#include "Task.h"

Task::Task(Task_header_t header_, Task_trigger *&trigger_, Task_act *&act_)
	: header(header_)
{
	trigger = trigger_;
	trigger_ = nullptr;
	
	act = act_;
	act_ = nullptr;
}

Task::~Task()
{
	if (trigger != nullptr)
	{
		delete trigger;
		trigger = nullptr;
	}

	if (act != nullptr)
	{
		delete act;
		act = nullptr;
	}
}

bool Task::calculate_time_left(Time c_time)
{
	if (c_time == last_time)
	{
		trigger->Set_time_left(INF);
		if (trigger->Get_type() == ONCE)
			return false;
	}
	else
		return trigger->calculate_time_left(c_time);

	return true;
}

void Task::make_act()
{
	act->make_act();
}

const bool Task::compare(const Task *left, const Task *right)
{
	return (*(left->trigger) < *(right->trigger));
}

const Task& Task::operator--()
{
	this->header.id--;
	
	return *this;
}

#ifdef DEBUG
void Task::output()
{
	printf("Task #%u\nName: %s\nDesc: %s", header.id, header.name.c_str(), header.desc.c_str());
	printf("\nTrigger:\n");
	trigger->output();
	printf("\nAct:\n");
	act->output();

	std::string s1, s2;
	switch (act->Get_type())
	{
	case ALERT:
		s1 = ((Task_act_alert*)act)->Get_alert_name();
		s2 = ((Task_act_alert*)act)->Get_alert_text();
		break;
	case PROG:
		s1 = ((Task_act_prog*)act)->Get_prog_name();
		s2 = ((Task_act_prog*)act)->Get_prog_params();
		break;
	default:
		throw Task_Exception(WrongActType);
		break;
	}
	printf("\nName:\n%s\nText:\n%s\n", s1.c_str(), s2.c_str());
}
#endif // DEBUG