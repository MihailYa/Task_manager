#pragma once
#include "stdafx.h"
#include "CreateTaskForm.h"
#define CONFIG_FILE_NAME "C:/Users/mikle/Documents/Visual Studio 2017/Projects/GitHub/Task_manager/Coursework/Debug/TasksConfig.tm"
//#define CONFIG_FILE_NAME "TasksConfig.tm"

namespace TaskManagerForm {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung f�r MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		/**
		* @param hide if need to hide window
		* @param entrance if need to start entrance tasks
		*/
		MainForm(bool hide, bool entrance);

		void refresh();

		Task_Manager* Get_TaskManager() { return m_TaskManager; }
		static MainForm^ Get() { return m_this; }

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~MainForm();

	private: System::Windows::Forms::Label^  ListHeader;
	private: System::Windows::Forms::DataGridView^  TaskList;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  TaskId;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  TaskName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  TaskDescription;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  TimeLeft;
	private: System::Windows::Forms::DataGridViewButtonColumn^  DeleteTask;
	private: System::Windows::Forms::DataGridViewButtonColumn^  TaskExport;
	private: System::Windows::Forms::Button^  RefreshButton;




	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  createTaskToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::FolderBrowserDialog^  ExportTask;
	private: System::Windows::Forms::ToolStripMenuItem^  importTaskToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  ImportTask;

	private:
		Task_Manager *m_TaskManager;
		CreateTaskForm^ m_CreateForm;
		Threading::Thread^ m_check_show_thread;
		bool m_check_show_thread_exit;
		bool m_exit;
		bool m_hide;
		static MainForm^ m_this;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ListHeader = (gcnew System::Windows::Forms::Label());
			this->TaskList = (gcnew System::Windows::Forms::DataGridView());
			this->TaskId = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TaskName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TaskDescription = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TimeLeft = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DeleteTask = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->TaskExport = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->RefreshButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->createTaskToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->importTaskToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExportTask = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->ImportTask = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TaskList))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// ListHeader
			// 
			this->ListHeader->AutoSize = true;
			this->ListHeader->Font = (gcnew System::Drawing::Font(L"Open Sans", 14));
			this->ListHeader->Location = System::Drawing::Point(12, 33);
			this->ListHeader->Name = L"ListHeader";
			this->ListHeader->Size = System::Drawing::Size(149, 33);
			this->ListHeader->TabIndex = 1;
			this->ListHeader->Text = L"List of tasks:";
			// 
			// TaskList
			// 
			this->TaskList->AllowUserToAddRows = false;
			this->TaskList->AllowUserToDeleteRows = false;
			this->TaskList->ColumnHeadersHeight = 30;
			this->TaskList->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->TaskList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->TaskId, this->TaskName,
					this->TaskDescription, this->TimeLeft, this->DeleteTask, this->TaskExport
			});
			this->TaskList->Location = System::Drawing::Point(18, 69);
			this->TaskList->Name = L"TaskList";
			this->TaskList->RowTemplate->Height = 24;
			this->TaskList->Size = System::Drawing::Size(653, 150);
			this->TaskList->TabIndex = 2;
			this->TaskList->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::TaskList_CellClick);
			// 
			// TaskId
			// 
			this->TaskId->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->TaskId->HeaderText = L"id";
			this->TaskId->Name = L"TaskId";
			this->TaskId->ReadOnly = true;
			this->TaskId->Width = 48;
			// 
			// TaskName
			// 
			this->TaskName->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->TaskName->HeaderText = L"Name";
			this->TaskName->Name = L"TaskName";
			this->TaskName->ReadOnly = true;
			this->TaskName->Width = 74;
			// 
			// TaskDescription
			// 
			this->TaskDescription->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->TaskDescription->HeaderText = L"Description";
			this->TaskDescription->Name = L"TaskDescription";
			this->TaskDescription->ReadOnly = true;
			this->TaskDescription->Width = 108;
			// 
			// TimeLeft
			// 
			this->TimeLeft->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->TimeLeft->HeaderText = L"Time left from last refresh";
			this->TimeLeft->Name = L"TimeLeft";
			this->TimeLeft->ReadOnly = true;
			this->TimeLeft->Width = 198;
			// 
			// DeleteTask
			// 
			this->DeleteTask->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->DeleteTask->HeaderText = L"Delete";
			this->DeleteTask->Name = L"DeleteTask";
			this->DeleteTask->Width = 55;
			// 
			// TaskExport
			// 
			this->TaskExport->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->TaskExport->HeaderText = L"Export";
			this->TaskExport->Name = L"TaskExport";
			this->TaskExport->Width = 54;
			// 
			// RefreshButton
			// 
			this->RefreshButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->RefreshButton->Location = System::Drawing::Point(518, 40);
			this->RefreshButton->Name = L"RefreshButton";
			this->RefreshButton->Size = System::Drawing::Size(75, 23);
			this->RefreshButton->TabIndex = 3;
			this->RefreshButton->Text = L"Refresh";
			this->RefreshButton->UseVisualStyleBackColor = true;
			this->RefreshButton->Click += gcnew System::EventHandler(this, &MainForm::RefreshButton_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripMenuItem1 });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(767, 28);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->createTaskToolStripMenuItem,
					this->importTaskToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(44, 24);
			this->toolStripMenuItem1->Text = L"File";
			// 
			// createTaskToolStripMenuItem
			// 
			this->createTaskToolStripMenuItem->Name = L"createTaskToolStripMenuItem";
			this->createTaskToolStripMenuItem->Size = System::Drawing::Size(159, 26);
			this->createTaskToolStripMenuItem->Text = L"Create task";
			this->createTaskToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::createTaskToolStripMenuItem_Click);
			// 
			// importTaskToolStripMenuItem
			// 
			this->importTaskToolStripMenuItem->Name = L"importTaskToolStripMenuItem";
			this->importTaskToolStripMenuItem->Size = System::Drawing::Size(159, 26);
			this->importTaskToolStripMenuItem->Text = L"Import task";
			this->importTaskToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::importTaskToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(159, 26);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// ImportTask
			// 
			this->ImportTask->Filter = L"Task files (.tm)|*.tm";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(767, 464);
			this->Controls->Add(this->RefreshButton);
			this->Controls->Add(this->TaskList);
			this->Controls->Add(this->ListHeader);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MainForm";
			this->Text = L"Task Manager";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->VisibleChanged += gcnew System::EventHandler(this, &MainForm::MainForm_VisibleChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TaskList))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		// Check if we need to show window
		void check_show_cycle();
		System::Void RefreshButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void createTaskToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void TaskList_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e);
		System::Void importTaskToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void MainForm_VisibleChanged(System::Object^  sender, System::EventArgs^  e);
};
}