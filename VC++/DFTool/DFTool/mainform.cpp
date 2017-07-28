#include <fstream>
#include <Windows.h>
#include <Psapi.h>
#include "DwarfEditor.h"
#include "InventoryEditor.h"
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

void DFTool::mainform::GetFullName(char * buf, uint32_t len, int i, uint64_t vect)
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
		strcat_s(buf, len, firstname);
	}
	else {
		ReadProcessMemory(hProcess, (void*)fnameaddr, firstname, 28, NULL);
		firstname[0] = toupper(firstname[0]);
		strcat_s(buf, len, firstname);
	}
	//
	strcat_s(buf, len, " ");
	//
	uint64_t l1nameaddr;
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

	strcat_s(buf, len, l1name);

	ReadProcessMemory(hProcess, (void*)ColNameOffset, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x50;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += (l2nameind + 1) * 8 - 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, l2name, 10, NULL);

	strcat_s(buf, len, l2name);

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
		if (hDF != NULL) CloseHandle(hDF);
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
						if ("Dwarf Fortress.exe" == str) {
							if (GetModuleInformation(hProcess, hModule, &modinfo, sizeof(MODULEINFO))) {
								DFStartAddr = (uint64_t)modinfo.lpBaseOfDll;
								hDF = hProcess;
								hDFWnd = FindWindow(L"SDL_app", L"Dwarf Fortress");
								infoLabel->Text = "Base addr: 0x" + InHex(DFStartAddr) + " Handle: 0x" + InHex((uint64_t)hDF);
								PauseStateAddr = DFStartAddr + ml->GetAddrByName("pause");
								SeasonAddr = DFStartAddr + ml->GetAddrByName("season");
								SeasonTickAddr = DFStartAddr + ml->GetAddrByName("season_tick");
								StateAddr = DFStartAddr + ml->GetAddrByName("state");

								InitDebugFunction();
								InitTimeWarp();
								StartDwarfEd->Text = InitStartDwarf().ToString();
								//CheckBox1->Checked = Init_EAW();
								//uint64_t block_addr = DFStartAddr + ml->GetAddrByName("main_blck");
								//ReadProcessMemory(hProcess, (void*)block_addr,old, 6, NULL);
								//Init_moodAcc();
								progSt = ProgState::STATE_START;
								CheckStatTmr->Enabled = true;
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
	DebugFuncAddr.Clear();

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
	}
}

int DFTool::mainform::InitStartDwarf()
{
	int count = 0;
	uint64_t addr = DFStartAddr + ml->GetAddrByName("start_dwarf");
	ReadProcessMemory(hDF, (void*)addr, &count, 4, NULL);
	return count;
}

void DFTool::mainform::UpdateSelectedUnitInfo()
{
	uint64_t num_addr = DFStartAddr + ml->GetAddrByName("selected_unit");
	uint64_t offset_addr = DFStartAddr + ml->GetAddrByName("active_creature_vect");
	int num = NULL;
	ReadProcessMemory(hDF, (void*)num_addr, &num, 4, NULL);
	int offset = num * 8;
	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);
	offset_addr += offset;
	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);

	// slaught
	char flags2; // 0xE4
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x10C + 2), &flags2, 1, NULL);
	char buf_flags2[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0, k = 7; i < 8; i++, k--) {
		buf_flags2[k] = (flags2 & (int)pow((double)2, i)) ? 49 : 48;
		//flags2 << 1;
	}
	SlaughtFlag->Checked = buf_flags2[6] - 48;
	// name
	char buf[100];
	strcpy_s(buf, 100, "");
	GetFullName(buf, 100, num, DFStartAddr + ml->GetAddrByName("active_creature_vect"));
	SelCreatureName->Text = gcnew String(buf);
}

int DFTool::mainform::SetAttPoints(int num, bool mode)
{
	if (mode) {	//set
		uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		WriteProcessMemory(hDF, (void*)(addr + 0x724), &num, 4, NULL);
		return num;
	}
	else {	//get
		uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		ReadProcessMemory(hDF, (void*)(addr + 0x724), &num, 4, NULL);
		return num;
	}
}

