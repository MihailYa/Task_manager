#include "Task_Manager.h"

Task_Manager::Task_Manager(const char* file_name_)
{
	m_last_id = -1;
	m_file_name = file_name_;
	m_file = new std::fstream(m_file_name, std::ifstream::in | std::ifstream::binary);

	unsigned int n; // Number of tasks
	m_file->read((char*)&n, sizeof(unsigned int));

	// Read tasks
	Task *tmp;
	for (int i = 0; i < n; i++)
	{
		tmp = read_task(i);
		m_Tasks.push_back(tmp);
	}
	m_last_id = n - 1;

	m_file->close();
	delete m_file;
	m_file = nullptr;

	//waiter = new std::thread(&Task_Manager::Listener, this);
}

Task_Manager::~Task_Manager()
{
	for (int i = 0; i < m_Tasks.size(); i++)
	{
		if (m_Tasks[i] == nullptr)
			exit(EXIT_FAILURE);
		delete m_Tasks[i];
	}
}

void Task_Manager::create_task(Task_header_t header, Task_trigger *&trigger, Task_act *&act)
{
	header.id = ++m_last_id;

	m_file = new std::fstream(m_file_name, std::ofstream::out | std::fstream::binary);

	// Write number of tasks
	unsigned int n = m_last_id + 1;
	m_file->write((char*)&n, sizeof(unsigned int));

	// Write in end of file
	m_file->seekp(std::ofstream::end);
	write_header(header);
	write_trigger(trigger);
	write_act(act);

	// Add task in list
	Task *tmp = new Task(header, trigger, act);
	m_Tasks.push_back(tmp);

	// Refresh list
	refresh();
}


Task*& Task_Manager::read_task(unsigned int id)
{
	Task *task;

	Task_header_t header;
	header = read_header(id);

	Task_trigger *trigger;
	trigger = read_trigger();

	Task_act *act;
	act = read_act();

	task = new Task(header, trigger, act);

	return task;
}

Task_header_t Task_Manager::read_header(unsigned int id)
{
	// Fill task header
	Task_header_t header;
	header.id = id;

	unsigned int n;
	char *tmp_char;
	m_file->read((char*)&n, sizeof(unsigned int));
	tmp_char = new char[n];
	m_file->read(tmp_char, n);
	header.name = tmp_char;

	m_file->read((char*)&n, sizeof(unsigned int));
	tmp_char = new char[n];
	m_file->read(tmp_char, n);
	header.desc = tmp_char;

	return header;
}

Task_trigger*& Task_Manager::read_trigger()
{
	// Fill trigger
	Task_trigger* trigger;
	Trigger_type_t trigger_type;
	Time time;
	unsigned int priority;

	// For weekly trigger:
	boost::date_time::weekdays wday;
	unsigned int every_n_week;

	// For monthly trigger:
	std::vector<boost::date_time::months_of_year> m_vec;
	std::vector<unsigned int> d_vec;

	m_file->read((char*)&trigger_type, sizeof(Trigger_type_t));
	m_file->read((char*)&time, sizeof(Time));
	m_file->read((char*)&priority, sizeof(unsigned int));

	if (trigger_type == WEEKLY)
	{
		m_file->read((char*)&wday, sizeof(boost::date_time::weekdays));

		m_file->read((char*)&every_n_week, sizeof(unsigned int));
	}
	else if (trigger_type == MONTHLY)
	{
		//
		//	There is may be error with vector, if we pass 1 element
		//
		unsigned int n;
		m_file->read((char*)&n, sizeof(unsigned int));
		boost::date_time::months_of_year *monthes = new boost::date_time::months_of_year[n];
		m_file->read((char*)&monthes, n * sizeof(boost::date_time::months_of_year));
		m_vec = std::vector<boost::date_time::months_of_year>(monthes, monthes + n - 1);
		delete[] monthes;

		m_file->read((char*)&n, sizeof(unsigned int));
		unsigned int *days = new unsigned int[n];
		m_file->read((char*)&days, n * sizeof(unsigned int));
		d_vec = std::vector<unsigned int>(days, days + n - 1);
		delete[] days;
	}

	switch (trigger_type)
	{
	case DAYLY:
		trigger = new Task_trigger_dayly(time, priority);
		break;
	case WEEKLY:
		trigger = new Task_trigger_weekly(time, priority, wday, every_n_week);
		break;
	case MONTHLY:
		trigger = new Task_trigger_monthly(time, priority, m_vec, d_vec);
		break;
	case ONCE:
		trigger = new Task_trigger_once(time, priority);
		break;
	case ENTRANCE:
		trigger = new Task_trigger_entrance(time, priority);
		break;
	default:
		exit(EXIT_FAILURE);
	}

	return trigger;
}

