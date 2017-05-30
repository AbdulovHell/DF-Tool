#include <fstream>
#include <Windows.h>
#include <Psapi.h>
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

void DFTool::mainform::OpenDF()
{
	try {
		if (!ml->isLoaded())
			throw gcnew Exception("load config file first");
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		HANDLE hProcess;
		struct _MODULEINFO modinfo;
		DWORD v10;
		HMODULE hModule;
		wchar_t szProcessName[MAX_PATH] = TEXT("<unknown>");
		
		EnumProcesses(idProcess, sizeof(idProcess), &cbNeeded);
		cbNeeded >>= 2;
		if (cbNeeded <= 0)
			throw gcnew Exception("error EnumProcesses");
		for (int i = 0; i < cbNeeded; i++) {
			if (idProcess[i] < 5)
				continue;
			hDF = OpenProcess(PROCESS_ALL_ACCESS, FALSE, idProcess[i]);
			if (hDF) {
				if (EnumProcessModulesEx(hDF, &hModule, sizeof(HMODULE), &v10, LIST_MODULES_64BIT)) {
					if (GetModuleBaseName(hDF, hModule, szProcessName, sizeof(szProcessName) / sizeof(TCHAR))) {
						if ((strcmp("Dwarf Fortress.exe", szProcessName) == 0) || (strcmp("Dwarf Fortress Rus.exe", szProcessName) == 0)) {
							if (GetModuleInformation(hDF, hModule, &modinfo,	sizeof(MODULEINFO))) {
								StartAddr = (long long)modinfo.lpBaseOfDll;
								hProcess = hDF;
								hWnd = FindWindow("SDL_app", "Dwarf Fortress");
								//TODO: Fix it for 64bit
								long long plus = get_addr_by_name("pause");
								pause = StartAddr + plus;
								season = StartAddr + get_addr_by_name("season");
								season_tick = StartAddr + get_addr_by_name("season_tick");
								plus = get_addr_by_name("state");
								state_addr = StartAddr + plus;

								for (int i = 0; i < 11; i++)
									Debug_func[i] = StartAddr + get_addr_by_name("debug") + i;
								Init_DebugFunc();
								//if (Init_EAW())
								//	EAW_ON = true;
								//CheckBox1->Checked = EAW_ON;
								//Edit1->Text = IntToStr(Init_StartDwarf());
								state = STATE_START;
								Init_Timewarp();
								//read_d_init();
								/*block_addr =
								(__int64)StartAddr + get_addr_by_name
								("main_blck");
								ReadProcessMemory(hProcess, (void*)block_addr,
								old, 6, NULL);
								__int64 con3_addr, con4_addr;
								if (get_addr_by_name("main_condition")
								== 0x3BA4F3) {
								con3_addr =
								(__int64)StartAddr + get_addr_by_name
								("con3");
								con4_addr =
								(__int64)StartAddr + get_addr_by_name
								("con4");

								ReadProcessMemory(hProcess,
								(void*)con3_addr, con3_old, 6, NULL);
								ReadProcessMemory(hProcess,
								(void*)con4_addr, con4_old, 6, NULL);
								}
								Init_moodAcc();     */
								Timer1->Enabled = true;
								return;
							}
							//else
							//	ErrorExit(TEXT("GetModuleInformation"));
						}
					}
					//else
					//	ErrorExit(TEXT("GetModuleBaseName"));
				}
				//else
				//	ErrorExit(TEXT("EnumProcessModulesEx"));
			}
			//else
			//	ErrorExit(TEXT("OpenProcess"));
			CloseHandle(v5);
		}
		throw gcnew Exception("Dwarf Fortress.exe isn`t finded");
	}
	catch (Exception^ e) {
		MessageBoxA(0, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(e->Message), "Exception", 0);
	}
}

System::Void DFTool::mainform::mainform_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	openINI->ShowDialog();
	ml = gcnew MemoryLayout((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openINI->FileName));
	ml->isLoaded();
}

DFTool::mainform::MemoryLayout::MemoryLayout(const char * Dest)
{
	struct stat fi;
	stat(Dest, &fi);
	length = fi.st_size;

	std::ifstream ifs(Dest, std::ios::in | std::ios::binary);
	buffer = new char[length + 1];
	ifs.read(buffer, length);
	buffer[length] = 0;
	loaded = true;
}

bool DFTool::mainform::MemoryLayout::isLoaded()
{
	return loaded;
}

uint64_t DFTool::mainform::MemoryLayout::GetAddrByName(char * name)
{
	uint64_t addr = 0;
	char *pDest1, *pDest2;
	try {
		pDest1 = strstr(buffer, name);
		if (pDest1 == NULL)
			throw(gcnew Exception("parameter isn`t finded in settings.ini"));
		pDest2 = strpbrk(pDest1, "=");
		if (pDest2 == NULL)
			throw(gcnew Exception("internal error 1"));
		addr = strtol(pDest2 + 1, NULL, 0);
		if (addr == NULL)
			throw(gcnew Exception("internal error 2"));
		else
			return addr;
	}
	catch (Exception^ e) {
		MessageBoxA(0, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(e->Message), "Exception", 0);
	}
	return addr;
}
