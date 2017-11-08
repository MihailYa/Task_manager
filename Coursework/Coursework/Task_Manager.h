#pragma once
#include "stdafx.h"
#include "Task.h"

class Task_Manager
{
public:
	Task_Manager(const char* file_name_);
	~Task_Manager();

	void create_task(Task_header_t header, Task_trigger *&trigger, Task_act *&act);
	void delete_task(unsigned int id_);

#ifdef DEBUG
	void output();
#endif // DEBUG
private:
	/*
	read_task:
		read_header
		read_trigger
		read_act
	*/
	Task*& read_task(unsigned int id);
	Task_header_t read_header(unsigned int id);
	Task_trigger*& read_trigger();
	Task_act*& read_act();

	void write_header(Task_header_t header);
	void write_trigger(Task_trigger *&trigger);
	void write_act(Task_act *&act);

	void skeep_task();

	void refresh();
	//bool stop;
	//void refresh();
	//void waiter();

	std::string m_file_name;
	/**
	* Struct of .task file:
	
		unsigned int n // Number of tasks
		*Task struct:
		{
			*header struct:
			{
				unsigned int n; // Size of name
				char name[n];

				unsigned int n; // Size of desc
				char desc[n];
			}

			*trigger struct:
			{
				Trigger_type
				Time
				priority
				// If weekly:
				boost::date_time::weekdays week_day
				unsigned int every_n_week
				// If monthly
				unsigned int n; // Size of month_list
				boost::date_time::months_of_year month_list[n]
				unsigned int n; // Size of days_list
				unsigned int days_list[n]
			}

			*act struct:
			{
				act_type
				unsigned int n; // Size of name
				char name[n];
				unsigned int n; // Size of text
				char text[n];
			}
		}
	*/
	std::fstream *m_file;
	std::vector<Task*> m_Tasks;
	int m_last_id;
};

