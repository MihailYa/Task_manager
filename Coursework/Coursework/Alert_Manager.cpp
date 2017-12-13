#include "Alert_Manager.h"
#include "Task_Exception.h"

Alert_Manager *Alert_Manager::m_this = nullptr;

Alert_Manager::Alert_Manager()
	:m_show_cycle_thread(nullptr), m_show_cycle_thread_exit(true)
{
	if (m_this != nullptr)
		throw new AlertManagerAlreadyCreated_ex;
	m_this = this;
}

Alert_Manager::~Alert_Manager()
{
	if (m_show_cycle_thread != nullptr)
	{
		m_show_cycle_thread_exit = true;
		m_show_cycle_thread->join();
		delete m_show_cycle_thread;
		m_show_cycle_thread = nullptr;
	}
	m_this = nullptr;
}

void Alert_Manager::add_alert(std::string header, std::string message)
{
	m_alerts_mutex.lock();
	m_alerts.push_back(alert_t(header, message));
	m_alerts_mutex.unlock();
}

Alert_Manager* Alert_Manager::Get()
{
	if (m_this == nullptr)
		throw new AlertManagerDoesNotExist_ex;

	return m_this;
}

void Alert_Manager::show_cycle()
{
	alert_t c_alert;

	m_alerts_mutex.lock();
	while (m_alerts.size() && !m_show_cycle_thread_exit)
	{
		c_alert = m_alerts[0];
		m_alerts_mutex.unlock();

		MessageBoxA(NULL, c_alert.message.c_str(), c_alert.header.c_str(), MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL | MB_SETFOREGROUND);

		m_alerts_mutex.lock();
		m_alerts.erase(m_alerts.begin());
	}
	m_alerts_mutex.unlock();
}