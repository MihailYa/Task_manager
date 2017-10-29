#include <conio.h>
#include "Task_Manager.h"

int main()
{
	//Task_Manager m;

	//getch();
	//m.stop();
	Task_trigger *t;
	Time time(Time_t(boost::gregorian::date(2017, 10, 30), 19, 30));

	std::vector<unsigned int> m_list, d_list;
	m_list.push_back(9);
	m_list.push_back(10);
	d_list.push_back(29);
	time.Set_next_month_day(m_list, d_list);
	time.output();

	t = new Task_trigger_monthly(MONTHLY, time, 1, m_list, d_list);
	
	Time c_time(Time_t(boost::gregorian::date(2017, 10, 29), 19, 16));
	t->calculate_time_left(c_time);

	printf("%d", t->Get_time_left());

	delete t;

	getch();
	return 0;
}

/*
	TO DO:
	Check all task triggers
	+dayly
	+weekly
	-monthly
		Time.cpp > 63 line

	Replace weekday by enum
	Replace monthday by enum
*/