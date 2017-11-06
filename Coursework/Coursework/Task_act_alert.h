#pragma once
#include "Task_act.h"

class Task_act_alert :
	public Task_act
{
public:
	Task_act_alert(std::string alert_name_, std::string alert_text_);
	
	void make_act();

	std::string Get_alert_name() const { return alert_name; }
	std::string Get_alert_text() const { return alert_text; }

private:
	std::string alert_name;
	std::string alert_text;
};