int DFTool::mainform::SetSkillPoints(int num, bool mode)
{
	if (mode) {	//set
		uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		WriteProcessMemory(hDF, (void*)(addr + 0x744), &num, 4, NULL);
		return num;
	}
	else {	//get
		uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		ReadProcessMemory(hDF, (void*)(addr + 0x744), &num, 4, NULL);
		return num;
	}
}

void DFTool::mainform::UpdateCoordinates(bool mode, short X, short Y, short Z)
{
	if (mode) {	//set
		short coords[3] = { X,Y,Z };
		uint64_t addr = DFStartAddr + ml->GetAddrByName("active_creature_vect");
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		WriteProcessMemory(hDF, (void*)(addr + 0xA0), coords, 6, NULL);
	}
	else {	//get
		short coords[3] = { 0,0,0 };
		uint64_t addr = DFStartAddr + ml->GetAddrByName("active_creature_vect");
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		ReadProcessMemory(hDF, (void*)(addr + 0xA0), coords, 6, NULL);
		CurXCoord->Text = coords[0].ToString();
		CurYCoord->Text = coords[1].ToString();
		CurZCoord->Text = coords[2].ToString();
	}
}

void DFTool::mainform::HealUnit(int unit)
{
	uint64_t offset_addr = DFStartAddr + ml->GetAddrByName("active_creature_vect");

	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);
	offset_addr += unit * 8;
	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);

	//refilling blood
	uint32_t bc = 0;
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x1D4), &bc, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x1D8), &bc, 4, NULL);
	//resetting grasp,stand,fly status
	uint16_t s2 = 0;
	ReadProcessMemory(hDF, (void*)(offset_addr + 0xBC0 + 0), &s2, 2, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0xBC0 + 0x2), &s2, 2, NULL);
	ReadProcessMemory(hDF, (void*)(offset_addr + 0xBC0 + 0x4), &s2, 2, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0xBC0 + 0x6), &s2, 2, NULL);
	ReadProcessMemory(hDF, (void*)(offset_addr + 0xBC0 + 0x8), &s2, 2, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0xBC0 + 0xA), &s2, 2, NULL);
	//status flags
	uint32_t flags = 0;
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x10C), &flags, 4, NULL);
	flags |= 0x10;	//calc nerv
	flags |= 0x20;	//calc bp
	flags &= 0xFFFFDFFF;	//has breaks
	flags &= 0xFFFFBFFF;	//gutted
	flags &= 0xFFFF7FFF;	//circ spray
	flags &= 0xFFFDFFFF;	//calc insulation
	flags |= 0x2000000;	//vision good
	flags &= 0xFBFFFFFF;	//vision damaged
	flags &= 0xF7FFFFFF;	//vision missing
	flags |= 0x10000000;	//breathing good
	flags &= 0xDFFFFFFF;	//breathing problem
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x10C), &flags, 4, NULL);

	ReadProcessMemory(hDF, (void*)(offset_addr + 0x110), &flags, 4, NULL);
	flags &= 0xFFFFEFFF;	//comp health
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x110), &flags, 4, NULL);
	//counters	7C4
	uint16_t counter2b = 0;
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x7C4 + 0x14), &counter2b, 2, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x7C4 + 0x16), &counter2b, 2, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x7C4 + 0x18), &counter2b, 2, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x7C4 + 0x1C), &counter2b, 2, NULL);
	uint32_t counter4b = 0;
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x7C4 + 0x30), &counter4b, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x7C4 + 0x34), &counter4b, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x7C4 + 0x38), &counter4b, 4, NULL);
	//counters2 950
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x950 + 0x0), &counter4b, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x950 + 0x8), &counter4b, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x950 + 0xC), &counter4b, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x950 + 0x10), &counter4b, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x950 + 0x14), &counter4b, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x950 + 0x18), &counter4b, 4, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x950 + 0x24), &counter4b, 4, NULL);
	//wounds
	uint64_t vect_start = NULL;
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0xC0), &vect_start, 8, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0xC8), &vect_start, 8, NULL);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0xD0), &vect_start, 8, NULL);
	uint32_t wound_next_id = 1;
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0xD8), &wound_next_id, 4, NULL);
	//body part status
	uint64_t nr_sta, nr_end;
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x30), &nr_sta, 8, NULL);
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x38), &nr_end, 8, NULL);
	size_t len = (nr_end - nr_sta) / 4;
	uint32_t fluid = 100;
	for (size_t i = 0; i < len; i++) {
		WriteProcessMemory(hDF, (void*)(nr_sta + i * 8), &fluid, 4, NULL);
	}

	uint32_t prcnt = 0;
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x48), &nr_sta, 8, NULL);
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x50), &nr_end, 8, NULL);
	len = (nr_end - nr_sta) / 4;
	uint64_t wa, cf, df, ef;
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x60), &wa, 8, NULL);
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x78), &cf, 8, NULL);
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x90), &df, 8, NULL);
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0xA8), &ef, 8, NULL);
	for (size_t i = 0; i < len; i++) {
		WriteProcessMemory(hDF, (void*)(nr_sta + i * 8), &prcnt, 4, NULL);
		WriteProcessMemory(hDF, (void*)(wa + i * 8), &prcnt, 4, NULL);
		WriteProcessMemory(hDF, (void*)(cf + i * 8), &prcnt, 4, NULL);
		WriteProcessMemory(hDF, (void*)(df + i * 8), &prcnt, 4, NULL);
		WriteProcessMemory(hDF, (void*)(ef + i * 8), &prcnt, 4, NULL);
	}

	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x0), &nr_sta, 8, NULL);
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x0 + 0x8), &nr_end, 8, NULL);
	len = (nr_end - nr_sta) / 4;
	for (size_t i = 0; i < len; i++) {
		WriteProcessMemory(hDF, (void*)(nr_sta + i * 8), &prcnt, 4, NULL);
	}
}

