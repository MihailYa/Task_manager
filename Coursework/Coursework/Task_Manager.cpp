#include "Task_Manager.h"

Task_Manager::Task_Manager(const char* file_name_, bool entrance)
{
#ifdef DEBUG
	printf("\nReading tasks...");
#endif // DEBUG

	m_last_id = -1;
	m_file_name = file_name_;
	m_file = new std::fstream;

	unsigned int n = 0; // Number of tasks

	if (is_corrupted())
	{
		// Trunc file
		open_(std::ios::out | std::ios::binary);
		m_file->write((char*)&n, sizeof(unsigned int));
		m_file->close();
	}

	open_(std::ios::in | std::ios::binary);

	m_file->seekg(0, std::ios::beg);

	read_((char*)&n, sizeof(unsigned int));

	// Read tasks
	Task *tmp;

	for (unsigned int i = 0; i < n; i++)
	{
		tmp = read_task(i);
		m_Tasks.push_back(tmp);
		if (!entrance && m_Tasks[i]->Get_trigger_type() == ENTRANCE)
		{
			m_Tasks[i]->Set_was_maked(true);
		}
	}
	m_last_id = n - 1;

	m_file->close();

	m_alert_manager = new Alert_Manager;

#ifdef DEBUG
	printf("\n%d tasks was read.\n", n);
#endif // DEBUG

	m_exit = false;
	m_waiter_cycle_thread = new boost::thread(boost::bind(&Task_Manager::waiter_cycle, this));
}

Task_Manager::~Task_Manager()
{
	m_exit = true;
	if (m_waiter_cycle_thread == nullptr)
		throw WaiterThreadCycleAlreadyDeleted_ex();
	m_waiter_cycle_thread->join();
	delete m_waiter_cycle_thread;
	m_waiter_cycle_thread = nullptr;

	m_file_mutex.lock();
	if (m_file == nullptr)
	{
		throw ConfigFileAlreadyDeleted_ex();
	}
	delete m_file;
	m_file = nullptr;

	m_Tasks_mutex.lock();
	for (unsigned int i = 0; i < m_Tasks.size(); i++)
	{
		if (m_Tasks[i] == nullptr)
		{
			throw TaskAlreadyDeleted_ex();
		}
		delete m_Tasks[i];
	}

	if (m_alert_manager != nullptr)
	{
		delete m_alert_manager;
		m_alert_manager = nullptr;
	}
}

void Task_Manager::create_task(Task_header_t header, Task_trigger *&trigger, Task_act *&act)
{
	try
	{
		create_task_private(header, trigger, act);
	}
	catch (Task_Exception &e)
	{
		throw e;
	}
}

void Task_Manager::delete_task(unsigned int id_)
{
	try
	{
		delete_task_private(id_);
	}
	catch (EndOfFileWasReached_ex &e)
	{
		if (is_corrupted())
			throw ConfigFileCorrupted_ex();
	}
	catch (TaskIdDoesNotFound_ex &e)
	{
	}
	catch (Task_Exception &e)
	{

		throw e;
	}
}

void Task_Manager::import_task(const char *import_file_name_)
{
#ifdef DEBUG
	printf("\nImporting task...");
#endif // DEBUG

	m_file_mutex.lock();
	try
	{
		if (m_file->is_open())
			throw ConfigFileAlreadyOpened_ex();
		m_file->open(import_file_name_, std::ios::in | std::ios::binary);
		if (!m_file->is_open())
			throw CanNotOpenFile_ex();

		skeep_task();

		// Save file in memory
		std::streampos file_size = m_file->tellg();
		m_file->seekg(0, std::ios::beg);
		char *file = new char[file_size];
		read_(file, file_size);

		m_file->seekg(0, std::ios::beg);
		m_last_id_mutex.lock();
		
		Task *tmp = nullptr;
		try
		{
			tmp = read_task(++m_last_id);
		}
		catch (Task_Exception &e)
		{
			m_last_id_mutex.unlock();
			throw e;
		}
		m_last_id_mutex.unlock();
		m_file->close();

		m_Tasks_mutex.lock();
		m_stop_waiting = true;
		m_Tasks.push_back(tmp);
		m_Tasks_mutex.unlock();

		// Write task in config file
		open_(std::ios::in | std::ios::out | std::ios::binary);
		// Write number of tasks
		m_file->seekp(0, std::ios::beg);
		m_last_id_mutex.lock();
		unsigned int n = m_last_id + 1;
		m_last_id_mutex.unlock();

		m_file->write((char*)&n, sizeof(unsigned int));

		m_file->seekp(0, std::ios::end);
		m_file->write(file, file_size);

		m_file->close();
	}
	catch (EndOfFileWasReached_ex &e)
	{
		if (m_file->is_open())
			m_file->close();
		m_file_mutex.unlock();
		throw FileCorrupted_ex();
	}
	catch (Task_Exception &e)
	{
		if (m_file->is_open())
			m_file->close();
		m_file_mutex.unlock();
		throw e;
	}
	m_file_mutex.unlock();

#ifdef DEBUG
	printf("\nTask was imported.\n");
#endif // DEBUG
}

