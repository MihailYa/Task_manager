#include "stdafx.h"
#include "CreateTaskForm.h"
#include "MainForm.h"

namespace TaskManagerForm
{
	void CreateTaskForm::ShowStep()
	{
		this->StepOneBox->Visible = false;
		this->StepTwoBox->Visible = false;
		this->StepThreeBox->Visible = false;

		switch (m_step)
		{
		case 0:
			this->StepOneBox->Visible = true;
			break;
		case 1:
			this->StepTwoBox->Visible = true;
			break;
		case 2:
			this->StepThreeBox->Visible = true;
			break;
		default:
			this->StepOneBox->Visible = true;
			m_step = 0;
			break;
		}
	}

	System::Void CreateTaskForm::SendBtn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Task_header_t header;
		Task_trigger *trigger = nullptr;
		Task_act *act = nullptr;
		try
		{
			header = InputHeader();
			trigger = InputTrigger();
			act = InputAct();
		}
		catch (Task_Exception &e)
		{
			MessageBox::Show(gcnew String(e.Get_as_string_with_solution().c_str()), L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		catch (Form_Exception &e)
		{
			MessageBox::Show(gcnew String(e.Get_as_string_with_solution().c_str()), L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		TaskManagerForm::MainForm::Get()->Get_TaskManager()->create_task(header, trigger, act);
		MainForm::Get()->refresh();
		MessageBox::Show(L"Task was successfully created!", L"Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
		this->~CreateTaskForm();
	}

	Task_header_t CreateTaskForm::InputHeader()
	{
		Task_header_t tmp;
		tmp.name = msclr::interop::marshal_as<std::string>(this->TaskName->Text);
		if (tmp.name == "")
			throw TaskManagerForm::TaskHeaderNotFound_ex();
		tmp.desc = msclr::interop::marshal_as<std::string>(this->TaskDesc->Text);
		if (tmp.desc == "")
			throw TaskManagerForm::TaskDescNotFound_ex();
		return tmp;
	}

	Task_trigger* CreateTaskForm::InputTrigger()
	{
		Task_trigger *tmp = nullptr;
		std::string tmp_str;
		unsigned int priority = atoi(msclr::interop::marshal_as<std::string>(this->TrigPrior->Text).c_str());
		Trigger_type_t type = static_cast<Trigger_type_t>(this->TrigType->SelectedIndex);
		
		Time time;
		try
		{
			tmp_str = msclr::interop::marshal_as<std::string>(this->TrigTime->Text);
			time = Time(atoi(tmp_str.substr(4, 4).c_str()),
				atoi(tmp_str.substr(2, 2).c_str()),
				atoi(tmp_str.substr(0, 2).c_str()),
				atoi(tmp_str.substr(8, 2).c_str()),
				atoi(tmp_str.substr(10, 2).c_str()));
		}
		catch (WrongTimeFormat_ex &e)
		{
			throw TrigTimeWrongFormat_ex();
		}

		unsigned int n;
		std::vector<boost::date_time::months_of_year> months;
		std::vector<unsigned int> days;
		if (type == WEEKLY)
		{
			n = atoi(msclr::interop::marshal_as<std::string>(this->WeeklyEveryNWeek->Text).c_str());
			if (n <= 0)
				throw WrongWeeklyTriggerEveryNWeek_ex();
		}
		else if (type == MONTHLY)
		{
			IEnumerator^ DaysEnum = this->MonthlyDays->CheckedIndices->GetEnumerator();
			while (DaysEnum->MoveNext())
			{
				days.push_back(atoi(msclr::interop::marshal_as<std::string>(DaysEnum->Current->ToString()).c_str()) + 1);
			}
			if (days.size() == 0)
				throw WrongMonthlyTriggerDaysVecSize_ex();

			IEnumerator^ MonthsEnum = this->MonthlyMonths->CheckedIndices->GetEnumerator();
			while (MonthsEnum->MoveNext())
			{
				months.push_back(static_cast<boost::date_time::months_of_year>(atoi(msclr::interop::marshal_as<std::string>(MonthsEnum->Current->ToString()).c_str()) + 1));
			}
			if (months.size() == 0)
				throw WrongMonthlyTriggerMonthsVecSize_ex();
		}

		switch (type)
		{
		case DAYLY:
			tmp = new Task_trigger_dayly(time, priority);
			break;
		case WEEKLY:
			tmp = new Task_trigger_weekly(time, priority, m_wday, n);
			break;
		case MONTHLY:
			tmp = new Task_trigger_monthly(time, priority, months, days);
			break;
		case ONCE:
			tmp = new Task_trigger_once(time, priority);
			break;
		case ENTRANCE:
			tmp = new Task_trigger_entrance(time, priority);
			break;
		default:
			throw WrongTriggerType_ex();
			break;
		}
		return tmp;
	}

	Task_act* CreateTaskForm::InputAct()
	{
		Task_act *tmp = nullptr;
		Task_act_type_t type = static_cast<Task_act_type_t>(this->ActType->SelectedIndex);

		std::string name, text;
		switch (type)
		{
		case PROG:
			name = msclr::interop::marshal_as<std::string>(this->ProgramName->Text);
			if (name == "")
				throw TaskManagerForm::ProgActNameNotFound_ex();

			text = msclr::interop::marshal_as<std::string>(this->ProgramParams->Text);
			
			tmp = new Task_act_prog(name, text);
			break;
		case ALERT:
			name = msclr::interop::marshal_as<std::string>(this->MessageName->Text);
			
			if (name == "")
				throw TaskManagerForm::MessageActHeaderNotFound_ex();

			text = msclr::interop::marshal_as<std::string>(this->MessageText->Text);

			if (text == "")
				throw TaskManagerForm::MessageActTextNotFound_ex();

			tmp = new Task_act_alert(name, text);
			break;
		default:
			throw WrongActType_ex();
			break;
		}

		return tmp;
	}
}