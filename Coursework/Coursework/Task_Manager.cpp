#include "Task_Manager.h"

Task_Manager::Task_Manager(const char* file_name_)
	: m_refresh_started(false), m_create_task_started(false), m_delete_task_started(false)
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
	}
	m_last_id = n - 1;

	m_file->close();

#ifdef DEBUG
	printf("\n%d tasks was read.\n", n);
#endif // DEBUG

	m_exit = false;
	m_waiter_cycle_thread = new boost::thread(boost::bind(&Task_Manager::waiter_cycle, this));
	//m_waiter_cycle_thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, Task_Manager::waiter_cycle));
	//m_waiter_cycle_thread->Start();
}

Task_Manager::~Task_Manager() throw()
{
	if (m_file == nullptr)
	{
		throw Task_Exception(ConfigFileAlreadyDeleted);
	}
	delete m_file;
	m_file = nullptr;

	m_exit = true;
	for (unsigned int i = 0; i < m_Tasks.size(); i++)
	{
		if (m_Tasks[i] == nullptr)
		{
			throw Task_Exception(TaskAlreadyDeleted);
		}
		delete m_Tasks[i];
	}
	m_waiter_cycle_thread->join();
	if (m_waiter_cycle_thread == nullptr)
	{
		throw Task_Exception(WaiterThreadCycleAlreadyDeleted);
	}
	delete m_waiter_cycle_thread;
	m_waiter_cycle_thread = nullptr;
}

void Task_Manager::create_task(Task_header_t header, Task_trigger *&trigger, Task_act *&act)
{
	bool try_again;
	do
	{
		try_again = false;

		try
		{
			create_task_private(header, trigger, act);
		}
		catch (Task_Exception &e)
		{
			if (m_file->is_open())
				m_file->close();

			if (m_waiter_cycle_thread == nullptr)
			{
				m_exit = false;
				m_waiter_cycle_thread = new boost::thread(boost::bind(&Task_Manager::waiter_cycle, this));
				//m_waiter_cycle_thread = gcnew System::Threading::Thread(this->Task_Manager::waiter_cycle);
				//m_waiter_cycle_thread->Start();
			}
			m_create_task_started = false;

			if (e.Get_error_code() == TryAgain || e.Get_error_code() == WaiterThreadCycleAlreadyDeleted)
				try_again = true;
			else
				throw e;
		}

	} while (try_again);
}

void Task_Manager::delete_task(unsigned int id_)
{
	bool try_again;
	do
	{
		try_again = false;

		try
		{
			delete_task_private(id_, false);
		}
		catch (Task_Exception &e)
		{
			if (m_file->is_open())
				m_file->close();

			if (m_waiter_cycle_thread == nullptr)
			{
				m_exit = false;
				m_waiter_cycle_thread = new boost::thread(boost::bind(&Task_Manager::waiter_cycle, this));
				//m_waiter_cycle_thread = gcnew System::Threading::Thread(this->Task_Manager::waiter_cycle);
				//m_waiter_cycle_thread->Start();
			}

			m_delete_task_started = false;
			if (e.Get_error_code() == TryAgain || e.Get_error_code() == WaiterThreadCycleAlreadyDeleted)
				try_again = true;
			else
				throw e;
		}

	} while (try_again);
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
	// Wait until list was leaved
	while (m_delete_task_started || m_create_task_started || m_refresh_started);

	m_create_task_started = true;

	if (m_delete_task_started || m_refresh_started || !m_create_task_started)
	{
		throw Task_Exception(TryAgain);
	}
#ifdef DEBUG
	printf("\nCreating task...");
#endif // DEBUG

	if (m_waiter_cycle_thread != nullptr)
	{
		m_exit = true;
		//while (!m_waiter_cycle_thread->joinable());
		m_waiter_cycle_thread->join();
		delete m_waiter_cycle_thread;
		m_waiter_cycle_thread = nullptr;
	}
	else
	{
		throw Task_Exception(WaiterThreadCycleAlreadyDeleted);
	}

	if (!trigger->calculate_time_left(Time::current_time()))
	{
		throw Task_Exception(WrongTime);
	}

	header.id = ++m_last_id;
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

	// Add task in list
	Task *tmp = new Task(header, trigger, act);
	m_Tasks.push_back(tmp);

#ifdef DEBUG
	printf("\nTask was create.\n");
#endif // DEBUG

	if (m_waiter_cycle_thread == nullptr)
	{
		m_exit = false;
		m_waiter_cycle_thread = new boost::thread(boost::bind(&Task_Manager::waiter_cycle, this));
		//m_waiter_cycle_thread = gcnew System::Threading::Thread(this->Task_Manager::waiter_cycle);
		//m_waiter_cycle_thread->Start();
	}

	m_create_task_started = false;
}

