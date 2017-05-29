#include "mainform.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	DFTool::mainform form;
	Application::Run(%form);
}

System::Void DFTool::mainform::mainform_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	try {
			openINI->ShowDialog();
			wchar_t name[MAX_PATH];
			ZeroMemory(name, MAX_PATH);
			wcscpy(name, OpenDialog1->FileName.c_str());
			ini_file = _wfopen(name, L"r");
			if (ini_file == NULL)
				throw Exception("settings.ini isn`t opened");
			int a = fread(buf, sizeof(char), 1000 - 5, ini_file);
			if (a == 0)
				throw Exception("settings.ini error reading");
			fclose(ini_file);
			ini_loaded = true;
	}
	catch (Exception^ e) {
		//fclose(ini_file);
		//Application->ShowException(&exception);
		//Application->~TApplication();
	}
}
