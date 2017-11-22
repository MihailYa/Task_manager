#include "stdafx.h"
#include "CreateTaskForm.h"

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


	Task_header_t CreateTaskForm::InputHeader()
	{
		Task_header_t tmp;

		return tmp;
	}

	Task_trigger* CreateTaskForm::InputTrigger()
	{
		Task_trigger *tmp = nullptr;

		return tmp;
	}

	Task_act* CreateTaskForm::InputAct()
	{
		Task_act *tmp = nullptr;

		return tmp;
	}
}