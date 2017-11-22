#include "stdafx.h"
#include "MainForm.h"
#include "CreateTaskForm.h"

namespace TaskManagerForm
{
	void MainForm::refresh()
	{
		std::string tmp;
		std::vector<Task_Info_t> tasks_info = m_TaskManager->Get_task_info();

		while (TaskList->RowCount != 0)
			TaskList->Rows->RemoveAt(0);

		unsigned int n = tasks_info.size();
		for (unsigned int i = 0; i < n; ++i)
		{
			TaskList->Rows->Add();
			TaskList->Rows[i]->Cells[0]->Value = tasks_info[i].header.id;
			TaskList->Rows[i]->Cells[1]->Value = gcnew System::String(tasks_info[i].header.name.c_str());
			TaskList->Rows[i]->Cells[2]->Value = gcnew System::String(tasks_info[i].header.desc.c_str());
			TaskList->Rows[i]->Cells[3]->Value = tasks_info[i].time_left;

			TaskList->Rows[i]->Cells[4]->Value = gcnew System::String("Export");
			TaskList->Rows[i]->Cells[4]->Value = gcnew System::String("Delete");
		}
	}

}