void DFTool::mainform::UpdateSpeed()
{
	short spd = 10;
	uint64_t addr = DFStartAddr + ml->GetAddrByName("active_creature_vect");
	ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
	ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
	WriteProcessMemory(hDF, (void*)(addr + 0x49C), &spd, 2, NULL);
}

String ^ DFTool::mainform::InHex(uint64_t addr)
{
	char* buf = new char[20];
	sprintf_s(buf, 20, "%I64X", addr);
	String^ str = gcnew String(buf);
	delete[] buf;
	return str;
}

System::Void DFTool::mainform::mainform_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	TimeWarpControls->Enabled = false;
	StartDwarfEd->Enabled = false;
	SetStartDwarfBtn->Enabled = false;
	tabControl1->TabPages[0]->Enabled = false;
	tabControl1->TabPages[1]->Enabled = false;
	tabControl1->TabPages[2]->Enabled = false;
	tabControl1->TabPages[3]->Enabled = false;
	openINI->ShowDialog();
	ml = gcnew MemoryLayout((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openINI->FileName));
	//ml->isLoaded();
}

System::Void DFTool::mainform::TimeWarpSetMultBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	UInt32 mult;
	if (System::UInt32::TryParse(TimeWarpMultEd->Text, mult))
		WriteProcessMemory(hDF, (void*)TimeWarpMultAddr, &mult, 4, NULL);
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

	if (!Int32::TryParse(EmbarkPointsEd->Text, count)) {
		//bad input
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
		TimeWarpControls->Enabled = true;
		StartDwarfEd->Enabled = true;
		SetStartDwarfBtn->Enabled = true;
		tabControl1->TabPages[0]->Enabled = false;
		tabControl1->TabPages[1]->Enabled = false;
		tabControl1->TabPages[2]->Enabled = false;
		tabControl1->TabPages[3]->Enabled = false;
		break;
	case ProgState::STATE_FORT:
		tabControl1->TabPages[0]->Enabled = true;
		tabControl1->TabPages[1]->Enabled = true;
		tabControl1->TabPages[2]->Enabled = false;
		tabControl1->TabPages[3]->Enabled = false;
		UpdateSelectedUnitInfo();
		break;
	case ProgState::STATE_ADV:
		tabControl1->TabPages[0]->Enabled = false;
		tabControl1->TabPages[1]->Enabled = false;
		tabControl1->TabPages[2]->Enabled = true;
		tabControl1->TabPages[3]->Enabled = true;
		if (adv_first) {
			SetAttPoints(NULL, false);
			SetSkillPoints(NULL, false);
			short race = NULL;
			uint64_t addrR = DFStartAddr + ml->GetAddrByName("main");
			ReadProcessMemory(hDF, (void*)addrR, &addrR, 8, NULL);
			ReadProcessMemory(hDF, (void*)(addrR + 0xB8), &race, 2, NULL);
			if (race < 0 || race>832) race = 572;
			this->RaceValue->Value = race;
			adv_first = false;
		}

		UpdateCoordinates(false, NULL, NULL, NULL);

		if (this->IntsMaxSpdChk->Checked)
			UpdateSpeed();

		break;
	case ProgState::STATE_START:
		TimeWarpControls->Enabled = true;
		StartDwarfEd->Enabled = true;
		SetStartDwarfBtn->Enabled = true;
		tabControl1->TabPages[0]->Enabled = false;
		tabControl1->TabPages[1]->Enabled = false;
		tabControl1->TabPages[2]->Enabled = false;
		tabControl1->TabPages[3]->Enabled = false;
		progSt = ProgState::STATE_IDLE;
		break;
	case ProgState::STATE_DISCON:
		TimeWarpControls->Enabled = false;
		StartDwarfEd->Enabled = false;
		SetStartDwarfBtn->Enabled = false;
		tabControl1->TabPages[0]->Enabled = false;
		tabControl1->TabPages[1]->Enabled = false;
		tabControl1->TabPages[2]->Enabled = false;
		tabControl1->TabPages[3]->Enabled = false;
		adv_first = false;
		infoLabel->Text = "";
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
}

