﻿#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <Windows.h>
#include <Psapi.h>
#include "DwarfEditor.h"
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

void DFTool::mainform::GetFullName(char * buf, int i, uint64_t vect)
{
	uint64_t NameOffset = vect;
	uint64_t ColNameOffset = DFStartAddr + ml->GetAddrByName("names");
	HANDLE hProcess = hDF;
	// char buf[100];
	// strcpy(buf,"");

	uint64_t fnameaddr;
	char firstname[28];
	ReadProcessMemory(hProcess, (void*)NameOffset, &fnameaddr, 8, NULL);
	fnameaddr += i * 8;
	ReadProcessMemory(hProcess, (void*)fnameaddr, &fnameaddr, 8, NULL);
	UCHAR mode = 0;
	ReadProcessMemory(hProcess, (void*)(fnameaddr + 0x14), &mode, 1, NULL);
	if (mode == 0x1F) {
		ReadProcessMemory(hProcess, (void*)fnameaddr, &fnameaddr, 8, NULL);
		ReadProcessMemory(hProcess, (void*)fnameaddr, firstname, 28, NULL);
		firstname[0] = toupper(firstname[0]);
		strcat(buf, firstname);
		// Edit2->Text=firstname;
	}
	else {
		ReadProcessMemory(hProcess, (void*)fnameaddr, firstname, 28, NULL);
		firstname[0] = toupper(firstname[0]);
		strcat(buf, firstname);
		// Edit2->Text=firstname;
	}
	//
	strcat(buf, " ");
	//
	__int64 l1nameaddr;
	int l1nameind, l2nameind;
	char l1name[10], l2name[10];
	// получение индексов имен, первой части
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += i * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x40;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameind, 4, NULL);
	// второй
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += i * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x44;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l2nameind, 4, NULL);
	//
	ReadProcessMemory(hProcess, (void*)ColNameOffset, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x50;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += (l1nameind + 1) * 8 - 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, l1name, 10, NULL);

	l1name[0] = toupper(l1name[0]);

	strcat(buf, l1name);

	ReadProcessMemory(hProcess, (void*)ColNameOffset, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x50;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += (l2nameind + 1) * 8 - 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, l2name, 10, NULL);

	strcat(buf, l2name);

	fix_name(buf);
}

char * DFTool::mainform::fix_name(char * name)
{
	uint64_t len = strlen(name);
	for (uint64_t i = 0; i < len; i++) {
		if (name[i] == 0xFFFFFF8C || name[i] == 0xFFFFFF8B ||
			name[i] == 0xFFFFFFA1)
			name[i] = 'i';
		if (name[i] == 0xFFFFFFA0 || name[i] == 0xFFFFFF86 ||
			name[i] == 0xFFFFFF83 || name[i] == 0xFFFFFF84)
			name[i] = 'a';
		if (name[i] == 0xFFFFFF89 || name[i] == 0xFFFFFF8A ||
			name[i] == 0xFFFFFF82 || name[i] == 0xFFFFFF88)
			name[i] = 'e';
		if (name[i] == 0xFFFFFF97 || name[i] == 0xFFFFFF96 ||
			name[i] == 0xFFFFFFA3)
			name[i] = 'u';
		if (name[i] == 0xFFFFFFA2 || name[i] == 0xFFFFFF93 ||
			name[i] == 0xFFFFFF94 || name[i] == 0xFFFFFF95)
			name[i] = 'o';
	}
	return name;
}

void DFTool::mainform::OpenDF()
{
	try {
		if (!ml->isLoaded())
			throw gcnew Exception("Load config file first");
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		HANDLE hProcess;
		struct _MODULEINFO modinfo;
		DWORD dummy;
		HMODULE hModule;
		wchar_t szProcessName[MAX_PATH] = TEXT("<unknown>");
		
		EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);
		cProcesses = cbNeeded/sizeof(DWORD);
		if (cProcesses <= 0)
			throw gcnew Exception("Error EnumProcesses");
		for (DWORD i = 0; i < cProcesses; i++) {
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
			if (hProcess) {
				if (EnumProcessModulesEx(hProcess, &hModule, sizeof(HMODULE), &dummy, LIST_MODULES_64BIT)) {
					if (GetModuleBaseName(hProcess, hModule, szProcessName, sizeof(szProcessName) / sizeof(TCHAR))) {
						String^ str = gcnew String(szProcessName);
						if (("Dwarf Fortress.exe" == str) || ("Dwarf Fortress Rus.exe" == str)) {
							if (GetModuleInformation(hProcess, hModule, &modinfo,	sizeof(MODULEINFO))) {
								DFStartAddr = (uint64_t)modinfo.lpBaseOfDll;
								hDF = hProcess;
								hDFWnd = FindWindow(L"SDL_app", L"Dwarf Fortress");
								//TODO: Fix it for 64bit
								uint64_t PauseOffset = ml->GetAddrByName("pause");
								PauseStateAddr = DFStartAddr + PauseOffset;
								SeasonAddr = DFStartAddr + ml->GetAddrByName("season");
								SeasonTickAddr = DFStartAddr + ml->GetAddrByName("season_tick");
								StateAddr = DFStartAddr + ml->GetAddrByName("state");

								///for (int i = 0; i < 11; i++)
								///	Debug_func[i] = StartAddr + get_addr_by_name("debug") + i;
								///Init_DebugFunc();
								//if (Init_EAW())
								//	EAW_ON = true;
								//CheckBox1->Checked = EAW_ON;
								//Edit1->Text = IntToStr(Init_StartDwarf());
								progSt = ProgState::STATE_START;
								InitTimeWarp();
								/*block_addr =(__int64)StartAddr + get_addr_by_name("main_blck");
								ReadProcessMemory(hProcess, (void*)block_addr,old, 6, NULL);
								
								Init_moodAcc();     */
								///Timer1->Enabled = true;
								return;
							}
							//else
							//	throw gcnew Exception("GetModuleInformation");
						}
					}
					//else
					//	throw gcnew Exception("GetModuleBaseName");
				}
				//else
				//	throw gcnew Exception("EnumProcessModulesEx");
			}
			//else
			//	throw gcnew Exception("OpenProcess");
			CloseHandle(hProcess);
		}
		throw gcnew Exception("Dwarf Fortress.exe isn`t finded");
	}
	catch (Exception^ e) {
		MessageBoxA(0, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(e->Message), "Exception", 0);
	}
}

