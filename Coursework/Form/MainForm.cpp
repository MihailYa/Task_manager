#include "stdafx.h"
#include "MainForm.h"
#include "CreateTaskForm.h"

namespace TaskManagerForm
{
	MainForm::MainForm(bool hide, bool entrance)
		:m_hide(hide), m_exit(false)
	{
		if (m_this != nullptr)
			exit(EXIT_FAILURE);
		m_this = this;

		m_check_show_thread_exit = false;
		m_check_show_thread = gcnew Threading::Thread(gcnew Threading::ThreadStart(this, &MainForm::check_show_cycle));
		m_check_show_thread->Start();

		InitializeComponent();

		try
		{
			m_TaskManager = new Task_Manager(CONFIG_FILE_NAME, entrance);
			refresh();
		}
		catch (Task_Exception &e)
		{
			MessageBox::Show(gcnew String(e.Get_as_string_with_solution().c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	MainForm::~MainForm()
	{
		if (components)
		{
			delete components;
		}

		m_exit = false;

		m_check_show_thread_exit = true;
		m_check_show_thread->Join();

		if (m_TaskManager != nullptr)
			delete m_TaskManager;
	}

	void MainForm::refresh()
	{
		this->Cursor = Cursors::WaitCursor;
		std::string tmp;
		std::vector<Task_Info_t> tasks_info = m_TaskManager->Get_task_info();

		while (TaskList->RowCount != 0)
			TaskList->Rows->RemoveAt(0);

		unsigned int n = tasks_info.size();
		for (unsigned int i = 0; i < n; ++i)
		{
			TaskList->Rows->Add();
			TaskList->Rows[i]->Cells[0]->Value = tasks_info[i].header.id;
			TaskList->Rows[i]->Cells[1]->Value = gcnew System::String(tasks_info[i].time_begin.c_str());
			switch (tasks_info[i].type)
			{
			case DAYLY:
				TaskList->Rows[i]->Cells[2]->Value = gcnew System::String("Dayly");
				break;
			case WEEKLY:
				TaskList->Rows[i]->Cells[2]->Value = gcnew System::String("Weekly");
				break;
			case MONTHLY:
				TaskList->Rows[i]->Cells[2]->Value = gcnew System::String("Monthly");
				break;
			case ONCE:
				TaskList->Rows[i]->Cells[2]->Value = gcnew System::String("Once");
				break;
			case ENTRANCE:
				TaskList->Rows[i]->Cells[2]->Value = gcnew System::String("Entrance");
				break;
			default:
				break;
			}
			TaskList->Rows[i]->Cells[3]->Value = tasks_info[i].priority;

			TaskList->Rows[i]->Cells[4]->Value = gcnew System::String(tasks_info[i].header.name.c_str());
			TaskList->Rows[i]->Cells[5]->Value = gcnew System::String(tasks_info[i].header.desc.c_str());
			if (tasks_info[i].time_left >= 60)
				TaskList->Rows[i]->Cells[6]->Value = gcnew System::String("More then hour...");
			else
				TaskList->Rows[i]->Cells[6]->Value = tasks_info[i].time_left;

			TaskList->Rows[i]->Cells[7]->Value = gcnew System::String("Delete");
			TaskList->Rows[i]->Cells[8]->Value = gcnew System::String("Export");

			if (tasks_info[i].time_left >= 60)
			{
				TaskList->Rows[i]->DefaultCellStyle->BackColor = Color::Green;
			}
			else
			{
				TaskList->Rows[i]->DefaultCellStyle->BackColor = Color::Red;
			}
		}
		this->Cursor = Cursors::Default;
	}

	void MainForm::check_show_cycle()
	{
		boost::interprocess::shared_memory_object obj;
		try
		{
			obj = boost::interprocess::shared_memory_object(boost::interprocess::create_only, "ShowTaskManagerBool", boost::interprocess::read_write);
			obj.truncate(sizeof(bool));
		}
		catch (boost::interprocess::interprocess_exception &e)
		{
			if (e.get_error_code() == boost::interprocess::already_exists_error)
				obj = boost::interprocess::shared_memory_object(boost::interprocess::open_only, "ShowTaskManagerBool", boost::interprocess::read_write);
			else
				throw;
		}
		boost::interprocess::mapped_region region(obj, boost::interprocess::read_write);
		bool *show_window = static_cast<bool*>(region.get_address());
		*show_window = false;

		while (!m_check_show_thread_exit)
		{
			if (*show_window)
			{
				m_hide = false;
				this->Show();
				*show_window = false;
			}
			Sleep(1000);
		}

		boost::interprocess::shared_memory_object::remove("ShowTaskManagerBool");
	}

	System::Void MainForm::RefreshButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		refresh();
	}
	System::Void MainForm::createTaskToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		m_CreateForm = gcnew TaskManagerForm::CreateTaskForm;
		m_CreateForm->Show();
	}
	System::Void MainForm::exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		m_exit = true;
		this->Close();
	}
	System::Void MainForm::TaskList_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
	{
		try
		{
			unsigned int id;
			if (e->ColumnIndex == 7)
			{
				id = atoi(msclr::interop::marshal_as<std::string>(this->TaskList->Rows[e->RowIndex]->Cells[0]->Value->ToString()).c_str());
				m_TaskManager->delete_task(id);
				refresh();
				MessageBox::Show(L"Task was successfully deleted!", L"Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else if (e->ColumnIndex == 8)
			{
				id = atoi(msclr::interop::marshal_as<std::string>(this->TaskList->Rows[e->RowIndex]->Cells[0]->Value->ToString()).c_str());
				System::Windows::Forms::DialogResult result = ExportTask->ShowDialog();
				if (result == System::Windows::Forms::DialogResult::OK)
				{
					std::string file_name = msclr::interop::marshal_as<std::string>(ExportTask->SelectedPath) + "/Task.tm";
					m_TaskManager->export_task(file_name.c_str(), id);
					MessageBox::Show(L"Task was successfully exported!", L"Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
		}
		catch (Task_Exception &e)
		{
			MessageBox::Show(gcnew String(e.Get_as_string_with_solution().c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	System::Void MainForm::importTaskToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			System::Windows::Forms::DialogResult result = ImportTask->ShowDialog();

			if (result == System::Windows::Forms::DialogResult::OK)
			{
				std::string file_name = msclr::interop::marshal_as<std::string>(ImportTask->FileName);
				m_TaskManager->import_task(file_name.c_str());
				refresh();
				MessageBox::Show(L"Task was successfully imported!", L"Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		catch (Task_Exception &e)
		{
			MessageBox::Show(gcnew String(e.Get_as_string_with_solution().c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	
		}
	}
	System::Void MainForm::MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		m_hide = true;
		this->Hide();
		if(!m_exit)
			e->Cancel = true;
	}
	System::Void MainForm::MainForm_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (m_hide)
			this->Visible = false;
		else
			this->Visible = true;
	}
}
