#include <conio.h>
#include "Task_Manager.h"

int main()
{
	boost::date_time::months_of_year m;
	m = static_cast<boost::date_time::months_of_year>(1);
	/*std::ofstream file("test.txt", std::fstream::binary);
	Time t(2017, 6, 11, 18, 18);
	file.write((char*)&t, sizeof(Time));

	std::ifstream file("test.txt", std::fstream::binary);
	Time t;
	file.read((char*)&t, sizeof(Time));
	t.output();
	*/

	//Task_Manager m;
	
	//getch();
	//m.stop();
	/*Task_trigger *t;
	Time time(Time_t(boost::gregorian::date(2017, 10, 30), 19, 30));

	t = new Task_trigger_once(time, 1);
	
	Time c_time(Time_t(boost::gregorian::date(2017, 10, 30), 19, 16));
	t->calculate_time_left(c_time);

	printf("%d", t->Get_time_left());

	delete t;*/

	getch();
	return 0;
}

/*
	TO DO:
	Check all task triggers
	+dayly
	+weekly
	+monthly
	+once
	+entrance
	
	
	*add check on empty file, or file does not exist
	*Task_manager.cpp -> read_task func
	*Think about how to delete once Tasks
	*Check error in Task_manager.cpp (Reading month_list)
*/