System::Void DFTool::mainform::SetStartDwarfBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Int32 count = 7;
	if (!int::TryParse(StartDwarfEd->Text, count)) {
		return;	//bad input
	}
	if ((count > 1) && (count < 2147483646)) {
		uint64_t addr = DFStartAddr + ml->GetAddrByName("start_dwarf");
		WriteProcessMemory(hDF, (void*)addr, &count, 4, NULL);
	}
}

System::Void DFTool::mainform::EditCreatureBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint64_t num_addr = DFStartAddr + ml->GetAddrByName("selected_unit");
	int num;
	ReadProcessMemory(hDF, (void*)num_addr, &num, 4, NULL);
	DwarfEditor^ dfEd = gcnew DwarfEditor(SINGLE, num);
	dfEd->Show();
}

System::Void DFTool::mainform::SlaughtFlag_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	uint64_t num_addr = DFStartAddr + ml->GetAddrByName("selected_unit");
	uint64_t offset_addr = DFStartAddr + ml->GetAddrByName("active_creature_vect");
	int num;
	ReadProcessMemory(hDF, (void*)num_addr, &num, 4, NULL);
	int offset = num * 8;
	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);
	offset_addr += offset;
	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);

	uint8_t flags2;
	ReadProcessMemory(hDF, (void*)(offset_addr + 0x10C + 2), &flags2, 1, NULL);
	char buf[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0, k = 7; i < 8; i++, k--) {
		buf[k] = (flags2 & (int)pow((double)2, i)) ? 49 : 48;
		//flags2 << 1;
	}
	buf[6] = (int)SlaughtFlag->Checked + 48;
	flags2 = (uint8_t)strtol(buf, NULL, 2);
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x10C + 2), &flags2, 1, NULL);
}

System::Void DFTool::mainform::CancelJobBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint64_t num_addr = DFStartAddr + ml->GetAddrByName("selected_unit");
	uint64_t offset_addr = DFStartAddr + ml->GetAddrByName("active_creature_vect");
	uint32_t num;

	ReadProcessMemory(hDF, (void*)num_addr, &num, 4, NULL);

	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);
	offset_addr += num * 8;
	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);

	// job
	// 0x364(job) 0x30(current, set 0 to cancel)    0x8(job_type)
	uint64_t job = offset_addr + 0x4B0;
	// ReadProcessMemory(hProcess,(void*)job,&job,4,NULL);
	uint64_t current_job = 0;
	WriteProcessMemory(hDF, (void*)job, &current_job, 8, NULL);
}

System::Void DFTool::mainform::KillUnitBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint64_t num_addr = DFStartAddr + ml->GetAddrByName("selected_unit");
	uint64_t offset_addr = DFStartAddr + ml->GetAddrByName("active_creature_vect");
	uint32_t num;

	ReadProcessMemory(hDF, (void*)num_addr, &num, 4, NULL);
	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);
	offset_addr += num * 8;
	ReadProcessMemory(hDF, (void*)offset_addr, &offset_addr, 8, NULL);

	uint32_t vc = 2;
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x310 + 0x1C), &vc, 4, NULL);

	uint32_t bc = 0;
	WriteProcessMemory(hDF, (void*)(offset_addr + 0x4C8 + 0x1D8), &bc, 4, NULL);
}

