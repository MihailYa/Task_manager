#pragma once
#include "stdafx.h"

struct alert_t
{
	alert_t() {}
	alert_t(std::string header_, std::string message_)
		: header(header_), message(message_)
	{}
	std::string header;
	std::string message;
};

class Alert_Manager
{
public:
	Alert_Manager();
	~Alert_Manager();

	void add_alert(std::string header, std::string message);

	static Alert_Manager* Get();

protected:
	void show_cycle();

	static Alert_Manager *m_this;

	boost::thread *m_show_cycle_thread;
	bool m_show_cycle_thread_exit;

	boost::mutex m_alerts_mutex;
	std::vector<alert_t> m_alerts;
};