Task_act*& Task_Manager::read_act()
{
	Task_act *act;
	Task_act_type_t type;
	m_file->read((char*)&type, sizeof(Task_act_type_t));
	
	unsigned int n;
	char *buf;
	
	m_file->read((char*)&n, sizeof(unsigned int));
	buf = new char[n];
	m_file->read((char*)&buf, n * sizeof(char));
	/*
	str1:
	name of prog for Tasc_act_prog
	header of alert for Task_act_alert
	*/
	std::string str1 = buf;
	delete[] buf;

	m_file->read((char*)&n, sizeof(unsigned int));
	buf = new char[n];
	m_file->read((char*)&buf, n * sizeof(char));
	/*
	str2:
	params of prog for Tasc_act_prog
	text of alert for Task_act_alert
	*/
	std::string str2 = buf;
	delete[] buf;

	switch (type)
	{
	case PROG:
		act = new Task_act_prog(str1, str2);
		break;
	case ALERT:
		act = new Task_act_alert(str1, str2);
		break;
	default:
		exit(EXIT_FAILURE);
		break;
	}

	return act;
}


void Task_Manager::write_header(Task_header_t header)
{
	m_file->write((char*)&header, sizeof(Task_header_t));
}

void Task_Manager::write_trigger(Task_trigger *&trigger)
{
	Trigger_type_t type = trigger->Get_type();
	m_file->write((char*)&type, sizeof(Trigger_type_t));
	
	m_file->write((char*)&trigger->Get_time(), sizeof(Time));

	if (type == WEEKLY)
	{
		boost::date_time::weekdays wd = ((Task_trigger_weekly*)trigger)->Get_week_day();
		m_file->write((char*)&wd, sizeof(boost::date_time::weekdays));

		unsigned int every_n = ((Task_trigger_weekly*)trigger)->Get_every_n_week();
		m_file->write((char*)&every_n, sizeof(unsigned int));
	}
	else if (type == MONTHLY)
	{
		std::vector<boost::date_time::months_of_year> m_list = ((Task_trigger_monthly*)trigger)->Get_month_list();
		unsigned int n = m_list.size();
		m_file->write((char*)&n, sizeof(unsigned int));
		m_file->write((char*)&m_list[0], sizeof(boost::date_time::months_of_year)*n);

		std::vector<unsigned int> d_list = ((Task_trigger_monthly*)trigger)->Get_days_list();
		n = d_list.size();
		m_file->write((char*)&n, sizeof(unsigned int));
		m_file->write((char*)&d_list[0], sizeof(unsigned int)*n);
	}
}

void Task_Manager::write_act(Task_act *&act)
{
	Task_act_type_t type = act->Get_type();
	m_file->write((char*)&type, sizeof(Task_act_type_t));


	std::string name, text;
	if (type == ALERT)
	{
		name = ((Task_act_alert*)act)->Get_alert_name();
		text = ((Task_act_alert*)act)->Get_alert_text();
	}
	else if (type == PROG)
	{
		name = ((Task_act_prog*)act)->Get_prog_name();
		text = ((Task_act_prog*)act)->Get_prog_params();
	}

	unsigned int n;
	const char *tmp;

	n = name.size();
	m_file->write((char*)&n, sizeof(unsigned int));
	tmp = name.c_str();
	m_file->write((char*)&tmp, sizeof(char)*n);

	n = text.size();
	m_file->write((char*)&n, sizeof(unsigned int));
	tmp = text.c_str();
	m_file->write((char*)&tmp, sizeof(char)*n);
}


void Task_Manager::refresh()
{
	exit(EXIT_FAILURE);
	// Add function
}