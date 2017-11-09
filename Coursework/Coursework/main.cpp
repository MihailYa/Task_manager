#include "Task_Manager.h"

int main()
{
	//printf("%d", sizeof(unsigned int));
	//getch();
	std::ofstream *f = new std::ofstream("tasks.txt", std::ofstream::binary | std::ios::trunc);
	unsigned int n = 0;
	f->write((char*)&n, sizeof(unsigned int));
	f->close();
	delete f;

	/*f->seekp(0, std::ios::beg);
	n = 3;
	f->write((char*)&n, sizeof(unsigned int));

	f->seekp(0, std::ios::end);
	n = 4;
	f->write((char*)&n, sizeof(unsigned int));

	f->close();
	delete f;

	std::ifstream *inp = new std::ifstream("inp.txt", std::ofstream::binary);

	inp->read((char*)&n, sizeof(unsigned int));
	printf("%d", n);
	inp->read((char*)&n, sizeof(unsigned int));
	printf("%d", n);
	getch();*/


	
	Task_Manager m("tasks.txt");

	//m.delete_task(1);
	/*Task_header_t header;
	header.name = "Task number one";
	header.desc = "And some desc fo this(1 task";
	Task_trigger *trig = new Task_trigger_dayly(Time(2017, 11, 8, 17, 59), 1);
	Task_act *act = new Task_act_alert("task1 alert", "Test of alert(task number 1).");
	m.create_task(header, trig, act);

	Task_header_t header2;
	header2.name = "Task number two";
	header2.desc = "Desc for number two";
	Task_trigger *trig2 = new Task_trigger_dayly(Time(2017, 11, 8, 14, 0), 1);
	Task_act *act2 = new Task_act_alert("task2 alert", "Important 2 task");
	m.create_task(header2, trig2, act2);*/


	Task_header_t header3;
	header3.name = "Task number tree";
	header3.desc = "And some desc fo this(3 task";
	Task_trigger *trig3 = new Task_trigger_weekly(Time(2017, 11, 2, 20, 44), 1, boost::date_time::Thursday, 1);
	Task_act *act3 = new Task_act_alert("Name of alert task3", "Test of alert(task number 3).");
	m.create_task(header3, trig3, act3);

	//m.refresh();

	m.output();

	/*boost::date_time::months_of_year m;
	m = static_cast<boost::date_time::months_of_year>(1);*/
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
	
	*check on delete task which does not exist (id_ > m_last_id)
	*add check on empty file, or file does not exist
	*Think about how to delete once Tasks
	*Think about "kostil" Set_last_time
	*Check error in Task_manager.cpp (Reading month_list)
	*Don't create new fstream each time (use one instead)



	*ctrl+h exit(EXIT_FAILURE) -> exceptions
*/