void Task_Manager::export_task(const char *export_file_name_, unsigned int id_)
{
#ifdef DEBUG
	printf("\nExporting task...");
#endif // DEBUG
	char *file = nullptr;

	m_last_id_mutex.lock();
	if ((int)id_ > m_last_id)
	{
		m_last_id_mutex.unlock();
		throw TaskIdDoesNotExist_ex();
	}
	m_last_id_mutex.unlock();

	m_file_mutex.lock();
	try
	{
		open_(std::ios::in | std::ios::binary);
		m_file->seekg(sizeof(unsigned int));

		for (unsigned int i = 0; i < id_; ++i)
			skeep_task();

		std::streampos task_begin = m_file->tellg();
		skeep_task();
		std::streampos task_end = m_file->tellg();
		unsigned int file_size = task_end - task_begin;
		file = new char[file_size];

		m_file->seekg(task_begin);
		read_(file, file_size);
		m_file->close();

		m_file->open(export_file_name_, std::ios::out | std::ios::binary);
		if (!m_file->is_open())
		{
			throw CanNotOpenFile_ex();
		}

		m_file->write(file, file_size);
		m_file->close();
	}
	catch (EndOfFileWasReached_ex &e)
	{
		if (m_file->is_open())
			m_file->close();

		m_file_mutex.unlock();
		if (is_corrupted())
			throw ConfigFileCorrupted_ex();
	}
	catch (Task_Exception &e)
	{
		if (m_file->is_open())
			m_file->close();

		m_file_mutex.unlock();
		throw e;
	}
	m_file_mutex.unlock();



#ifdef DEBUG
	printf("\nTask was exported.\n");
#endif // DEBUG
}

std::vector<Task_Info_t> Task_Manager::Get_task_info()
{
	std::vector<Task_Info_t> tasks_info;
	Task_Info_t tmp;

	m_stop_waiting = true;
	while (!m_stop_waiting);

	m_Tasks_mutex.lock();
	unsigned int n = m_Tasks.size();
	for (unsigned int i = 0; i < n; ++i)
	{
		tmp.header = m_Tasks[i]->Get_header();
		tmp.time_left = m_Tasks[i]->Get_time_left();
		tasks_info.push_back(tmp);
	}
	m_Tasks_mutex.unlock();

	return tasks_info;
}


#ifdef DEBUG
void Task_Manager::output()
{

	for (unsigned int i = 0; i < m_Tasks.size(); i++)
	{
		printf("\n==========\nTask #%d", i);
		m_Tasks[i]->output();
	}
}
#endif //DEBUG