void Task_Manager::delete_task_private(unsigned int id_, bool from_waiter)
{
	while (m_delete_task_started || m_create_task_started || m_refresh_started && !from_waiter);

	m_delete_task_started = true;

	if (!m_delete_task_started || m_refresh_started && !from_waiter || m_create_task_started)
	{
		throw Task_Exception(TryAgain);
	}

	if (m_waiter_cycle_thread != nullptr)
	{
		if (!from_waiter)
		{
			m_exit = true;
			//while (!m_waiter_cycle_thread->joinable());
			m_waiter_cycle_thread->join();
			delete m_waiter_cycle_thread;
			m_waiter_cycle_thread = nullptr;
		}
	}
	else
	{
		throw Task_Exception(WaiterThreadCycleAlreadyDeleted);
	}

#ifdef DEBUG
	printf("\nDeleting task...");
#endif // DEBUG
	if ((int)id_ > m_last_id)
	{
		throw Task_Exception(TaskIdDoesNotExist);
	}

	unsigned int n; // Number of tasks

	open_(std::ios::in | std::ios::out | std::ios::binary);

	// Change number of tasks
	n = m_last_id;
	m_file->seekp(0, std::ios::beg);
	m_file->write((char*)&n, sizeof(unsigned int));
	m_last_id--;

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

	std::vector<Task*>::iterator elem = find_task_by_id(id_);
	if (*elem != nullptr)
	{
		delete *elem;
		*elem = nullptr;
		m_Tasks.erase(elem);
	}
	else
		throw Task_Exception(TaskIdDoesNotFound);

	for (unsigned int i = 0; i < m_Tasks.size(); ++i)
	{
		if (m_Tasks[i]->Get_id() > id_)
			--*m_Tasks[i];
	}

	if (m_waiter_cycle_thread == nullptr)
	{
		m_exit = false;
		m_waiter_cycle_thread = new boost::thread(boost::bind(&Task_Manager::waiter_cycle, this));
		//m_waiter_cycle_thread = gcnew System::Threading::Thread(this->Task_Manager::waiter_cycle);
		//m_waiter_cycle_thread->Start();
	}

	m_delete_task_started = false;
}

void Task_Manager::delete_task_waiter(unsigned int id_)
{
	bool try_again;
	do
	{
		try_again = false;

		try
		{
			delete_task_private(id_, true);
		}
		catch (Task_Exception &e)
		{
			if (m_file->is_open())
				m_file->close();

			m_delete_task_started = false;
			if (e.Get_error_code() == TryAgain)
				try_again = true;
			else
				throw e;
		}

	} while (try_again);
}


void Task_Manager::read_(char *s, std::streamsize n)
{
	m_file->read(s, n);
	if ((m_file->rdstate() & std::ios::eofbit) != 0)
	{
		throw Task_Exception(EndOfFileWasReached);
	}
}

void Task_Manager::open_(unsigned int mode_)
{
	if (m_file->is_open())
	{
		throw Task_Exception(ConfigFileAlreadyOpened);
	}

	m_file->open(m_file_name, mode_);

	if (!m_file->is_open())
	{
		throw Task_Exception(CanNotOpenConfigFile);
	}
}


bool Task_Manager::is_corrupted()
{
	open_(std::ios::in | std::ios::binary);

	try
	{
		unsigned int n;
		read_((char*)&n, sizeof(unsigned int));
		
		for (unsigned int i = 0; i < n; ++i)
			skeep_task();

		m_file->close();
	}
	catch (Task_Exception &e)
	{
		if (e.Get_error_code() == EndOfFileWasReached)
		{
			m_file->close();
			return true;
		}
	}

	return false;
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
	read_((char*)&n, sizeof(unsigned int));
	tmp_char = new char[n+1];
	read_(tmp_char, sizeof(char)*n);
	tmp_char[n] = '\0';
	header.name = tmp_char;
	delete[] tmp_char;

	read_((char*)&n, sizeof(unsigned int));
	tmp_char = new char[n+1];
	read_(tmp_char, sizeof(char)*n);
	tmp_char[n] = '\0';
	header.desc = tmp_char;
	delete[] tmp_char;

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
		read_((char*)&months, n * sizeof(boost::date_time::months_of_year));
		if (n == 1)
			m_vec.push_back(months[0]);
		else
			m_vec = std::vector<boost::date_time::months_of_year>(months, months + n - 1);
		delete[] months;

		read_((char*)&n, sizeof(unsigned int));
		unsigned int *days = new unsigned int[n];
		read_((char*)&days, n * sizeof(unsigned int));
		if (n == 1)
			d_vec.push_back(days[0]);
		else
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
		throw Task_Exception(WrongTriggerType);
	}

	return trigger;
}

Task_act*& Task_Manager::read_act()
{
	Task_act *act;
	Task_act_type_t type;
	read_((char*)&type, sizeof(Task_act_type_t));
	
	unsigned int n;
	char *buf;
	
	read_((char*)&n, sizeof(unsigned int));
	buf = new char[n+1];
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
	buf = new char[n+1];
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
		act = new Task_act_prog(str1, str2);
		break;
	case ALERT:
		act = new Task_act_alert(str1, str2);
		break;
	default:
		throw Task_Exception(WrongActType);
		break;
	}

	return act;
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
	while (m_create_task_started || m_delete_task_started);
	m_refresh_started = true;
#ifdef DEBUG
	printf("\nRefresh task list...");
#endif // DEBUG
	Time c_time = Time::current_time();
	int n = m_Tasks.size();
	for (int i = 0; i < n; ++i)
	{
		if (!m_Tasks[i]->calculate_time_left(c_time))
		{
			delete_task_waiter(m_Tasks[i]->Get_id());
			--i;
			--n;
		}
	}

	if (n <= 1)
	{
#ifdef DEBUG
		printf("\nTasks list has been refreshed.\n");
#endif // DEBUG
		m_refresh_started = false;
		return;
	}

	std::sort(m_Tasks.begin(), m_Tasks.end(), Task::compare);
#ifdef DEBUG
	printf("\nTasks list has been refreshed.\n");
#endif // DEBUG

	m_refresh_started = false;
}

void Task_Manager::waiter()
{
#ifdef DEBUG
	printf("\nWaiter was started:\n");
#endif // DEBUG
	unsigned int to_wait;
	if (m_Tasks.size() != 0)
	{
		to_wait = m_Tasks[0]->Get_time_left();
	}
	else
		to_wait = INF;

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
	seconds = Time::to_minute_left();
	if (seconds != 0)
	{
		to_wait -= 60;
		to_wait += seconds;
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

	m_Tasks[0]->Set_last_time(Time::current_time());
	m_Tasks[0]->make_act();
}
