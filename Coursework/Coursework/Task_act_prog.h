#pragma once
#include "Task_act.h"

class Task_act_prog :
	public Task_act
{
public:
	Task_act_prog(std::string prog_name_, std::string prog_params_);
	
	void make_act();

private:
	std::string prog_name;
	std::string prog_params;
};

