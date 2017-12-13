#pragma once
#include "stdafx.h"
#include "Task.h"
#include "Alert_Manager.h"

struct Task_Info_t
{
	Task_header_t header;
	int time_left;
};

class Task_Manager
{
public:
	Task_Manager(const char* file_name_, bool entrance);
	~Task_Manager() throw();


	void create_task(Task_header_t header, Task_trigger *&trigger, Task_act *&act);
	void delete_task(unsigned int id_);

	void import_task(const char *import_file_name_);
	void export_task(const char *export_file_name_, unsigned int id_);

	std::vector<Task_Info_t> Get_task_info();

#ifdef DEBUG
	void output();
#endif // DEBUG
private:
	/**
	* Create task. This function can be called only from create_task function
	* @param header - header of task
	* @param trigger - trigger of task
	* @param act - action of task
	* @exceptions WrongTriggerType, WrongActType, WrongTimeFormat, WrongTime
	*/
	void create_task_private(Task_header_t header, Task_trigger *&trigger, Task_act *&act);

	/**
	* Delete task by id. This function can be called only from delete_task and delete_task_waiter functions
	* @param id_ - id of task to delete
	* @param from_waiter - if function was called from delete_task_waiter function
	* @exceptions TaskIdDoesNotExist, ConfigFileCorrupted
	*/
	void delete_task_private(unsigned int id_, bool from_waiter);

	void delete_task_waiter(unsigned int id_);

	/**
	* Safely continue program after exception
	*/
	void safely_continue();

	/**
	* Read from file @n bytes and check on errors
	* @param s - pointer to char buffer
	* @param n - number of bytes to read
	* @exceptions EndOfFileWasReached
	*/
	void read_(char *s, std::streamsize n);
	/**
	* Open file with path m_file_name
	* @param mode_ mode of opening
	* @exceptions ConfigFileAlreadyOpened, CanNotOpenConfigFile
	*/
	void open_(unsigned int mode_);

	/**
	* Check if configuration file is corrupted
	* @return true if file corrupted
	*/
	bool is_corrupted();

	/*
	read_task:
		read_header
		read_trigger
		read_act
	*/
	Task* read_task(unsigned int id);
	Task_header_t read_header(unsigned int id);
	Task_trigger* read_trigger();
	Task_act* read_act();

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
	boost::mutex m_file_mutex;
	std::vector<Task*> m_Tasks;
	boost::mutex m_Tasks_mutex;

	int m_last_id;

	Alert_Manager *m_alert_manager;

	// Waiter:
	bool m_stop_waiting;
	bool m_exit;
	//System::Threading::Thread ^m_waiter_cycle_thread;
	//std::thread *m_waiter_cycle_thread;
	//gcroot<System::Threading::Thread ^> m_waiter_cycle_thread;
	boost::thread *m_waiter_cycle_thread;
};