//
// private:
//
void Task_Manager::create_task_private(Task_header_t header, Task_trigger *&trigger, Task_act *&act)
{
#ifdef DEBUG
	printf("\nCreating task...");
#endif // DEBUG
	if (!trigger->calculate_time_left(Time::current_time()))
	{
		throw WrongTime_ex();
	}

	m_last_id_mutex.lock();
	header.id = ++m_last_id;
	m_last_id_mutex.unlock();

	m_file_mutex.lock();
	try
	{
		open_(std::ios::in | std::ios::out | std::ios::binary);

		// Write number of tasks
		m_file->seekp(0, std::ios::beg);
		unsigned int n = m_last_id + 1;
		m_file->write((char*)&n, sizeof(unsigned int));

		// Write in end of file
		m_file->seekp(0, std::ios::end);
		write_header(header);
		write_trigger(trigger);
		write_act(act);

		m_file->close();
	}
	catch (Task_Exception &e)
	{
		if (m_file->is_open())
			m_file->close();
		m_file_mutex.unlock();
		throw e;
	}
	m_file_mutex.unlock();

	// Add task in list
	Task *tmp = new Task(header, trigger, act);
	if (tmp->Get_trigger_type() == ENTRANCE)
		tmp->Set_was_maked(true);
	m_Tasks_mutex.lock();
	m_stop_waiting = true;
	m_Tasks.push_back(tmp);
	m_Tasks_mutex.unlock();

#ifdef DEBUG
	printf("\nTask was create.\n");
#endif // DEBUG
}

void Task_Manager::delete_task_private(unsigned int id_)
{
#ifdef DEBUG
	printf("\nDeleting task...");
#endif // DEBUG
	m_last_id_mutex.lock();
	unsigned int n = m_last_id; // Number of tasks
	m_last_id_mutex.unlock();

	if (id_ > n)
		throw TaskIdDoesNotExist_ex();


	m_file_mutex.lock();
	try
	{
		open_(std::ios::in | std::ios::out | std::ios::binary);

		// Change number of tasks
		m_file->seekp(0, std::ios::beg);
		m_file->write((char*)&n, sizeof(unsigned int));

		// Skeep tasks before id_ task
		m_file->seekg(sizeof(unsigned int), std::ios::beg);
		for (unsigned int i = 0; i < id_; i++)
			skeep_task();

		std::streamoff begin_of_task = m_file->tellg();
		skeep_task();
		std::streamoff end_of_task = m_file->tellg();

		m_file->seekg(0, std::ios::end);
		std::streamoff file_size = m_file->tellg();

		std::streamoff rest_file_size = file_size - end_of_task;
		m_file->seekg(end_of_task);

		char *rest_file = new char[rest_file_size];
		read_(rest_file, rest_file_size);

		m_file->seekp(begin_of_task, std::ios::beg);
		m_file->write(rest_file, rest_file_size);
		delete[] rest_file;

		m_file->seekg(0, std::ios::beg);
		file_size -= end_of_task - begin_of_task;
		char *all_file = new char[file_size];
		read_(all_file, file_size);

		m_file->close();

		// Trunc file
		open_(std::ios::out | std::ios::binary);

		m_file->seekp(0, std::ios::beg);
		m_file->write(all_file, file_size);
		delete[] all_file;

		m_file->close();
	}
	catch (Task_Exception &e)
	{
		if (m_file->is_open())
			m_file->close();
		m_file_mutex.unlock();
		throw e;
	}
	m_file_mutex.unlock();

	m_Tasks_mutex.lock();
	m_stop_waiting = true;
	try
	{
		m_stop_waiting = true;

		m_last_id_mutex.lock();
		m_last_id--;
		m_last_id_mutex.unlock();

		std::vector<Task*>::iterator elem = find_task_by_id(id_);
		if (*elem != nullptr)
		{
			delete *elem;
			*elem = nullptr;
			m_Tasks.erase(elem);
		}
		else
			throw TaskIdDoesNotFound_ex();

		for (unsigned int i = 0; i < m_Tasks.size(); ++i)
		{
			if (m_Tasks[i]->Get_id() > id_)
				--*m_Tasks[i];
		}
	}
	catch (Task_Exception &e)
	{
		m_Tasks_mutex.unlock();
		throw e;
	}
	m_Tasks_mutex.unlock();

#ifdef DEBUG
	printf("\nTask was deleted.\n");
#endif // DEBUG
}

