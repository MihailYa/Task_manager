#include "Task_Manager.h"

Task_Manager::Task_Manager()
{
	waiter = new std::thread(&Task_Manager::Listener, this);
}

Task_Manager::~Task_Manager()
{
}

void Task_Manager::Listener()
{
	void sleep(unsigned int time, bool &check);
	check = true;
	sleep(10000, check);
	printf("lol");
}

void sleep(unsigned int time, bool &check)
{
	int n = time / 1000;
	for (int i = 0; i < n; i++)
	{
		if (!check)
			return;
		Sleep(1000);
	}
}

void Task_Manager::stop()
{
	check = false;
	
}