System::Void DFTool::mainform::HealUnitBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint64_t num_addr = DFStartAddr + ml->GetAddrByName("selected_unit");
	uint32_t num;

	ReadProcessMemory(hDF, (void*)num_addr, &num, 4, NULL);
	HealUnit(num);
}

System::Void DFTool::mainform::SetAPBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int AP = 0;
	if (int::TryParse(this->APEdit->Text, AP))
		SetAttPoints(AP, true);
}

System::Void DFTool::mainform::SetSPBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int SP = 0;
	if (int::TryParse(this->SPEdit->Text, SP))
		SetSkillPoints(SP, true);
}

System::Void DFTool::mainform::AllAttrSet_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (AllAttrSet->SelectedIndex < 0 && AllAttrSet->SelectedIndex > 6) return;
	uint32_t stat[19];
	for (int i = 0; i < 19; i++)
		stat[i] = AllAttrSet->SelectedIndex;

	uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
	ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
	WriteProcessMemory(hDF, (void*)(addr + 0x2F8), stat, 4 * 19, NULL);
}

System::Void DFTool::mainform::SetAllSkillsAt5Btn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int stat[128];
	for (int i = 0; i < 128; i++)
		stat[i] = 20;

	uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
	ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
	WriteProcessMemory(hDF, (void*)(addr + 0xBC), stat, 4 * 128, NULL);
}

System::Void DFTool::mainform::SetRaceBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	uint16_t race = Decimal::ToUInt16(RaceValue->Value);
	uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
	ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
	WriteProcessMemory(hDF, (void*)(addr + 0xB8), &race, 2, NULL);
}

System::Void DFTool::mainform::RaceValue_ValueChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	uint16_t race = Decimal::ToUInt16(RaceValue->Value);
	uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
	ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
	WriteProcessMemory(hDF, (void*)(addr + 0xB8), &race, 2, NULL);
}

System::Void DFTool::mainform::RaceList_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	RaceValue->Value = 572 + RaceList->SelectedIndex;
	uint16_t race = Decimal::ToUInt16(RaceValue->Value);
	uint64_t addr = DFStartAddr + ml->GetAddrByName("main");
	ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
	WriteProcessMemory(hDF, (void*)(addr + 0xB8), &race, 2, NULL);
}

System::Void DFTool::mainform::CopyCoordBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	XCoordEd->Value = int::Parse(CurXCoord->Text);
	YCoordEd->Value = int::Parse(CurYCoord->Text);
	ZCoordEd->Value = int::Parse(CurZCoord->Text);
}

System::Void DFTool::mainform::SetCoordBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	UpdateCoordinates(true, Decimal::ToUInt16(XCoordEd->Value), Decimal::ToUInt16(YCoordEd->Value), Decimal::ToUInt16(ZCoordEd->Value));
}

System::Void DFTool::mainform::CurXCoord_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	XCoordEd->Value = int::Parse(CurXCoord->Text);
}

System::Void DFTool::mainform::CurYCoord_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	YCoordEd->Value = int::Parse(CurYCoord->Text);
}

System::Void DFTool::mainform::CurZCoord_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	ZCoordEd->Value = int::Parse(CurZCoord->Text);
}

System::Void DFTool::mainform::HealAdvBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	HealUnit(0);
}

System::Void DFTool::mainform::SkipTurnCkh_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	DecSpam->Enabled = SkipTurnCkh->Checked;
}

System::Void DFTool::mainform::DecSpam_Tick(System::Object ^ sender, System::EventArgs ^ e)
{
	DecSpam->Interval = Decimal::ToInt32(SkipIntValue->Value);

	PostMessage(hDFWnd, WM_KEYDOWN, 0x6E, 0x00530001);
	Sleep(1);
	PostMessage(hDFWnd, WM_KEYUP, 0x6E, 0xC0530001);
}

System::Void DFTool::mainform::InvEditStartBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	InventoryEditor^ InvEdit = gcnew InventoryEditor(0);
	InvEdit->Show();
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
