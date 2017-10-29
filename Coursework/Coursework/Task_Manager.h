#pragma once
#include "stdafx.h"

class Task_Manager
{
public:
	Task_Manager();
	~Task_Manager();
	
	void stop();

private:
	void Listener();
	
	bool check;
	std::thread *waiter;
};

