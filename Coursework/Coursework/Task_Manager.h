#pragma once
#include "stdafx.h"
#include "Task.h"

class Task_Manager
{
public:
	Task_Manager(const char* file_name_);
	~Task_Manager();


private:
	void read_task();



	std::string file_name;
	std::fstream *file;
	std::vector<Task> Tasks;
};

