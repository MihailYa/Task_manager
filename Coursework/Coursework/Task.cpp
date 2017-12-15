#include "Task.h"

Task::Task(Task_header_t header_, Task_trigger *&trigger_, Task_act *&act_)
	: header(header_), m_was_maked(false)
{
	trigger = trigger_;
	trigger_ = nullptr;
	
	act = act_;
	act_ = nullptr;
}

Task::Task(const Task &right)
	:m_was_maked(false)
{
	header = right.header;

	switch (right.trigger->Get_type())
	{
	case DAYLY:
		trigger = new Task_trigger_dayly(*((Task_trigger_dayly*)right.trigger));
		break;
	case WEEKLY:
		trigger = new Task_trigger_weekly(*((Task_trigger_weekly*)right.trigger));
		break;
	case MONTHLY:
		trigger = new Task_trigger_monthly(*((Task_trigger_monthly*)right.trigger));
		break;
	case ONCE:
		trigger = new Task_trigger_once(*((Task_trigger_once*)right.trigger));
		break;
	case ENTRANCE:
		trigger = new Task_trigger_entrance(*((Task_trigger_entrance*)right.trigger));
		break;
	default:
		throw WrongTriggerType_ex();
		break;
	}

	switch (right.act->Get_type())
	{
	case PROG:
		act = new Task_act_prog(*((Task_act_prog*)right.act));
		break;
	case ALERT:
		act = new Task_act_prog(*((Task_act_prog*)right.trigger));
		break;
	default:
		throw WrongActType_ex();
		break;
	}
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
	if (m_was_maked && trigger->Get_type() == ENTRANCE)
	{
		trigger->Set_time_left(INF);
		return true;
	}

	if (c_time == last_time)
	{
		trigger->Set_time_left(INF);
		if (trigger->Get_type() == ONCE)
			return false;
	}
	else
	{
		trigger->calculate_time_left(c_time);
	}

	return true;
}

void Task::make_act()
{
	m_was_maked = true;
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
		throw WrongActType_ex();
		break;
	}
	printf("\nName:\n%s\nText:\n%s\n", s1.c_str(), s2.c_str());
}
#endif // DEBUG