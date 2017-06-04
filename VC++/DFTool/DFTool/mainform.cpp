#define _CRT_SECURE_NO_WARNINGS
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
	}
	else {
		ReadProcessMemory(hProcess, (void*)fnameaddr, firstname, 28, NULL);
		firstname[0] = toupper(firstname[0]);
		strcat(buf, firstname);
	}
	//
	strcat(buf, " ");
	//
	__int64 l1nameaddr;
	int l1nameind, l2nameind;
	char l1name[10], l2name[10];
	// name ind, p1
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += i * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x40;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameind, 4, NULL);
	// p2
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
		cProcesses = cbNeeded / sizeof(DWORD);
		if (cProcesses <= 0)
			throw gcnew Exception("Error EnumProcesses");
		for (DWORD i = 0; i < cProcesses; i++) {
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
			if (hProcess) {
				if (EnumProcessModulesEx(hProcess, &hModule, sizeof(HMODULE), &dummy, LIST_MODULES_64BIT)) {
					if (GetModuleBaseName(hProcess, hModule, szProcessName, sizeof(szProcessName) / sizeof(TCHAR))) {
						String^ str = gcnew String(szProcessName);
						if (("Dwarf Fortress.exe" == str) || ("Dwarf Fortress Rus.exe" == str)) {
							if (GetModuleInformation(hProcess, hModule, &modinfo, sizeof(MODULEINFO))) {
								DFStartAddr = (uint64_t)modinfo.lpBaseOfDll;
								hDF = hProcess;
								hDFWnd = FindWindow(L"SDL_app", L"Dwarf Fortress");

								PauseStateAddr = DFStartAddr + ml->GetAddrByName("pause");
								SeasonAddr = DFStartAddr + ml->GetAddrByName("season");
								SeasonTickAddr = DFStartAddr + ml->GetAddrByName("season_tick");
								StateAddr = DFStartAddr + ml->GetAddrByName("state");

								InitDebugFunction();
								InitTimeWarp();
								//if (Init_EAW())
								//	EAW_ON = true;
								//CheckBox1->Checked = EAW_ON;
								//Edit1->Text = IntToStr(Init_StartDwarf());
								progSt = ProgState::STATE_START;
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
	char PauseState; //pause game
	ReadProcessMemory(hDF, (void*)PauseStateAddr, &PauseState, 1, NULL);
	if (!PauseState) {
		PauseState = 1;
		WriteProcessMemory(hDF, (void*)PauseStateAddr, &PauseState, 1, NULL);
	}
	//
	void *ExtCode = VirtualAllocEx(hDF, NULL, 64, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	uint64_t Inject_point = DFStartAddr + ml->GetAddrByName("inject_point");
	// int
	uint8_t modsrc[13] = { 0x48,0xB9,0,0,0,0,0,0,0,0,0xFF,0xE1,0x90 };
	uint64_t JmpToEx = (uint64_t)ExtCode;
	memcpy(modsrc + 2, &JmpToEx, 8);
	WriteProcessMemory(hDF, (void*)Inject_point, modsrc, 13, NULL);
	// ext
	uint8_t Extern_code[34] = {/*mov eax,01*/0x05,0x01,0x00,0x00,0x00,
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

void DFTool::mainform::InitDebugFunction()
{
	DebugFuncAddr.Add(DFStartAddr + ml->GetAddrByName("debug") + 2);//no pause
	DebugFuncAddr.Add(DFStartAddr + ml->GetAddrByName("debug") + 9);//no moods
	DebugFuncAddr.Add(DFStartAddr + ml->GetAddrByName("debug") + 119);//no drink
	DebugFuncAddr.Add(DFStartAddr + ml->GetAddrByName("debug") + 10);//no eat
	DebugFuncAddr.Add(DFStartAddr + ml->GetAddrByName("debug") + 1);//no sleep
	DebugFuncAddr.Add(DFStartAddr + ml->GetAddrByName("debug") + 120);//no berserk
	DebugFuncAddr.Add(DFStartAddr + ml->GetAddrByName("debug") + 0);//fast mining
	DebugFuncAddr.Add(DFStartAddr + ml->GetAddrByName("debug") + 80235);//turbo speed

	for (int i = 0; i < DebugFuncAddr.Count; i++) {
		uint8_t state = 0;
		ReadProcessMemory(hDF, (void*)DebugFuncAddr[i], &state, 1, NULL);
		DebugFeatures->SetItemChecked(i, state);
		DebugFeaturesLastState.Add(state);
	}
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
		;	//TODO: err
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

System::Void DFTool::mainform::SetEmbarkPtBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Int32 count = -1;

	if (!Int32::TryParse(textBox1->Text, count)) {
		//TODO: err
		return;
	}

	if ((count >= 0) && (count < 2147483646)) {
		uint64_t tempAddr;
		uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
		ReadProcessMemory(hDF, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x8;
		ReadProcessMemory(hDF, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0xEC4;
		WriteProcessMemory(hDF, (void*)addr, &count, 4, NULL);
	}
}

System::Void DFTool::mainform::CheckStatTmr_Tick(System::Object ^ sender, System::EventArgs ^ e)
{
	if (progSt != ProgState::STATE_START) {
		int temp;
		if (!ReadProcessMemory(hDF, (void*)StateAddr, &temp, 4, NULL)) {
			progSt = ProgState::STATE_DISCON;
		}
		else {
			progSt = (ProgState)temp;
		}
	}
	switch (progSt) {
	case ProgState::STATE_MAIN:

		break;
	case ProgState::STATE_FORT:

		//Update_selected_unit_wnd();
		break;
	case ProgState::STATE_ADV:
		/*
		if (adv_first) {
			AttPoints(NULL, false);
			SkillPoints(NULL, false);
			short race = NULL;
			__int64 addrR = StartAddr + get_addr_by_name("main");
			ReadProcessMemory(hProcess, (void*)addrR, &addrR, 8, NULL);
			addrR += 0xB8;
			ReadProcessMemory(hProcess, (void*)addrR, &race, 2, NULL);
			Edit7->Text = IntToStr(race);
			adv_first = false;
		}

		update_coords(false, NULL, NULL, NULL);

		if (MaxSpeed)
			update_speed();
		*/
		break;
	case ProgState::STATE_START:
		//Button10->Enabled = !timewarpON;
		//Button32->Enabled = true;
		//PrintSetup1->Enabled = true;
		//Button1->Enabled = false;
		progSt = ProgState::STATE_IDLE;

		break;
	case ProgState::STATE_DISCON:

		break;
	default:
		break;
	}
}

System::Void DFTool::mainform::SetSpringBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint8_t SetSeason = 0;	//Spring
	WriteProcessMemory(hDF, (void*)SeasonAddr, &SetSeason, 1, NULL);
}

System::Void DFTool::mainform::SetSummerBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint8_t SetSeason = 1;	//Summer
	WriteProcessMemory(hDF, (void*)SeasonAddr, &SetSeason, 1, NULL);
}

System::Void DFTool::mainform::SetAutumnBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint8_t SetSeason = 2;	//Autumn
	WriteProcessMemory(hDF, (void*)SeasonAddr, &SetSeason, 1, NULL);
}

System::Void DFTool::mainform::SetWinterBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint8_t SetSeason = 3;	//Winter
	WriteProcessMemory(hDF, (void*)SeasonAddr, &SetSeason, 1, NULL);
}

System::Void DFTool::mainform::SetBeginningSeasonBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int tick = 1;
	WriteProcessMemory(hDF, (void*)SeasonTickAddr, &tick, 4, NULL);
}

System::Void DFTool::mainform::SetMidSeasonBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int tick = 10080 / 2;
	WriteProcessMemory(hDF, (void*)SeasonTickAddr, &tick, 4, NULL);
}

System::Void DFTool::mainform::SetEndSeasonBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int tick = 10079;
	WriteProcessMemory(hDF, (void*)SeasonTickAddr, &tick, 4, NULL);
}

System::Void DFTool::mainform::DebugFeatures_ItemCheck(System::Object ^ sender, System::Windows::Forms::ItemCheckEventArgs ^ e)
{
	uint8_t state = (bool)e->NewValue;
	WriteProcessMemory(hDF, (void*)DebugFuncAddr[e->Index], &state, 1, NULL);
	/*
	for (int i = 0; i < DebugFuncAddr.Count; i++) {
		uint8_t state = DebugFeatures->GetItemChecked(i);
		if ((bool)state != DebugFeaturesLastState[i]) {
			DebugFeaturesLastState[i] = (bool)state;
			WriteProcessMemory(hDF, (void*)DebugFuncAddr[i], &state, 1, NULL);
		}
	}
	*/
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
