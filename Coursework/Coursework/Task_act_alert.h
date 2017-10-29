#pragma once
#include "Task_act.h"

class Task_act_alert :
	public Task_act
{
public:
	Task_act_alert(std::string alert_name_, std::string alert_text_);
	
	void make_act();

private:
	std::string alert_name;
	std::string alert_text;
};

