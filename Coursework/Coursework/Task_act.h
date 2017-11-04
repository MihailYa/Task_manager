#pragma once
#include "stdafx.h"

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

protected:
	Task_act_type_t type;
};

