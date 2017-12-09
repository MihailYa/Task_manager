#include "Task_act_alert.h"

Task_act_alert::Task_act_alert(std::string alert_name_, std::string alert_text_)
	: Task_act(ALERT), alert_name(alert_name_), alert_text(alert_text_)
{
}

void Task_act_alert::make_act()
{
	printf("Act was maked:\nName:%s\nText:\n%s\n", alert_name.c_str(), alert_text.c_str());
	MessageBoxA(NULL, alert_text.c_str(), alert_name.c_str(), MB_OK | MB_ICONINFORMATION);
	// TO DO
	// Add alert
	//exit(EXIT_FAILURE);
}
