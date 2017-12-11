#include "Task_act_alert.h"
#include "Alert_Manager.h"

Task_act_alert::Task_act_alert(std::string alert_name_, std::string alert_text_)
	: Task_act(ALERT), alert_name(alert_name_), alert_text(alert_text_)
{
}

void Task_act_alert::make_act()
{
#ifdef DEBUG
	printf("Act was maked:\nName:%s\nText:\n%s\n", alert_name.c_str(), alert_text.c_str());
#endif // DEBUG
	Alert_Manager::Get()->add_alert(alert_name, alert_text);
	// TO DO
	// Add alert
	//exit(EXIT_FAILURE);
}
