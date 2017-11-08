#pragma once
#include "stdafx.h"
#include "globals.h"

enum Task_act_type_t
{
	PROG,
	ALERT
};

class Task_act
{
public:
	Task_act(Task_act_type_t type_);
	virtual void make_act() = 0;

	Task_act_type_t Get_type() const { return type; }

#ifdef DEBUG
	void output();
#endif // DEBUG

protected:
	Task_act_type_t type;
};

