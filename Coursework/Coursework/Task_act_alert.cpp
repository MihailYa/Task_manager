#include "Task_act_alert.h"

Task_act_alert::Task_act_alert(std::string alert_name_, std::string alert_text_)
	: Task_act(ALERT), alert_name(alert_name_), alert_text(alert_text_)
{
}

void Task_act_alert::make_act()
{
	// TO DO
	// Add alert
	exit(EXIT_FAILURE);
}