//void Task_Manager::delete_task_waiter(unsigned int id_)
//{
//	bool try_again;
//	bool second_try = false;
//	do
//	{
//		try_again = false;
//
//		try
//		{
//			delete_task_private(id_);
//		}
//		catch (ConfigFileAlreadyOpened_ex *&e)
//		{
//			try_again = true;
//
//			delete e;
//		}
//		catch (CanNotOpenConfigFile_ex *&e)
//		{
//			if (m_file->is_open())
//				m_file->close();
//			delete e;
//
//			if (second_try)
//				throw new ConfigFileNotFound_ex;
//
//			second_try = true;
//			try_again = true;
//		}
//		catch (TaskIdDoesNotFound_ex *&e)
//		{
//			if (m_file->is_open())
//				m_file->close();
//
//			delete e;
//		}
//		catch (EndOfFileWasReached_ex *&e)
//		{
//			if (m_file->is_open())
//				m_file->close();
//			delete e;
//
//			if (is_corrupted())
//				throw new ConfigFileCorrupted_ex;
//		}
//		catch (Task_Exception *&e)
//		{
//			if (m_file->is_open())
//				m_file->close();
//
//			throw e;
//		}
//
//	} while (try_again);
//}


//void Task_Manager::safely_continue()
//{
//	if (m_file->is_open())
//		m_file->close();
//
//	if (m_waiter_cycle_thread == nullptr)
//	{
//		m_exit = false;
//		m_waiter_cycle_thread = new boost::thread(boost::bind(&Task_Manager::waiter_cycle, this));
//	}
//}


void Task_Manager::read_(char *s, std::streamsize n)
{
	m_file->read(s, n);
	if ((m_file->rdstate() & std::ios::eofbit) != 0)
	{
		throw EndOfFileWasReached_ex();
	}
}

void Task_Manager::open_(unsigned int mode_)
{
	if (m_file->is_open())
	{
		throw ConfigFileAlreadyOpened_ex();
	}

	m_file->open(m_file_name, mode_);

	if (!m_file->is_open())
	{
		throw CanNotOpenConfigFile_ex();
	}
}


bool Task_Manager::is_corrupted()
{
	m_file_mutex.lock();
	try
	{
		open_(std::ios::in | std::ios::binary);
		unsigned int n;
		read_((char*)&n, sizeof(unsigned int));

		for (unsigned int i = 0; i < n; ++i)
			skeep_task();

		m_file->close();
	}
	catch (Task_Exception &e)
	{
		Task_Exception_error_code_t e_code = e.Get_error_code();
		m_file_mutex.unlock();
		if (m_file->is_open())
			m_file->close();

		if (e_code == EndOfFileWasReached || e_code == CanNotOpenConfigFile)
			return true;

		throw e;
	}

	m_file_mutex.unlock();

	return false;
}


Task* Task_Manager::read_task(unsigned int id)
{
	Task_header_t header;
	header = read_header(id);

	Task_trigger *trigger = nullptr;
	trigger = read_trigger();

	Task_act *act = nullptr;
	act = read_act();

	return new Task(header, trigger, act);
}

Task_header_t Task_Manager::read_header(unsigned int id)
{
	// Fill task header
	Task_header_t header;
	header.id = id;

	unsigned int n;
	char *tmp_char;
	read_((char*)&n, sizeof(unsigned int));
	tmp_char = new char[n + 1];
	read_(tmp_char, sizeof(char)*n);
	tmp_char[n] = '\0';
	header.name = tmp_char;
	delete[] tmp_char;

	read_((char*)&n, sizeof(unsigned int));
	tmp_char = new char[n + 1];
	read_(tmp_char, sizeof(char)*n);
	tmp_char[n] = '\0';
	header.desc = tmp_char;
	delete[] tmp_char;

	return header;
}

