#include "Task_act_prog.h"

Task_act_prog::Task_act_prog(std::string prog_name_, std::string prog_params_)
	: Task_act(PROG), prog_name(prog_name_), prog_params(prog_params_)
{
}

void Task_act_prog::make_act()
{
	system(("start " + prog_name + " " + prog_params).c_str());
}
