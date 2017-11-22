#pragma once
#include "stdafx.h"

namespace TaskManagerForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CreateTaskForm
	/// </summary>
	public ref class CreateTaskForm : public System::Windows::Forms::Form
	{
	public:
		CreateTaskForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			m_step = 0;
			
			Task_header_t header = InputHeader();
			Task_trigger *trigger = InputTrigger();
			Task_act *act = InputAct();

			
			//TaskManagerForm::MainForm::Get()->Get_TaskManager()->create_task(header, trigger, act);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CreateTaskForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  PreviousStepBtn;
	private: System::Windows::Forms::Button^  NextStepBtn;
	private: System::Windows::Forms::Label^  TaskNameLabel;
	private: System::Windows::Forms::Label^  TaskDescLabel;
	private: System::Windows::Forms::TextBox^  TaskName;
	private: System::Windows::Forms::RichTextBox^  TaskDesc;
	private: System::Windows::Forms::Label^  MainHeaderLabel;
	private: System::Windows::Forms::GroupBox^  StepOneBox;
	private: System::Windows::Forms::GroupBox^  StepTwoBox;
	private: System::Windows::Forms::Label^  TrigTypeLabel;
	private: System::Windows::Forms::ComboBox^  TrigType;
	private: System::Windows::Forms::Label^  TrigTimeLabel;
	private: System::Windows::Forms::MaskedTextBox^  TrigTime;
	private: System::Windows::Forms::CheckedListBox^  MonthlyDays;
	private: System::Windows::Forms::Label^  MonthlyDaysLabel;
	private: System::Windows::Forms::GroupBox^  MonthlyBox;
	private: System::Windows::Forms::CheckedListBox^  MonthlyMonths;
	private: System::Windows::Forms::Label^  MonthlyMonthsLabel;
	private: System::Windows::Forms::GroupBox^  WeeklyBox;
	private: System::Windows::Forms::CheckedListBox^  WeeklyWDays;
	private: System::Windows::Forms::Label^  WeeklyWDaysLabel;
	private: System::Windows::Forms::Label^  WeeklyEveryNWeekLabel;
	private: System::Windows::Forms::NumericUpDown^  WeeklyEveryNWeek;
	private: System::Windows::Forms::GroupBox^  StepThreeBox;
	private: System::Windows::Forms::GroupBox^  ProgramBox;
	private: System::Windows::Forms::TextBox^  ProgramParams;
	private: System::Windows::Forms::Label^  ProgramNameLabel;
	private: System::Windows::Forms::Label^  ProgramParamsLabel;
	private: System::Windows::Forms::TextBox^  ProgramName;
	private: System::Windows::Forms::GroupBox^  MessageBox;
	private: System::Windows::Forms::Label^  MessageNameLabel;
	private: System::Windows::Forms::RichTextBox^  MessageText;
	private: System::Windows::Forms::Label^  MessageTextLabel;
	private: System::Windows::Forms::TextBox^  MessageName;
	private: System::Windows::Forms::ComboBox^  ActType;
	private: System::Windows::Forms::Label^  ActTypeLabel;




	protected:




	protected:

	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		unsigned int m_step;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->PreviousStepBtn = (gcnew System::Windows::Forms::Button());
			this->NextStepBtn = (gcnew System::Windows::Forms::Button());
			this->TaskNameLabel = (gcnew System::Windows::Forms::Label());
			this->TaskDescLabel = (gcnew System::Windows::Forms::Label());
			this->TaskName = (gcnew System::Windows::Forms::TextBox());
			this->TaskDesc = (gcnew System::Windows::Forms::RichTextBox());
			this->MainHeaderLabel = (gcnew System::Windows::Forms::Label());
			this->StepOneBox = (gcnew System::Windows::Forms::GroupBox());
			this->StepTwoBox = (gcnew System::Windows::Forms::GroupBox());
			this->WeeklyBox = (gcnew System::Windows::Forms::GroupBox());
			this->WeeklyWDays = (gcnew System::Windows::Forms::CheckedListBox());
			this->WeeklyWDaysLabel = (gcnew System::Windows::Forms::Label());
			this->WeeklyEveryNWeekLabel = (gcnew System::Windows::Forms::Label());
			this->WeeklyEveryNWeek = (gcnew System::Windows::Forms::NumericUpDown());
			this->MonthlyBox = (gcnew System::Windows::Forms::GroupBox());
			this->MonthlyMonths = (gcnew System::Windows::Forms::CheckedListBox());
			this->MonthlyDays = (gcnew System::Windows::Forms::CheckedListBox());
			this->MonthlyMonthsLabel = (gcnew System::Windows::Forms::Label());
			this->MonthlyDaysLabel = (gcnew System::Windows::Forms::Label());
			this->TrigTimeLabel = (gcnew System::Windows::Forms::Label());
			this->TrigTime = (gcnew System::Windows::Forms::MaskedTextBox());
			this->TrigTypeLabel = (gcnew System::Windows::Forms::Label());
			this->TrigType = (gcnew System::Windows::Forms::ComboBox());
			this->StepThreeBox = (gcnew System::Windows::Forms::GroupBox());
			this->ProgramBox = (gcnew System::Windows::Forms::GroupBox());
			this->ProgramParams = (gcnew System::Windows::Forms::TextBox());
			this->ProgramNameLabel = (gcnew System::Windows::Forms::Label());
			this->ProgramParamsLabel = (gcnew System::Windows::Forms::Label());
			this->ProgramName = (gcnew System::Windows::Forms::TextBox());
			this->MessageBox = (gcnew System::Windows::Forms::GroupBox());
			this->MessageNameLabel = (gcnew System::Windows::Forms::Label());
			this->MessageText = (gcnew System::Windows::Forms::RichTextBox());
			this->MessageTextLabel = (gcnew System::Windows::Forms::Label());
			this->MessageName = (gcnew System::Windows::Forms::TextBox());
			this->ActType = (gcnew System::Windows::Forms::ComboBox());
			this->ActTypeLabel = (gcnew System::Windows::Forms::Label());
			this->StepOneBox->SuspendLayout();
			this->StepTwoBox->SuspendLayout();
			this->WeeklyBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->WeeklyEveryNWeek))->BeginInit();
			this->MonthlyBox->SuspendLayout();
			this->StepThreeBox->SuspendLayout();
			this->ProgramBox->SuspendLayout();
			this->MessageBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// PreviousStepBtn
			// 
			this->PreviousStepBtn->Enabled = false;
			this->PreviousStepBtn->Location = System::Drawing::Point(20, 413);
			this->PreviousStepBtn->Name = L"PreviousStepBtn";
			this->PreviousStepBtn->Size = System::Drawing::Size(75, 23);
			this->PreviousStepBtn->TabIndex = 8;
			this->PreviousStepBtn->Text = L"Previous";
			this->PreviousStepBtn->UseVisualStyleBackColor = true;
			this->PreviousStepBtn->Click += gcnew System::EventHandler(this, &CreateTaskForm::PreviousStepBtn_Click);
			// 
			// NextStepBtn
			// 
			this->NextStepBtn->Location = System::Drawing::Point(122, 413);
			this->NextStepBtn->Name = L"NextStepBtn";
			this->NextStepBtn->Size = System::Drawing::Size(75, 23);
			this->NextStepBtn->TabIndex = 5;
			this->NextStepBtn->Text = L"Next";
			this->NextStepBtn->UseVisualStyleBackColor = true;
			this->NextStepBtn->Click += gcnew System::EventHandler(this, &CreateTaskForm::NextStepBtn_Click);
			// 
			// TaskNameLabel
			// 
			this->TaskNameLabel->AutoSize = true;
			this->TaskNameLabel->Location = System::Drawing::Point(15, 28);
			this->TaskNameLabel->Name = L"TaskNameLabel";
			this->TaskNameLabel->Size = System::Drawing::Size(95, 17);
			this->TaskNameLabel->TabIndex = 0;
			this->TaskNameLabel->Text = L"Name of task:";
			// 
			// TaskDescLabel
			// 
			this->TaskDescLabel->AutoSize = true;
			this->TaskDescLabel->Location = System::Drawing::Point(15, 80);
			this->TaskDescLabel->Name = L"TaskDescLabel";
			this->TaskDescLabel->Size = System::Drawing::Size(165, 17);
			this->TaskDescLabel->TabIndex = 1;
			this->TaskDescLabel->Text = L"Short description of task:";
			// 
			// TaskName
			// 
			this->TaskName->Location = System::Drawing::Point(16, 48);
			this->TaskName->Name = L"TaskName";
			this->TaskName->Size = System::Drawing::Size(100, 22);
			this->TaskName->TabIndex = 2;
			// 
			// TaskDesc
			// 
			this->TaskDesc->Location = System::Drawing::Point(16, 100);
			this->TaskDesc->Name = L"TaskDesc";
			this->TaskDesc->Size = System::Drawing::Size(267, 67);
			this->TaskDesc->TabIndex = 3;
			this->TaskDesc->Text = L"";
			// 
			// MainHeaderLabel
			// 
			this->MainHeaderLabel->AutoSize = true;
			this->MainHeaderLabel->Font = (gcnew System::Drawing::Font(L"Open Sans", 12));
			this->MainHeaderLabel->Location = System::Drawing::Point(16, 16);
			this->MainHeaderLabel->Name = L"MainHeaderLabel";
			this->MainHeaderLabel->Size = System::Drawing::Size(181, 27);
			this->MainHeaderLabel->TabIndex = 4;
			this->MainHeaderLabel->Text = L"Fill info about task";
			// 
			// StepOneBox
			// 
			this->StepOneBox->Controls->Add(this->TaskName);
			this->StepOneBox->Controls->Add(this->TaskNameLabel);
			this->StepOneBox->Controls->Add(this->TaskDescLabel);
			this->StepOneBox->Controls->Add(this->TaskDesc);
			this->StepOneBox->Location = System::Drawing::Point(20, 46);
			this->StepOneBox->Name = L"StepOneBox";
			this->StepOneBox->Size = System::Drawing::Size(296, 184);
			this->StepOneBox->TabIndex = 6;
			this->StepOneBox->TabStop = false;
			this->StepOneBox->Text = L"Step 1/3";
			// 
			// StepTwoBox
			// 
			this->StepTwoBox->Controls->Add(this->WeeklyBox);
			this->StepTwoBox->Controls->Add(this->MonthlyBox);
			this->StepTwoBox->Controls->Add(this->TrigTimeLabel);
			this->StepTwoBox->Controls->Add(this->TrigTime);
			this->StepTwoBox->Controls->Add(this->TrigTypeLabel);
			this->StepTwoBox->Controls->Add(this->TrigType);
			this->StepTwoBox->Location = System::Drawing::Point(19, 46);
			this->StepTwoBox->Name = L"StepTwoBox";
			this->StepTwoBox->Size = System::Drawing::Size(367, 359);
			this->StepTwoBox->TabIndex = 7;
			this->StepTwoBox->TabStop = false;
			this->StepTwoBox->Text = L"Step 2/3";
			this->StepTwoBox->Visible = false;
			// 
			// WeeklyBox
			// 
			this->WeeklyBox->Controls->Add(this->WeeklyWDays);
			this->WeeklyBox->Controls->Add(this->WeeklyWDaysLabel);
			this->WeeklyBox->Controls->Add(this->WeeklyEveryNWeekLabel);
			this->WeeklyBox->Controls->Add(this->WeeklyEveryNWeek);
			this->WeeklyBox->Location = System::Drawing::Point(13, 141);
			this->WeeklyBox->Name = L"WeeklyBox";
			this->WeeklyBox->Size = System::Drawing::Size(233, 202);
			this->WeeklyBox->TabIndex = 8;
			this->WeeklyBox->TabStop = false;
			this->WeeklyBox->Text = L"Select info for weekly trigger";
			this->WeeklyBox->Visible = false;
			// 
			// WeeklyWDays
			// 
			this->WeeklyWDays->FormattingEnabled = true;
			this->WeeklyWDays->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat",
					L"Sun"
			});
			this->WeeklyWDays->Location = System::Drawing::Point(10, 99);
			this->WeeklyWDays->Name = L"WeeklyWDays";
			this->WeeklyWDays->Size = System::Drawing::Size(120, 89);
			this->WeeklyWDays->TabIndex = 3;
			// 
			// WeeklyWDaysLabel
			// 
			this->WeeklyWDaysLabel->AutoSize = true;
			this->WeeklyWDaysLabel->Location = System::Drawing::Point(7, 72);
			this->WeeklyWDaysLabel->Name = L"WeeklyWDaysLabel";
			this->WeeklyWDaysLabel->Size = System::Drawing::Size(137, 17);
			this->WeeklyWDaysLabel->TabIndex = 2;
			this->WeeklyWDaysLabel->Text = L"Select days of week:";
			// 
			// WeeklyEveryNWeekLabel
			// 
			this->WeeklyEveryNWeekLabel->AutoSize = true;
			this->WeeklyEveryNWeekLabel->Location = System::Drawing::Point(7, 23);
			this->WeeklyEveryNWeekLabel->Name = L"WeeklyEveryNWeekLabel";
			this->WeeklyEveryNWeekLabel->Size = System::Drawing::Size(96, 17);
			this->WeeklyEveryNWeekLabel->TabIndex = 1;
			this->WeeklyEveryNWeekLabel->Text = L"Every n week:";
			// 
			// WeeklyEveryNWeek
			// 
			this->WeeklyEveryNWeek->Location = System::Drawing::Point(10, 44);
			this->WeeklyEveryNWeek->Name = L"WeeklyEveryNWeek";
			this->WeeklyEveryNWeek->Size = System::Drawing::Size(108, 22);
			this->WeeklyEveryNWeek->TabIndex = 0;
			// 
			// MonthlyBox
			// 
			this->MonthlyBox->Controls->Add(this->MonthlyMonths);
			this->MonthlyBox->Controls->Add(this->MonthlyDays);
			this->MonthlyBox->Controls->Add(this->MonthlyMonthsLabel);
			this->MonthlyBox->Controls->Add(this->MonthlyDaysLabel);
			this->MonthlyBox->Location = System::Drawing::Point(13, 141);
			this->MonthlyBox->Name = L"MonthlyBox";
			this->MonthlyBox->Size = System::Drawing::Size(309, 171);
			this->MonthlyBox->TabIndex = 11;
			this->MonthlyBox->TabStop = false;
			this->MonthlyBox->Text = L"Select info for monthly trigger";
			this->MonthlyBox->Visible = false;
			// 
			// MonthlyMonths
			// 
			this->MonthlyMonths->FormattingEnabled = true;
			this->MonthlyMonths->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10", L"11", L"12"
			});
			this->MonthlyMonths->Location = System::Drawing::Point(17, 46);
			this->MonthlyMonths->Name = L"MonthlyMonths";
			this->MonthlyMonths->Size = System::Drawing::Size(123, 106);
			this->MonthlyMonths->TabIndex = 10;
			// 
			// MonthlyDays
			// 
			this->MonthlyDays->FormattingEnabled = true;
			this->MonthlyDays->Items->AddRange(gcnew cli::array< System::Object^  >(31) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23", L"24", L"25", L"26",
					L"27", L"28", L"29", L"30", L"31"
			});
			this->MonthlyDays->Location = System::Drawing::Point(167, 46);
			this->MonthlyDays->Name = L"MonthlyDays";
			this->MonthlyDays->Size = System::Drawing::Size(124, 106);
			this->MonthlyDays->TabIndex = 7;
			// 
			// MonthlyMonthsLabel
			// 
			this->MonthlyMonthsLabel->AutoSize = true;
			this->MonthlyMonthsLabel->Location = System::Drawing::Point(14, 26);
			this->MonthlyMonthsLabel->Name = L"MonthlyMonthsLabel";
			this->MonthlyMonthsLabel->Size = System::Drawing::Size(101, 17);
			this->MonthlyMonthsLabel->TabIndex = 9;
			this->MonthlyMonthsLabel->Text = L"Select months:";
			// 
			// MonthlyDaysLabel
			// 
			this->MonthlyDaysLabel->AutoSize = true;
			this->MonthlyDaysLabel->Location = System::Drawing::Point(165, 26);
			this->MonthlyDaysLabel->Name = L"MonthlyDaysLabel";
			this->MonthlyDaysLabel->Size = System::Drawing::Size(85, 17);
			this->MonthlyDaysLabel->TabIndex = 8;
			this->MonthlyDaysLabel->Text = L"Select days:";
			// 
			// TrigTimeLabel
			// 
			this->TrigTimeLabel->AutoSize = true;
			this->TrigTimeLabel->Location = System::Drawing::Point(10, 79);
			this->TrigTimeLabel->Name = L"TrigTimeLabel";
			this->TrigTimeLabel->Size = System::Drawing::Size(153, 17);
			this->TrigTimeLabel->TabIndex = 4;
			this->TrigTimeLabel->Text = L"Time from which begin:";
			// 
			// TrigTime
			// 
			this->TrigTime->Location = System::Drawing::Point(13, 99);
			this->TrigTime->Mask = L"00/00/0000 90:00";
			this->TrigTime->Name = L"TrigTime";
			this->TrigTime->Size = System::Drawing::Size(125, 22);
			this->TrigTime->TabIndex = 3;
			this->TrigTime->TextMaskFormat = System::Windows::Forms::MaskFormat::IncludePrompt;
			this->TrigTime->ValidatingType = System::DateTime::typeid;
			// 
			// TrigTypeLabel
			// 
			this->TrigTypeLabel->AutoSize = true;
			this->TrigTypeLabel->Location = System::Drawing::Point(10, 25);
			this->TrigTypeLabel->Name = L"TrigTypeLabel";
			this->TrigTypeLabel->Size = System::Drawing::Size(105, 17);
			this->TrigTypeLabel->TabIndex = 2;
			this->TrigTypeLabel->Text = L"Type of trigger:";
			// 
			// TrigType
			// 
			this->TrigType->FormattingEnabled = true;
			this->TrigType->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Once", L"Entrance", L"Dayly", L"Weekly", L"Monthly" });
			this->TrigType->SelectedIndex = 0;
			this->TrigType->Location = System::Drawing::Point(13, 45);
			this->TrigType->Name = L"TrigType";
			this->TrigType->Size = System::Drawing::Size(121, 24);
			this->TrigType->TabIndex = 1;
			this->TrigType->SelectedIndexChanged += gcnew System::EventHandler(this, &CreateTaskForm::TrigType_SelectedIndexChanged);
			// 
			// StepThreeBox
			// 
			this->StepThreeBox->Controls->Add(this->ProgramBox);
			this->StepThreeBox->Controls->Add(this->MessageBox);
			this->StepThreeBox->Controls->Add(this->ActType);
			this->StepThreeBox->Controls->Add(this->ActTypeLabel);
			this->StepThreeBox->Location = System::Drawing::Point(19, 46);
			this->StepThreeBox->Name = L"StepThreeBox";
			this->StepThreeBox->Size = System::Drawing::Size(333, 263);
			this->StepThreeBox->TabIndex = 9;
			this->StepThreeBox->TabStop = false;
			this->StepThreeBox->Text = L"Step 3/3";
			this->StepThreeBox->Visible = false;
			// 
			// ProgramBox
			// 
			this->ProgramBox->Controls->Add(this->ProgramParams);
			this->ProgramBox->Controls->Add(this->ProgramNameLabel);
			this->ProgramBox->Controls->Add(this->ProgramParamsLabel);
			this->ProgramBox->Controls->Add(this->ProgramName);
			this->ProgramBox->Location = System::Drawing::Point(17, 79);
			this->ProgramBox->Name = L"ProgramBox";
			this->ProgramBox->Size = System::Drawing::Size(263, 126);
			this->ProgramBox->TabIndex = 6;
			this->ProgramBox->TabStop = false;
			this->ProgramBox->Text = L"Input info for program action";
			this->ProgramBox->Visible = false;
			// 
			// ProgramParams
			// 
			this->ProgramParams->Location = System::Drawing::Point(6, 93);
			this->ProgramParams->Name = L"ProgramParams";
			this->ProgramParams->Size = System::Drawing::Size(136, 22);
			this->ProgramParams->TabIndex = 5;
			// 
			// ProgramNameLabel
			// 
			this->ProgramNameLabel->AutoSize = true;
			this->ProgramNameLabel->Location = System::Drawing::Point(6, 24);
			this->ProgramNameLabel->Name = L"ProgramNameLabel";
			this->ProgramNameLabel->Size = System::Drawing::Size(122, 17);
			this->ProgramNameLabel->TabIndex = 4;
			this->ProgramNameLabel->Text = L"Name of program:";
			// 
			// ProgramParamsLabel
			// 
			this->ProgramParamsLabel->AutoSize = true;
			this->ProgramParamsLabel->Location = System::Drawing::Point(5, 73);
			this->ProgramParamsLabel->Name = L"ProgramParamsLabel";
			this->ProgramParamsLabel->Size = System::Drawing::Size(203, 17);
			this->ProgramParamsLabel->TabIndex = 1;
			this->ProgramParamsLabel->Text = L"Start program with parameters:";
			// 
			// ProgramName
			// 
			this->ProgramName->Location = System::Drawing::Point(6, 44);
			this->ProgramName->Name = L"ProgramName";
			this->ProgramName->Size = System::Drawing::Size(136, 22);
			this->ProgramName->TabIndex = 2;
			// 
			// MessageBox
			// 
			this->MessageBox->Controls->Add(this->MessageNameLabel);
			this->MessageBox->Controls->Add(this->MessageText);
			this->MessageBox->Controls->Add(this->MessageTextLabel);
			this->MessageBox->Controls->Add(this->MessageName);
			this->MessageBox->Location = System::Drawing::Point(17, 78);
			this->MessageBox->Name = L"MessageBox";
			this->MessageBox->Size = System::Drawing::Size(289, 172);
			this->MessageBox->TabIndex = 5;
			this->MessageBox->TabStop = false;
			this->MessageBox->Text = L"Input info for message action";
			// 
			// MessageNameLabel
			// 
			this->MessageNameLabel->AutoSize = true;
			this->MessageNameLabel->Location = System::Drawing::Point(6, 24);
			this->MessageNameLabel->Name = L"MessageNameLabel";
			this->MessageNameLabel->Size = System::Drawing::Size(136, 17);
			this->MessageNameLabel->TabIndex = 4;
			this->MessageNameLabel->Text = L"Header of message:";
			// 
			// MessageText
			// 
			this->MessageText->Location = System::Drawing::Point(6, 93);
			this->MessageText->Name = L"MessageText";
			this->MessageText->Size = System::Drawing::Size(267, 67);
			this->MessageText->TabIndex = 3;
			this->MessageText->Text = L"";
			// 
			// MessageTextLabel
			// 
			this->MessageTextLabel->AutoSize = true;
			this->MessageTextLabel->Location = System::Drawing::Point(5, 73);
			this->MessageTextLabel->Name = L"MessageTextLabel";
			this->MessageTextLabel->Size = System::Drawing::Size(116, 17);
			this->MessageTextLabel->TabIndex = 1;
			this->MessageTextLabel->Text = L"Text of message:";
			// 
			// MessageName
			// 
			this->MessageName->Location = System::Drawing::Point(6, 44);
			this->MessageName->Name = L"MessageName";
			this->MessageName->Size = System::Drawing::Size(136, 22);
			this->MessageName->TabIndex = 2;
			// 
			// ActType
			// 
			this->ActType->FormattingEnabled = true;
			this->ActType->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Show message", L"Start program" });
			this->ActType->SelectedIndex = 0;
			this->ActType->Location = System::Drawing::Point(17, 48);
			this->ActType->Name = L"ActType";
			this->ActType->Size = System::Drawing::Size(128, 24);
			this->ActType->TabIndex = 4;
			this->ActType->SelectedIndexChanged += gcnew System::EventHandler(this, &CreateTaskForm::ActType_SelectedIndexChanged);
			// 
			// ActTypeLabel
			// 
			this->ActTypeLabel->AutoSize = true;
			this->ActTypeLabel->Location = System::Drawing::Point(15, 28);
			this->ActTypeLabel->Name = L"ActTypeLabel";
			this->ActTypeLabel->Size = System::Drawing::Size(102, 17);
			this->ActTypeLabel->TabIndex = 0;
			this->ActTypeLabel->Text = L"Type of action:";
			// 
			// CreateTaskForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(986, 721);
			this->Controls->Add(this->StepThreeBox);
			this->Controls->Add(this->PreviousStepBtn);
			this->Controls->Add(this->StepTwoBox);
			this->Controls->Add(this->StepOneBox);
			this->Controls->Add(this->NextStepBtn);
			this->Controls->Add(this->MainHeaderLabel);
			this->Name = L"CreateTaskForm";
			this->Text = L"Create task";
			this->StepOneBox->ResumeLayout(false);
			this->StepOneBox->PerformLayout();
			this->StepTwoBox->ResumeLayout(false);
			this->StepTwoBox->PerformLayout();
			this->WeeklyBox->ResumeLayout(false);
			this->WeeklyBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->WeeklyEveryNWeek))->EndInit();
			this->MonthlyBox->ResumeLayout(false);
			this->MonthlyBox->PerformLayout();
			this->StepThreeBox->ResumeLayout(false);
			this->StepThreeBox->PerformLayout();
			this->ProgramBox->ResumeLayout(false);
			this->ProgramBox->PerformLayout();
			this->MessageBox->ResumeLayout(false);
			this->MessageBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		void ShowStep();
		Task_header_t InputHeader();
		Task_trigger* InputTrigger();
		Task_act* InputAct();

		private: System::Void NextStepBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			if (++m_step == 2)
				this->NextStepBtn->Enabled = false;

			this->PreviousStepBtn->Enabled = true;

			ShowStep();
		}
		
		private: System::Void PreviousStepBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			if (--m_step == 0)
				this->PreviousStepBtn->Enabled = false;

			this->NextStepBtn->Enabled = true;

			ShowStep();
		}
		private: System::Void ActType_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			this->MessageBox->Visible = false;
			this->ProgramBox->Visible = false;

			if (this->ActType->SelectedIndex == 0)
				this->MessageBox->Visible = true;
			else
				this->ProgramBox->Visible = true;
		}
		private: System::Void TrigType_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	this->MonthlyBox->Visible = false;
	this->WeeklyBox->Visible = false;

	if (this->TrigType->SelectedIndex == 3)
		this->WeeklyBox->Visible = true;
	else if (this->TrigType->SelectedIndex == 4)
		this->MonthlyBox->Visible = true;
}
};
}
