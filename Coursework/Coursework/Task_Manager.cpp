#include "Task_Manager.h"

Task_Manager::Task_Manager(const char* file_name_)
{
	file_name = file_name_;
	file = new std::fstream(file_name, std::ifstream::in | std::ifstream::binary);



	//waiter = new std::thread(&Task_Manager::Listener, this);
}

Task_Manager::~Task_Manager()
{
}

void read_task()
{
	
}
