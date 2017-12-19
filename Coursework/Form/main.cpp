// CppCLR_WinformsProjekt.cpp: Hauptprojektdatei.
#include "stdafx.h"
#include "MainForm.h"

#define SHOW_FORM

using namespace System;
using namespace System::Windows::Forms;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
// TO DO:
// Оператива жрется refresh'ом
// Fix problem with too many refreshes when 18:59 -> 19:00

[STAThread]
int main(array<String^>^ args)
{
	std::vector<std::string> argv;
	for (int i = 0; i < args->Length; ++i)
		argv.push_back(msclr::interop::marshal_as<std::string>(args[i]->ToString()));

	if (std::find(argv.begin(), argv.end(), "--help") != argv.end())
	{
		printf("\
Task Manager help\n\
=================\n\
This program was developed for creating and running tasks.\n\
\
\n\tTaskManager [parameters]\n\
\
\nparameters:\n\
\t--run, --r - run Task Manager\n\
\t--s, --show - show Task Manager after run (work only with \"--r\")\n\
\t--e, --entrance - make all entrance tasks (work only with \"--r\")\n\
");
		return 0;
	}

#ifndef SHOW_FORM
	if (std::find(argv.begin(), argv.end(), "--r") != argv.end() || std::find(argv.begin(), argv.end(), "--run") != argv.end())
	{


		bool hide, entrance;
		if (std::find(argv.begin(), argv.end(), "--s") != argv.end() || std::find(argv.begin(), argv.end(), "--show") != argv.end())
			hide = false;
		else
			hide = true;
		
		if (std::find(argv.begin(), argv.end(), "--e") != argv.end() || std::find(argv.begin(), argv.end(), "--entrance") != argv.end())
			entrance = true;
		else
			entrance = false;
#endif // !SHOW_FORM

#ifdef SHOW_FORM
		bool hide, entrance;
		hide = false;
		entrance = true;
#endif // SHOW_FORM


		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		Application::Run(gcnew TaskManagerForm::MainForm(hide, entrance));
#ifndef SHOW_FORM
	}
	else
	{
		boost::interprocess::shared_memory_object obj;
		try
		{
			obj = boost::interprocess::shared_memory_object(boost::interprocess::open_only, "ShowTaskManagerBool", boost::interprocess::read_write);
		}
		catch (boost::interprocess::interprocess_exception &e)
		{
			if (e.get_error_code() == boost::interprocess::not_found_error)
			{
				printf("\nError:\n\tShowTaskManagerBool was not created.\nSolution:\n\tBe sure that Task Manager was already started.\n\tIf not: start Task Manager with parameters \"--r --s\"\n");
				return 0;
			}
		}
		boost::interprocess::mapped_region region(obj, boost::interprocess::read_write);
		bool *show = static_cast<bool*>(region.get_address());
		*show = true;
		return 0;
	}
#endif // !SHOW_FORM
	return 0;
}