Task_trigger* Task_Manager::read_trigger()
{
	// Fill trigger
	Trigger_type_t trigger_type;
	Time time;
	unsigned int priority;

	// For weekly trigger:
	boost::date_time::weekdays wday;
	unsigned int every_n_week;

	// For monthly trigger:
	std::vector<boost::date_time::months_of_year> m_vec;
	std::vector<unsigned int> d_vec;

	read_((char*)&trigger_type, sizeof(Trigger_type_t));
	read_((char*)&time, sizeof(Time));
	read_((char*)&priority, sizeof(unsigned int));

	if (trigger_type == WEEKLY)
	{
		read_((char*)&wday, sizeof(boost::date_time::weekdays));

		read_((char*)&every_n_week, sizeof(unsigned int));
	}
	else if (trigger_type == MONTHLY)
	{
		unsigned int n;
		read_((char*)&n, sizeof(unsigned int));
		boost::date_time::months_of_year *months = new boost::date_time::months_of_year[n];
		read_((char*)months, n * sizeof(boost::date_time::months_of_year));
		if (n == 1)
			m_vec.push_back(months[0]);
		else
			m_vec = std::vector<boost::date_time::months_of_year>(months, months + n);
		delete[] months;

		read_((char*)&n, sizeof(unsigned int));
		unsigned int *days = new unsigned int[n];
		read_((char*)days, n * sizeof(unsigned int));
		if (n == 1)
			d_vec.push_back(days[0]);
		else
			d_vec = std::vector<unsigned int>(days, days + n);
		delete[] days;
	}

	switch (trigger_type)
	{
	case DAYLY:
		return new Task_trigger_dayly(time, priority);
		break;
	case WEEKLY:
		return new Task_trigger_weekly(time, priority, wday, every_n_week);
		break;
	case MONTHLY:
		return new Task_trigger_monthly(time, priority, m_vec, d_vec);
		break;
	case ONCE:
		return new Task_trigger_once(time, priority);
		break;
	case ENTRANCE:
		return new Task_trigger_entrance(time, priority);
		break;
	default:
		throw WrongTriggerType_ex();
	}

	return nullptr;
}

Task_act* Task_Manager::read_act()
{
	Task_act_type_t type;
	read_((char*)&type, sizeof(Task_act_type_t));

	unsigned int n;
	char *buf;

	read_((char*)&n, sizeof(unsigned int));
	buf = new char[n + 1];
	read_(buf, sizeof(char)*n);
	buf[n] = '\0';
	/*
	str1:
	name of prog for Tasc_act_prog
	header of alert for Task_act_alert
	*/
	std::string str1 = buf;
	delete[] buf;

	read_((char*)&n, sizeof(unsigned int));
	buf = new char[n + 1];
	read_(buf, sizeof(char)*n);
	buf[n] = '\0';
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
		return new Task_act_prog(str1, str2);
		break;
	case ALERT:
		return new Task_act_alert(str1, str2);
		break;
	default:
		throw WrongActType_ex();
		break;
	}

	return nullptr;
}


void Task_Manager::write_header(Task_header_t header)
{
	unsigned int n;
	const char* tmp;

	n = header.name.size();
	m_file->write((char*)&n, sizeof(unsigned int));
	tmp = header.name.c_str();
	m_file->write((char*)tmp, sizeof(char)*n);

	n = header.desc.size();
	m_file->write((char*)&n, sizeof(unsigned int));
	tmp = header.desc.c_str();
	m_file->write((char*)tmp, sizeof(char)*n);
}

void Task_Manager::write_trigger(Task_trigger *&trigger)
{
	Trigger_type_t type = trigger->Get_type();
	m_file->write((char*)&type, sizeof(Trigger_type_t));

	Time time = trigger->Get_time();
	m_file->write((char*)&time, sizeof(Time));

	unsigned int priority = trigger->Get_priority();
	m_file->write((char*)&priority, sizeof(unsigned int));


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
	m_file->write(tmp, sizeof(char)*n);

	n = text.size();
	m_file->write((char*)&n, sizeof(unsigned int));
	tmp = text.c_str();
	m_file->write(tmp, sizeof(char)*n);
}


std::vector<Task*>::iterator Task_Manager::find_task_by_id(unsigned int id)
{
	std::vector<Task*>::iterator curr, end;
	curr = m_Tasks.begin();
	end = m_Tasks.end();

	while (curr != end)
	{
		if ((*curr)->Get_id() == id)
			return curr;
		++curr;
	}

	return end;
}


