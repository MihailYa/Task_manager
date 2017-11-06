#pragma once
#include "Task_act.h"

class Task_act_prog :
	public Task_act
{
public:
	Task_act_prog(std::string prog_name_, std::string prog_params_);
	
	void make_act();

	std::string Get_prog_name() const { return prog_name; }
	std::strign Get_prog_params() const { return prog_params; }

private:
	std::string prog_name;
	std::string prog_params;
};

