#pragma once
#include "stdafx.h"
#include "Task.h"

class Task_Manager
{
public:
	Task_Manager(const char* file_name_);
	~Task_Manager() throw();


	void create_task(Task_header_t header, Task_trigger *&trigger, Task_act *&act);
	void delete_task(unsigned int id_);

#ifdef DEBUG
	void output();
#endif // DEBUG
private:
	void create_task_private(Task_header_t header, Task_trigger *&trigger, Task_act *&act);
	void delete_task_private(unsigned int id_, bool from_waiter);

	void delete_task_waiter(unsigned int id_);


	/**
	* Read from file @n bytes and check on errors
	* @param s - pointer to char buffer
	* @param n - number of bytes to read
	*/
	void read_(char *s, std::streamsize n);
	void open_(unsigned int mode_);

	bool is_corrupted();

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

	/**
	* Find task by id in m_Tasks vector
	* @param id - id of task
	* @return iterrator, which pointing on the task
	*/
	std::vector<Task*>::iterator find_task_by_id(unsigned int id);

	void skeep_task();


#ifdef DEBUG
public:
#endif // DEBUG
	void waiter_cycle();
	void refresh();

#ifdef DEBUG
private:
#endif // DEBUG
	void waiter();

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

	// Waiter:
	bool m_stop_waiting;
	bool m_exit;
	//System::Threading::Thread ^m_waiter_cycle_thread;
	//std::thread *m_waiter_cycle_thread;
	//gcroot<System::Threading::Thread ^> m_waiter_cycle_thread;
	boost::thread *m_waiter_cycle_thread;

	// Functions states:
	bool m_create_task_started;
	bool m_delete_task_started;
	bool m_refresh_started;
	bool m_waiter_started;
};