void Task_Manager::skeep_task()
{
	Trigger_type_t trig_type;
	Task_act_type_t act_type;
	unsigned int n;

	// Skip header
	read_((char*)&n, sizeof(unsigned int));
	m_file->seekg(sizeof(char)*n, std::ios::cur);
	read_((char*)&n, sizeof(unsigned int));
	m_file->seekg(sizeof(char)*n, std::ios::cur);

	// Skip trigger
	read_((char*)&trig_type, sizeof(Trigger_type_t));
	m_file->seekg(sizeof(Time) + sizeof(unsigned int), std::ios::cur);
	switch (trig_type)
	{
	case WEEKLY:
		m_file->seekg(sizeof(boost::date_time::weekdays) + sizeof(unsigned int), std::ios::cur);
		break;
	case MONTHLY:
		read_((char*)&n, sizeof(unsigned int));
		m_file->seekg(sizeof(boost::date_time::months_of_year)*n, std::ios::cur);
		read_((char*)&n, sizeof(unsigned int));
		m_file->seekg(sizeof(unsigned int)*n, std::ios::cur);
		break;
	}

	// Skip act
	read_((char*)&act_type, sizeof(Task_act_type_t));
	read_((char*)&n, sizeof(unsigned int));
	m_file->seekg(sizeof(char)*n, std::ios::cur);
	read_((char*)&n, sizeof(unsigned int));
	m_file->seekg(sizeof(char)*n, std::ios::cur);
}


void Task_Manager::waiter_cycle()
{
#ifdef DEBUG
	printf("\nWaiter cycle was started.\n");
#endif // DEBUG
	while (!m_exit)
	{
		refresh();
		m_stop_waiting = false;
		waiter();
	}
#ifdef DEBUG
	printf("\nExit from waiter cycle.\n");
#endif // DEBUG
}


void Task_Manager::refresh()
{
#ifdef DEBUG
	printf("\nRefresh task list...");
#endif // DEBUG
	Time c_time = Time::current_time();

	m_Tasks_mutex.lock();
	int n = m_Tasks.size();
	for (int i = 0; i < n; ++i)
	{
		if (!m_Tasks[i]->calculate_time_left(c_time))
		{
			unsigned int c_task_id = m_Tasks[i]->Get_id();
			m_Tasks_mutex.unlock();
			delete_task(c_task_id);
			m_Tasks_mutex.lock();
			--i;
			--n;
		}
	}
	m_Tasks_mutex.unlock();

	if (n <= 1)
	{
#ifdef DEBUG
		printf("\nTasks list has been refreshed.\n");
#endif // DEBUG
		return;
	}

	m_Tasks_mutex.lock();
	std::sort(m_Tasks.begin(), m_Tasks.end(), Task::compare);
	m_Tasks_mutex.unlock();
#ifdef DEBUG
	printf("\nTasks list has been refreshed.\n");
#endif // DEBUG
}

void Task_Manager::waiter()
{
#ifdef DEBUG
	printf("\nWaiter was started:\n");
#endif // DEBUG
	unsigned int to_wait;
	m_Tasks_mutex.lock();
	if (m_Tasks.size() != 0)
		to_wait = m_Tasks[0]->Get_time_left();
	else
		to_wait = INF;
	m_Tasks_mutex.unlock();

	unsigned int seconds;

	if (to_wait == INF)
	{
#ifdef DEBUG
		printf("To wait: INF");
#endif // DEBUG
		seconds = Time::to_hour_left();
		for (unsigned int i = 0; i < seconds; ++i)
		{
			if (m_stop_waiting || m_exit)
				return;
			Sleep(1000);
		}
		return;
	}

	to_wait *= 60;
	if (to_wait)
	{
		seconds = Time::to_minute_left();
		if (seconds != 0)
		{
			to_wait -= 60;
			to_wait += seconds;
		}
	}
#ifdef DEBUG
	printf("To wait: %d seconds.\n", to_wait);
#endif // DEBUG
	for (unsigned int i = 0; i < to_wait; i++)
	{
		if (m_stop_waiting || m_exit)
			return;
		Sleep(1000);
	}

	m_Tasks_mutex.lock();
	if (m_stop_waiting)
	{
		m_Tasks_mutex.unlock();
		return;
	}
	m_Tasks[0]->Set_last_time(Time::current_time());
	m_Tasks[0]->make_act();
	m_Tasks_mutex.unlock();
}