void DFTool::mainform::InitTimeWarp()
{
	unsigned char NOP;
	uint64_t addr_inj = DFStartAddr + ml->GetAddrByName("inject_point"); //+0xC
	ReadProcessMemory(hDF, (void*)(addr_inj + 0xC), &NOP, 1, NULL);
	if (NOP == 0x90) {
		TimeWarpEnBtn->Enabled = false;
		TimeWarpSetMultBtn->Enabled = true;
		TimeWarpMultEd->Enabled = true;

		unsigned int rate = 1;
		uint64_t offset;
		ReadProcessMemory(hDF, (void*)(addr_inj + 2), &offset, 8, NULL);
		TimeWarpMultAddr = offset + 1;
		ReadProcessMemory(hDF, (void*)TimeWarpMultAddr, &rate, 4, NULL);
		TimeWarpMultEd->Text = rate.ToString();
	}
}

void DFTool::mainform::EnableTimeWarp()
{
	char PauseState; //ставим паузу
	ReadProcessMemory(hDF, (void*)PauseStateAddr, &PauseState, 1, NULL);
	if (!PauseState) {
		PauseState = 1;
		WriteProcessMemory(hDF, (void*)PauseStateAddr, &PauseState, 1, NULL);
	}
	//
	void *ExtCode = VirtualAllocEx(hDF, NULL, 64, MEM_COMMIT | MEM_RESERVE,	PAGE_EXECUTE_READWRITE);
	uint64_t Inject_point = DFStartAddr + ml->GetAddrByName("inject_point");
	// меняем исходный код
	char modsrc[13] = { 0x48,0xB9,0,0,0,0,0,0,0,0,0xFF,0xE1,0x90 };
	uint64_t JmpToEx = (uint64_t)ExtCode;
	memcpy(modsrc + 2, &JmpToEx, 8);
	WriteProcessMemory(hDF, (void*)Inject_point, modsrc, 13, NULL);
	// внешний блок
	char Extern_code[34] = {/*mov eax,01*/0x05,0x01,0x00,0x00,0x00,
		/*mov*/0x48,0xB9,0,0,0,0,0,0,0,0, 			//+7	StartAddr+0x13030D4
		/*mov rcx,eax*/0x89,0x01,
		/*cmp eax*/0x3D,0x60,0x27,0x00,0x00,
		/*mov rcx*/0x48,0xB9,0,0,0,0,0,0,0,0,		//+24   Inject_point+0xD
		/*jmp rcx*/0xFF,0xE1 };
	uint64_t temp = DFStartAddr + 0x13030D4;
	memcpy(Extern_code + 7, &temp, 8);
	temp = Inject_point + 0xD;
	memcpy(Extern_code + 24, &temp, 8);
	WriteProcessMemory(hDF, ExtCode, Extern_code, 34, NULL);
	TimeWarpMultAddr = (uint64_t)ExtCode + 1;
	//
	PauseState = 0;
	WriteProcessMemory(hDF, (void*)PauseStateAddr, &PauseState, 1, NULL);
	TimeWarpMultEd->Enabled = true;
	TimeWarpSetMultBtn->Enabled = true;
	TimeWarpEnBtn->Enabled = false;
}

System::Void DFTool::mainform::mainform_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	openINI->ShowDialog();
	ml = gcnew MemoryLayout((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openINI->FileName));
	ml->isLoaded();
}

System::Void DFTool::mainform::TimeWarpSetMultBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	UInt32 mult;
	if (System::UInt32::TryParse(TimeWarpMultEd->Text, mult))
		WriteProcessMemory(hDF, (void*)TimeWarpMultAddr, &mult, 4, NULL);
	else
		;	//TODO: обработать ошибку
}

System::Void DFTool::mainform::TimeWarpEnBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	EnableTimeWarp();
}

System::Void DFTool::mainform::CnctBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	OpenDF();
}

System::Void DFTool::mainform::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DwarfEditor^ dfEd = gcnew DwarfEditor(EMBARK);
	dfEd->Show();
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
