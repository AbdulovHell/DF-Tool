// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "mirror.h"
#include <strsafe.h>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define STATE_MAIN 3
#define STATE_FORT 0
#define STATE_ADV 1
#define STATE_START 0xFF
#define STATE_DISCON 0xFF-1
#define STATE_IDLE 0xFF-2
TForm1 *Form1;
HANDLE hProcess;
HWND hWnd;
__int64 StartAddr;
BOOL EAW_ON = false;
__int64 pause;
__int64 timerate;
__int64 season;
__int64 season_tick;
TCheckBox *CheckBoxes[9];
__int64 Debug_func[11];
int state;
__int64 state_addr;
bool adv_first = true;
bool MaxSpeed = false;
bool init_d_init = false;
char old[6], con3_old[6], con4_old[6];
__int64 block_addr = NULL;
FILE *ini_file;
char buf[1000];
bool timewarpON = false;
bool strmoodAccON = false;
bool ini_loaded = false;

void ErrorExit(LPTSTR lpszFunction) {
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	__int64 dw = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL,
		SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40)
		*sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

int range_rand(int range_min, int range_max) {
	double u = ((double)rand() / (RAND_MAX + 1)) * (range_max - range_min) +
		range_min;
	return u;
}

char *fix_name(char *name) {
	__int64 len = strlen(name);
	for (__int64 i = 0; i < len; i++) {
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

void get_full_name(char *buf, int i, __int64 vect) {
	__int64 NameOffset = vect;
	__int64 ColNameOffset = get_dfstartaddr() + get_addr_by_name("names");
	HANDLE hProcess = get_process();
	// char buf[100];
	// strcpy(buf,"");

	__int64 fnameaddr;
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
	l1nameaddr += (l1nameind + 1)*8 - 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, l1name, 10, NULL);

	l1name[0] = toupper(l1name[0]);

	strcat(buf, l1name);

	ReadProcessMemory(hProcess, (void*)ColNameOffset, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x50;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += (l2nameind + 1)*8 - 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	ReadProcessMemory(hProcess, (void*)l1nameaddr, l2name, 10, NULL);

	strcat(buf, l2name);

	fix_name(buf);
}

__int64 get_dfstartaddr(void) {
	return StartAddr;
}

int get_dwarfcount(void) {   //TODO:find start_dwarf
	int dwarfs = NULL;
	//__int64 Startdwarf_addr = StartAddr + get_addr_by_name("start_dwarf");
	//ReadProcessMemory(hProcess, (void*)Startdwarf_addr, &dwarfs, 4, NULL);
	return 7;
}

HANDLE get_process(void) {
	return hProcess;
}

__int64 get_addr_by_name(char *name) {
	char *pDest1, *pDest2;
	try {
		pDest1 = strstr(buf, name);
		if (pDest1 == NULL)
			throw Exception("parameter isn`t finded in settings.ini");
		pDest2 = strpbrk(pDest1, "=");
		if (pDest2 == NULL)
			throw Exception("internal error 1");
		__int64 addr = strtol(pDest2 + 1, NULL, 0);
		if (addr == NULL)
			throw Exception("internal error 2");
		else
			return addr;
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
		Application->~TApplication();
	}
}

void patch_embark(void) {
	if (EAW_ON) {
		unsigned char buf[] = {0x90, 0x90};
		__int64 addr = (__int64)StartAddr + get_addr_by_name("embark");
		WriteProcessMemory(hProcess, (void*)addr, buf, 2, NULL);
	}
	else {
		unsigned char buf[] = {0x74, 0x05};
		__int64 addr = (__int64)StartAddr + get_addr_by_name("embark");
		WriteProcessMemory(hProcess, (void*)addr, buf, 2, NULL);
	}
}

int Init_EAW(void) {
	unsigned char buf[] = {0, 0};
	__int64 addr = (__int64)StartAddr + get_addr_by_name("embark");
	ReadProcessMemory(hProcess, (void*)addr, buf, 2, NULL);
	if ((buf[0] == 0x74) && (buf[1] == 0x5))
		return 0;
	if ((buf[0] == 0x90) && (buf[1] == 0x90))
		return 1;
	else
		Form1->Close();
	return 0xFF;
}

int Init_StartDwarf(void) {
	int count = 0;
	__int64 addr = (__int64)StartAddr + get_addr_by_name("start_dwarf");
	ReadProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
	return count;
}

void Init_Timewarp(void) {
	unsigned char temp;
	__int64 addr_inj = StartAddr + get_addr_by_name("inject_point"); //+0xC
	ReadProcessMemory(hProcess, (void*)(addr_inj+0xC), &temp, 1, NULL);
	if (temp == 0x90) {
		Form1->Button10->Enabled = false;
		timewarpON = true;
		Form1->Button11->Enabled = true;
		Form1->Edit4->Enabled = true;

		int rate=1;
		__int64 offset;
		ReadProcessMemory(hProcess, (void*)(addr_inj+2), &offset, 8, NULL);
		timerate = offset + 1;
		ReadProcessMemory(hProcess, (void*)timerate, &rate, 4, NULL);
		Form1->Edit4->Text = IntToStr(rate);
	}
	else
		timewarpON = false;
}

void Init_DebugFunc(void) {
	for (int i = 0, k = 0; i < 9; i++, k++) {
		if (k > 1)
			k += 2;
		char state = 0;
		ReadProcessMemory(hProcess, (void*)Debug_func[k], &state, 1, NULL);
		CheckBoxes[i]->Checked = state;
		if (k > 1)
			k -= 2;
	}
}

void Init_moodAcc(void) {
	unsigned char nops[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	ReadProcessMemory(hProcess, (void*)block_addr, nops, 6, NULL);
	if (nops[1] == 0x90)
		Form1->CheckBox24->Checked = true;
}

void read_d_init(void) {
	__int64 tempAddr = (__int64)StartAddr + get_addr_by_name("d_init");
	// +0x30 +0x31
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 4, NULL);
	char p1, p2;
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x30), &p1, 1, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x31), &p2, 1, NULL);

	Form1->CheckBox12->Checked = p1 & 0x80;
	Form1->CheckBox13->Checked = p1 & 0x40;
	Form1->CheckBox17->Checked = p1 & 0x8;
	Form1->CheckBox18->Checked = p1 & 0x4;
	Form1->CheckBox19->Checked = p1 & 0x2;
	Form1->CheckBox20->Checked = p1 & 0x1;

	Form1->CheckBox14->Checked = p2 & 0x20;
	Form1->CheckBox15->Checked = p2 & 0x10;
	Form1->CheckBox21->Checked = p2 & 0x8;
	Form1->CheckBox22->Checked = p2 & 0x4;
	Form1->CheckBox23->Checked = p2 & 0x2;
	Form1->CheckBox16->Checked = p2 & 0x1;

	char index = 0;
	index = p1 & 0x20; // p1&0x20
	index += p1 & 0x10; // p1&0x10
	index >>= 4;
	Form1->ComboBox3->ItemIndex = (int)index;

	Form1->CheckBox12->Enabled = true;
	Form1->CheckBox13->Enabled = true;
	Form1->CheckBox17->Enabled = true;
	Form1->CheckBox18->Enabled = true;
	Form1->CheckBox19->Enabled = true;
	Form1->CheckBox20->Enabled = true;

	Form1->CheckBox14->Enabled = true;
	Form1->CheckBox15->Enabled = true;
	Form1->CheckBox21->Enabled = true;
	Form1->CheckBox22->Enabled = true;
	Form1->CheckBox23->Enabled = true;
	Form1->CheckBox16->Enabled = true;
	Form1->ComboBox3->Enabled = true;
	init_d_init = true;
}

void AttPoints(int num, bool mode) {
	if (mode) { // set
		int count = StrToInt(Form1->Edit5->Text);
		__int64 addr = StartAddr + get_addr_by_name("main");
		ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
		addr += 0x724; //
		WriteProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
	}
	else { // get
		int count = 0;
		__int64 addr = StartAddr + get_addr_by_name("main");
		ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
		addr += 0x724;
		ReadProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
		Form1->Edit5->Text = IntToStr(count);
	}
}

void SkillPoints(int num, bool mode) {
	if (mode) { // set
		int count = StrToInt(Form1->Edit6->Text);
		__int64 addr = StartAddr + get_addr_by_name("main");
		ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
		addr += 0x744;
		WriteProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
	}
	else { // get
		int count = 0;
		__int64 addr = StartAddr + get_addr_by_name("main");
		ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
		addr += 0x744;
		ReadProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
		Form1->Edit6->Text = IntToStr(count);
	}
}

void update_coords(bool mode, short X, short Y, short Z) {
	if (mode) { // set
		short coords[3] = {X, Y, Z};
		__int64 addr = StartAddr + get_addr_by_name
			("active_creature_vect");
		ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
		addr += 0x0;
		ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
		addr += 0xA0;
		WriteProcessMemory(hProcess, (void*)addr, coords, 6, NULL);
	}
	else { // get
		short coords[3] = {0, 0, 0};
		__int64 addr = StartAddr + get_addr_by_name
			("active_creature_vect");
		ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
		addr += 0x0;
		ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
		addr += 0xA0;
		ReadProcessMemory(hProcess, (void*)addr, coords, 6, NULL);
		Form1->Edit8->Text = IntToStr(coords[0]);
		Form1->Edit9->Text = IntToStr(coords[1]);
		Form1->Edit10->Text = IntToStr(coords[2]);
	}
}

void update_speed() {
	short spd = 10;
	__int64 addr = StartAddr + get_addr_by_name("active_creature_vect");
	ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
	addr += 0x0;
	ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
	addr += 0x49c; //TODO:spd offset???
	WriteProcessMemory(hProcess, (void*)addr, &spd, 2, NULL);
}

void Update_selected_unit_wnd() {
	__int64 num_addr = StartAddr + get_addr_by_name("selected_unit");
	__int64 offset_addr = StartAddr + get_addr_by_name("active_creature_vect");
	int num = NULL;
	ReadProcessMemory(hProcess, (void*)num_addr, &num, 4, NULL);
	int offset = num * 8;
	ReadProcessMemory(hProcess, (void*)offset_addr, &offset_addr, 8, NULL);
	offset_addr += offset;
	ReadProcessMemory(hProcess, (void*)offset_addr, &offset_addr, 8, NULL);
	// offset
	char offset_buf[20];
	sprintf(offset_buf, "0x%X", offset_addr);
	Form1->Label11->Caption = offset_buf;
	// slaught
	char flags2; // 0xE4
	ReadProcessMemory(hProcess, (void*)(offset_addr + 0x10C+2), &flags2,
		1, NULL);
	char buf_flags2[] = {0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0, k = 7; i < 8; i++, k--) {
		buf_flags2[k] = (flags2 & (int)pow((double)2, i)) ? 49 : 48;
		flags2 << 1;
	}
	Form1->CheckBox25->Checked = buf_flags2[6] - 48;
	// name
	char buf[100];
	strcpy(buf, "");
	int i = num;
	get_full_name(buf, i, get_dfstartaddr() + get_addr_by_name
		("active_creature_vect"));
	Form1->Label9->Caption = buf;
}

void Heal_unit(__int64 character) {
	/* TODO: Heal unit function
	 //print("Erasing wounds...")
	 while(unit_body_wounds > 0){
	 unit_body_wounds:erase(#unit.body.wounds-1)
	 }
	 unit.body.wound_next_id=1

	 //print("Refilling blood...")
	 unit.body.blood_count=unit.body.blood_max

	 //print("Resetting grasp/stand status...")
	 unit.status2.limbs_stand_count=unit.status2.limbs_stand_max
	 unit.status2.limbs_grasp_count=unit.status2.limbs_grasp_max

	 //print("Resetting status flags...")
	 unit.flags2.has_breaks=false
	 unit.flags2.gutted=false
	 unit.flags2.circulatory_spray=false
	 unit.flags2.vision_good=true
	 unit.flags2.vision_damaged=false
	 unit.flags2.vision_missing=false
	 unit.flags2.breathing_good=true
	 unit.flags2.breathing_problem=false

	 unit.flags2.calculated_nerves=false
	 unit.flags2.calculated_bodyparts=false
	 unit.flags2.calculated_insulation=false
	 unit.flags3.compute_health=true

	 //print("Resetting counters...")
	 unit.counters.winded=0
	 unit.counters.stunned=0
	 unit.counters.unconscious=0
	 unit.counters.webbed=0
	 unit.counters.pain=0
	 unit.counters.nausea=0
	 unit.counters.dizziness=0

	 unit.counters2.paralysis=0
	 unit.counters2.fever=0
	 unit.counters2.exhaustion=0
	 unit.counters2.hunger_timer=0
	 unit.counters2.thirst_timer=0
	 unit.counters2.sleepiness_timer=0
	 unit.counters2.vomit_timeout=0

	 //print("Resetting body part status...")
	 local v=unit.body.components
	 for i=0,#v.nonsolid_remaining - 1,1 do
	 v.nonsolid_remaining[i] = 100    // percent remaining of fluid layers (Urist Da Vinci)
	 end

	 v=unit.body.components
	 for i=0,#v.layer_wound_area - 1,1 do
	 v.layer_status[i].whole = 0        // severed, leaking layers (Urist Da Vinci)
	 v.layer_wound_area[i] = 0        // wound contact areas (Urist Da Vinci)
	 v.layer_cut_fraction[i] = 0        // 100*surface percentage of cuts/fractures on the body part layer (Urist Da Vinci)
	 v.layer_dent_fraction[i] = 0        // 100*surface percentage of dents on the body part layer (Urist Da Vinci)
	 v.layer_effect_fraction[i] = 0        // 100*surface percentage of "effects" on the body part layer (Urist Da Vinci)
	 end

	 v=unit.body.components.body_part_status
	 for i=0,#v-1,1 do
	 v[i].on_fire = false
	 v[i].missing = false
	 v[i].organ_loss = false
	 v[i].organ_damage = false
	 v[i].muscle_loss = false
	 v[i].muscle_damage = false
	 v[i].bone_loss = false
	 v[i].bone_damage = false
	 v[i].skin_damage = false
	 v[i].motor_nerve_severed = false
	 v[i].sensory_nerve_severed = false
	 end */
}

void __fastcall TForm1::OnKeyPress(TMessage &Message) {
	if (Message.WParam == 1) {
		GroupBox7->Enabled = GroupBox7->Enabled ? false : true;
		GroupBox7->Visible = GroupBox7->Visible ? false : true;
	}
}

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	CheckBoxes[0] = CheckBox2;
	CheckBoxes[1] = CheckBox3;
	CheckBoxes[2] = CheckBox4;
	CheckBoxes[3] = CheckBox5;
	CheckBoxes[4] = CheckBox6;
	CheckBoxes[5] = CheckBox7;
	CheckBoxes[6] = CheckBox8;
	CheckBoxes[7] = CheckBox9;
	CheckBoxes[8] = CheckBox10;
	RegisterHotKey(this->Handle, 1, MOD_CONTROL, 0x44);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::OpenDF(TObject *Sender) {
	try {
		if (!ini_loaded)
			throw Exception("load config file first");
		HANDLE v5 = NULL;
		DWORD idProcess[2000];
		DWORD cbNeeded = 0;
		struct _MODULEINFO modinfo;
		DWORD v10;
		HMODULE hModule;
		TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

		for (int i = 0; i < 2000; i++)
			idProcess[i] = 0;

		EnumProcesses((DWORD *)idProcess, 8000, &cbNeeded);
		// ïîëó÷àåì ñïèñîê èä ïðîöåññîâ
		cbNeeded >>= 2; // èõ êîë-âî
		if (cbNeeded <= 0)
			Close(); // åñëè íå ïîëó÷èëè, òî âûõîä

		for (int v4 = 0; v4 < cbNeeded; v4++) {
			if(idProcess[v4]<5)
				continue;
			v5 = OpenProcess(PROCESS_ALL_ACCESS, FALSE,idProcess[v4]);
			// 0x43A          , , idProcess[v4]
			// îòêðûâàåì ñ ïåðâîãî ïðîöåññà
			if (v5) {
				if (EnumProcessModulesEx(v5, &hModule, sizeof(HMODULE), &v10,LIST_MODULES_64BIT)) {
					if (GetModuleBaseName(v5, hModule, szProcessName,sizeof(szProcessName) / sizeof(TCHAR))){
						if ((strcmp("Dwarf Fortress.exe", szProcessName) == 0)
							|| (strcmp("Dwarf Fortress Rus.exe",
							szProcessName) == 0)) {
							if (GetModuleInformation(v5, hModule, &modinfo,
								sizeof(MODULEINFO))) {
								StartAddr = (long long)modinfo.lpBaseOfDll;
								hProcess = v5;
								hWnd = FindWindow("SDL_app", "Dwarf Fortress");
								//TODO: Fix it for 64bit
								long long plus=get_addr_by_name("pause");
								pause = StartAddr + plus;
								season = StartAddr + get_addr_by_name ("season");
								season_tick = StartAddr + get_addr_by_name("season_tick");
								plus=get_addr_by_name("state");
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
		throw Exception("Dwarf Fortress.exe isn`t finded");
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Change_Patch_state(TObject *Sender) {
	EAW_ON = CheckBox1->Checked;
	patch_embark();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Patch_StartDwarf(TObject *Sender) {
	int count = StrToInt(Edit1->Text);
	if ((count > 1) && (count < 2147483646)) {
		__int64 addr = (__int64)StartAddr + get_addr_by_name("start_dwarf");
		WriteProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender) {
	Button36->Enabled = true;
	Edit3->Enabled = true;
	Button5->Enabled = true;
	// Read Embark points
	int count = 0;
	long long tempAddr;
	long long addr = StartAddr + get_addr_by_name("main");
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x8;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0xEC4;
	ReadProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
	Edit3->Text = IntToStr(count);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender) {
	int count = -1;

	try {
		count = StrToInt(Edit3->Text);
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}

	if ((count >= 0) && (count < 2147483646)) {
		__int64 tempAddr;
		__int64 addr = StartAddr + get_addr_by_name("main");
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x8;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0xEC4;
		WriteProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender) {
	//
	char PauseState; //ставим паузу
	ReadProcessMemory(hProcess, (void*)pause, &PauseState, 1, NULL);
	if (!PauseState) {
		PauseState = 1;
		WriteProcessMemory(hProcess, (void*)pause, &PauseState, 1, NULL);
	}
	//
	void *ExtCode = VirtualAllocEx(hProcess, NULL, 64, MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE);
	__int64 Inject_point = StartAddr + get_addr_by_name("inject_point");
	// меняем исходный код
	char modsrc[13]={0x48,0xB9,0,0,0,0,0,0,0,0,0xFF,0xE1,0x90};
	__int64 JmpToEx=(__int64)ExtCode;
	memcpy(modsrc+2,&JmpToEx,8);
	WriteProcessMemory(hProcess, (void*)Inject_point, modsrc, 13, NULL);
	// внешний блок
	char Extern_code[34] = {/*mov eax,01*/0x05,0x01,0x00,0x00,0x00,
							/*mov*/0x48,0xB9,0,0,0,0,0,0,0,0, 			//+7	StartAddr+0x13030D4
							/*mov rcx,eax*/0x89,0x01,
							/*cmp eax*/0x3D,0x60,0x27,0x00,0x00,
							/*mov rcx*/0x48,0xB9,0,0,0,0,0,0,0,0,		//+24   Inject_point+0xD
							/*jmp rcx*/0xFF,0xE1};
	__int64 temp=StartAddr+0x13030D4;
	memcpy(Extern_code+7,&temp,8);
	temp=Inject_point+0xD;
	memcpy(Extern_code+24,&temp,8);
	WriteProcessMemory(hProcess, ExtCode, Extern_code, 34, NULL);
	timerate = (__int64)ExtCode + 1;
	//
	PauseState = 0;
	WriteProcessMemory(hProcess, (void*)pause, &PauseState, 1, NULL);
	Edit4->Enabled = true;
	Button11->Enabled = true;
	Button10->Enabled = false;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender) {
	int tmr = StrToInt(Edit4->Text);
	WriteProcessMemory(hProcess, (void*)timerate, &tmr, 4, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender) {
	char PauseState;
	ReadProcessMemory(hProcess, (void*)pause, &PauseState, 1, NULL);
	PauseState = (PauseState) ? 0 : 1;
	WriteProcessMemory(hProcess, (void*)pause, &PauseState, 1, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender) {
	char SetSeason = 0;
	if (Sender == Button12)
		SetSeason = 0;
	else if (Sender == Button13)
		SetSeason = 1;
	else if (Sender == Button14)
		SetSeason = 2;
	else if (Sender == Button15)
		SetSeason = 3;
	WriteProcessMemory(hProcess, (void*)season, &SetSeason, 1, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender) {
	int tick = 1;
	if (Sender == Button17)
		tick = 1;
	else if (Sender == Button18)
		tick = 10080 / 2;
	else if (Sender == Button16)
		tick = 10079;
	WriteProcessMemory(hProcess, (void*)season_tick, &tick, 4, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::deb_func(TObject *Sender) {
	for (int i = 0, k = 0; i < 9; i++, k++)
		if (CheckBoxes[i] == Sender) {
			if (k > 1)
				k += 2;
			char state = CheckBoxes[i]->Checked;
			WriteProcessMemory(hProcess, (void*)Debug_func[k], &state, 1, NULL);
		}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Check_stat(TObject *Sender) {
	if (state != STATE_START)
		if (!ReadProcessMemory(hProcess, (void*)state_addr, &state, 4, NULL)){
			state = STATE_DISCON;
			//ErrorExit(TEXT("ReadProcessMemory"));
		}
	switch (state) {
	case STATE_MAIN:
		Button4->Enabled = false;
		Button12->Enabled = false;
		Button13->Enabled = false;
		Button14->Enabled = false;
		Button15->Enabled = false;
		Button16->Enabled = false;
		Button17->Enabled = false;
		Button18->Enabled = false;
		Button19->Enabled = false;
		CheckBox2->Enabled = false;
		CheckBox3->Enabled = false;
		CheckBox4->Enabled = false;
		CheckBox5->Enabled = false;
		CheckBox6->Enabled = false;
		CheckBox7->Enabled = false;
		CheckBox8->Enabled = false;
		CheckBox9->Enabled = false;
		CheckBox10->Enabled = false;

		Edit5->Enabled = false;
		Edit6->Enabled = false;
		Edit7->Enabled = false;
		Edit8->Enabled = false;
		Edit9->Enabled = false;
		Edit10->Enabled = false;
		Edit11->Enabled = false;
		Edit12->Enabled = false;
		Edit13->Enabled = false;
		Button21->Enabled = false;
		Button22->Enabled = false;
		Button23->Enabled = false;
		Button24->Enabled = false;
		Button25->Enabled = false;
		Button26->Enabled = false;
		Button27->Enabled = false;
		Button28->Enabled = false;
		Button29->Enabled = false;
		Button30->Enabled = false;
		ComboBox2->Enabled = false;
		UpDown1->Enabled = false;
		ListBox1->Enabled = false;

		Button33->Enabled = false;
		CheckBox24->Enabled = false;

		CheckBox26->Enabled = false;
		Edit14->Enabled = false;
		UpDown5->Enabled = false;

		Button36->Enabled = false;
		Edit3->Enabled = false;
		Button5->Enabled = false;
		Button3->Enabled=false;
		// ComboBox1->Enabled=false;
		// Edit2->Enabled=false;
		// Button6->Enabled=false;
		// Button7->Enabled=false;
		// Button8->Enabled=false;
		// Button9->Enabled=false;

		CheckBox25->Enabled = false;
		Button34->Enabled = false;
		Button3->Enabled = false;

		break;
	case STATE_FORT:
		Button4->Enabled = true;
		Button12->Enabled = true;
		Button13->Enabled = true;
		Button14->Enabled = true;
		Button15->Enabled = true;
		Button16->Enabled = true;
		Button17->Enabled = true;
		Button18->Enabled = true;
		Button19->Enabled = true;
		//CheckBox2->Enabled = true;
		//CheckBox3->Enabled = true;
		//CheckBox4->Enabled = true;
		//CheckBox5->Enabled = true;
		//CheckBox6->Enabled = true;
		//CheckBox7->Enabled = true;
		//CheckBox8->Enabled = true;
		//CheckBox9->Enabled = true;
		//CheckBox10->Enabled = true;

		//Button33->Enabled = true;
		//CheckBox24->Enabled = true;

		Edit5->Enabled = false;
		Edit6->Enabled = false;
		Edit7->Enabled = false;
		Edit8->Enabled = false;
		Edit9->Enabled = false;
		Edit10->Enabled = false;
		Edit11->Enabled = false;
		Edit12->Enabled = false;
		Edit13->Enabled = false;
		Button21->Enabled = false;
		Button22->Enabled = false;
		Button23->Enabled = false;
		Button24->Enabled = false;
		Button25->Enabled = false;
		Button26->Enabled = false;
		Button27->Enabled = false;
		Button28->Enabled = false;
		Button29->Enabled = false;
		Button30->Enabled = false;
		ComboBox2->Enabled = false;
		UpDown1->Enabled = false;
		ListBox1->Enabled = false;
		CheckBox11->Enabled = false;

		CheckBox25->Enabled = true;
		Button34->Enabled = true;
		Button3->Enabled = true;

		Update_selected_unit_wnd();

		break;
	case STATE_ADV:
		Edit5->Enabled = true;
		Edit6->Enabled = true;
		Edit7->Enabled = true;
		Edit8->Enabled = true;
		Edit9->Enabled = true;
		Edit10->Enabled = true;
		Edit11->Enabled = true;
		Edit12->Enabled = true;
		Edit13->Enabled = true;
		Button21->Enabled = true;
		Button22->Enabled = true;
		Button23->Enabled = true;
		Button24->Enabled = true;
		Button25->Enabled = true;
		Button26->Enabled = true;
		Button27->Enabled = true;
		Button28->Enabled = true;
		Button29->Enabled = true;
		//Button30->Enabled = true;
		ComboBox2->Enabled = true;
		UpDown1->Enabled = true;
		ListBox1->Enabled = true;
		CheckBox11->Enabled = true;

		CheckBox26->Enabled = true;
		Edit14->Enabled = true;
		UpDown5->Enabled = true;
		CheckBox25->Enabled = false;
		Button34->Enabled = false;

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

		break;
	case STATE_START:
		//CheckBox1->Enabled = true;
		//Button2->Enabled = true;
		//Edit1->Enabled = true;
		Button10->Enabled = !timewarpON;
		Button32->Enabled = true;
		PrintSetup1->Enabled = true;
		Button1->Enabled = false;
		state = STATE_IDLE;

		break;
	case STATE_DISCON:
		CheckBox1->Enabled = false;
		Button2->Enabled = false;
		Edit1->Enabled = false;
		Button10->Enabled = false;
		Button32->Enabled = false;
		PrintSetup1->Enabled = false;
		Button1->Enabled = true;
		Timer1->Enabled = false;
		Edit4->Enabled = false;
		Button11->Enabled = false;

		Button4->Enabled = false;
		Button12->Enabled = false;
		Button13->Enabled = false;
		Button14->Enabled = false;
		Button15->Enabled = false;
		Button16->Enabled = false;
		Button17->Enabled = false;
		Button18->Enabled = false;
		Button19->Enabled = false;
		CheckBox2->Enabled = false;
		CheckBox3->Enabled = false;
		CheckBox4->Enabled = false;
		CheckBox5->Enabled = false;
		CheckBox6->Enabled = false;
		CheckBox7->Enabled = false;
		CheckBox8->Enabled = false;
		CheckBox9->Enabled = false;
		CheckBox10->Enabled = false;

		Button33->Enabled = false;
		CheckBox24->Enabled = false;

		CheckBox26->Enabled = false;
		Edit14->Enabled = false;
		UpDown5->Enabled = false;

		Edit5->Enabled = false;
		Edit6->Enabled = false;
		Edit7->Enabled = false;
		Edit8->Enabled = false;
		Edit9->Enabled = false;
		Edit10->Enabled = false;
		Edit11->Enabled = false;
		Edit12->Enabled = false;
		Edit13->Enabled = false;
		Button21->Enabled = false;
		Button22->Enabled = false;
		Button23->Enabled = false;
		Button24->Enabled = false;
		Button25->Enabled = false;
		Button26->Enabled = false;
		Button27->Enabled = false;
		Button28->Enabled = false;
		Button29->Enabled = false;
		Button30->Enabled = false;
		ComboBox2->Enabled = false;
		UpDown1->Enabled = false;
		ListBox1->Enabled = false;
		CheckBox11->Enabled = false;

		CheckBox25->Enabled = false;
		Button34->Enabled = false;
		Button3->Enabled = false;

		Edit3->Enabled = false;
		Button5->Enabled = false;
		Button3->Enabled=false;
		Button36->Enabled = false;
		// ComboBox1->Enabled=false;
		// Edit2->Enabled=false;
		// Button6->Enabled=false;
		// Button7->Enabled=false;
		// Button8->Enabled=false;
		// Button9->Enabled=false;

		Form1->CheckBox12->Enabled = false;
		Form1->CheckBox13->Enabled = false;
		Form1->CheckBox17->Enabled = false;
		Form1->CheckBox18->Enabled = false;
		Form1->CheckBox19->Enabled = false;
		Form1->CheckBox20->Enabled = false;

		Form1->CheckBox14->Enabled = false;
		Form1->CheckBox15->Enabled = false;
		Form1->CheckBox21->Enabled = false;
		Form1->CheckBox22->Enabled = false;
		Form1->CheckBox23->Enabled = false;
		Form1->CheckBox16->Enabled = false;
		Form1->ComboBox3->Enabled = false;
		init_d_init = false;

		break;
	default:
		break;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button21Click(TObject *Sender) {
	AttPoints(StrToInt(Edit5->Text), true);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button22Click(TObject *Sender) {
	SkillPoints(StrToInt(Edit6->Text), true);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button23Click(TObject *Sender) {
	int stat[19];
	for (int i = 0; i < 19; i++)
		stat[i] = ComboBox2->ItemIndex;

	__int64 addr = StartAddr + get_addr_by_name("main");
	ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
	addr += 0x2F8;
	WriteProcessMemory(hProcess, (void*)addr, &stat, 4*19, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button24Click(TObject *Sender) {
	int status = 1;

	if (Sender == Button24) {
		status = 0;
	}
	else if (Sender == Button25) {
		status = 1;
	}
	else if (Sender == Button26) {
		status = 2;
	}

	__int64 addr = StartAddr + get_addr_by_name("main");
	ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
	addr += 0x344;
	WriteProcessMemory(hProcess, (void*)addr, &status, 4, NULL);

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button27Click(TObject *Sender) {
	int stat[136];
	for (int i = 0; i < 136; i++)
		stat[i] = 20;

	__int64 addr = StartAddr + get_addr_by_name("main");
	ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
	addr += 0xBC;
	WriteProcessMemory(hProcess, (void*)addr, &stat, 136*4, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button28Click(TObject *Sender) {
	short race = StrToInt(Edit7->Text);

	__int64 addr = StartAddr + get_addr_by_name("main");
	ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
	addr += 0xB8;
	WriteProcessMemory(hProcess, (void*)addr, &race, 2, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button29Click(TObject *Sender) {
	update_coords(true, StrToInt(Edit11->Text), StrToInt(Edit12->Text),
		StrToInt(Edit13->Text));
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::setrace1(TObject *Sender, TUDBtnType Button) {
	short race = StrToInt(Edit7->Text);

	__int64 addr = StartAddr + get_addr_by_name("main");
	ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
	addr += 0xB8;
	WriteProcessMemory(hProcess, (void*)addr, &race, 2, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::CopyCoords(TObject *Sender) {
	Edit11->Text = Edit8->Text;
	Edit12->Text = Edit9->Text;
	Edit13->Text = Edit10->Text;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::MaxSpeedState(TObject *Sender) {
	MaxSpeed = CheckBox11->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender) {
	TForm *Dialog = get_about_pointer();
	Dialog->Visible = Dialog->Visible ? false : true;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender) {
	Close();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::PrintSetup1Click(TObject *Sender) {
	adv_first = true;        //TODO:REWORK!

	/*int count = 0;
	__int64 tempAddr;
	__int64 addr = StartAddr + get_addr_by_name("main");
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x8;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	if (get_addr_by_name("main") == 0x159C738)
		addr = tempAddr + 0xAA0;
	else
		addr = tempAddr + 0x9E4;
	ReadProcessMemory(hProcess, (void*)addr, &count, 4, NULL);
	Edit3->Text = IntToStr(count);  */
}
// ---------------------------------------------------------------------------


void __fastcall TForm1::ForumThread1Click(TObject *Sender) {
	AnsiString site = "http://www.bay12forums.com/smf/index.php?topic=152903.0";
	ShellExecute(NULL, "open", site.c_str(), NULL, NULL, SW_RESTORE);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Donate1Click(TObject *Sender) {
	AnsiString site =
		"https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=TY2YMFJQEJXWG";
	ShellExecute(NULL, "open", site.c_str(), NULL, NULL, SW_RESTORE);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button30Click(TObject *Sender) {
	TForm *Dialog = get_invedit_pointer();
	Dialog->Visible = Dialog->Visible ? false : true;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1Click(TObject *Sender) {
	Edit7->Text = IntToStr(572 + ListBox1->ItemIndex);

	short race = StrToInt(Edit7->Text);

	__int64 addr = StartAddr + get_addr_by_name("main");
	ReadProcessMemory(hProcess, (void*)addr, &addr, 8, NULL);
	addr += 0xB8;
	WriteProcessMemory(hProcess, (void*)addr, &race, 2, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Skip(TObject *Sender) {
	DecimalRepeat->Enabled = DecimalRepeat->Enabled ? false : true;
	CheckBox26->Checked = DecimalRepeat->Enabled;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::DecimalRepeatTimer(TObject *Sender) {
	int i = StrToInt(Edit14->Text);
	if (i > 0)
		DecimalRepeat->Interval = i;
	else
		DecimalRepeat->Interval = 1;

	PostMessage(hWnd, WM_KEYDOWN, 0x6E, 0x00530001);
	Sleep(1);
	PostMessage(hWnd, WM_KEYUP, 0x6E, 0xC0530001);
	// Sleep(1);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Change_d_init(TObject *Sender) {
	if (!init_d_init)
		return;
	__int64 tempAddr = (__int64)StartAddr + get_addr_by_name("d_init");
	// +0x30 +0x31
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 4, NULL);
	char p1, p2;
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x30), &p1, 1, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x31), &p2, 1, NULL);

	char p1buf[] = {0, 0, 0, 0, 0, 0, 0, 0};

	for (int i = 0, k = 7; i < 8; i++, k--) {
		p1buf[k] = (p1 & (int)pow((double)2, i)) ? 49 : 48;
		p1 << 1;
	}

	p1buf[0] = (int)Form1->CheckBox12->Checked + 48;
	p1buf[1] = (int)Form1->CheckBox13->Checked + 48;

	p1buf[4] = (int)Form1->CheckBox17->Checked + 48;
	p1buf[5] = (int)Form1->CheckBox18->Checked + 48;
	p1buf[6] = (int)Form1->CheckBox19->Checked + 48;
	p1buf[7] = (int)Form1->CheckBox20->Checked + 48;

	switch (Form1->ComboBox3->ItemIndex) {
	case 0:
		p1buf[2] = 0 + 48;
		p1buf[3] = 0 + 48;
		break;
	case 1:
		p1buf[2] = 0 + 48;
		p1buf[3] = 1 + 48;
		break;
	case 2:
		p1buf[2] = 1 + 48;
		p1buf[3] = 0 + 48;
		break;
	default:
		break;
	}

	p1 = strtol(p1buf, NULL, 2);

	char p2buf[] = {0, 0, 0, 0, 0, 0, 0, 0};

	for (int i = 0, k = 7; i < 8; i++, k--) {
		p2buf[k] = (p2 & (int)pow((double)2, i)) ? 49 : 48;
		p2 << 1;
	}

	p2buf[2] = (int)Form1->CheckBox14->Checked + 48;
	p2buf[3] = (int)Form1->CheckBox15->Checked + 48;
	p2buf[4] = (int)Form1->CheckBox21->Checked + 48;
	p2buf[5] = (int)Form1->CheckBox22->Checked + 48;
	p2buf[6] = (int)Form1->CheckBox23->Checked + 48;
	p2buf[7] = (int)Form1->CheckBox16->Checked + 48;

	p2 = strtol(p2buf, NULL, 2);

	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x30), &p1, 1, NULL);
	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x31), &p2, 1, NULL);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Act_DeAct_mood_acc(TObject *Sender) {
	char PauseState;
	ReadProcessMemory(hProcess, (void*)pause, &PauseState, 1, NULL);
	if (!PauseState) {
		PauseState = 1;
		WriteProcessMemory(hProcess, (void*)pause, &PauseState, 1, NULL);
	}
	//
	__int64 dwarf_addr = (__int64)StartAddr + get_addr_by_name("min_dwarf");
	__int64 maxmood_addr = (__int64)StartAddr + get_addr_by_name("max_in_mood");
	__int64 co_condition_addr = (__int64)StartAddr + get_addr_by_name
		("co_condition");
	__int64 condition1_addr = (__int64)StartAddr + get_addr_by_name("condition1");
	__int64 condition2_addr = (__int64)StartAddr + get_addr_by_name("condition2");

	__int64 con3_addr = NULL;
	__int64 con4_addr = NULL;
	if (get_addr_by_name("main_condition") == 0x3BA4F3) {
		con3_addr = (__int64)StartAddr + get_addr_by_name("con3");
		con4_addr = (__int64)StartAddr + get_addr_by_name("con4");
	}

	if (CheckBox24->Checked) {
		char nops[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
		char dwarfs = 0;
		char maxmood = 0xFF;
		char co_condition = 0x84;
		char condition1 = 0xFF;
		char condition2[] = {0x90, 0x90};
		char con3[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90}; // +436BBE
		char con4[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90}; // +436C24
		WriteProcessMemory(hProcess, (void*)block_addr, nops, 6, NULL);
		WriteProcessMemory(hProcess, (void*)dwarf_addr, &dwarfs, 1, NULL);
		WriteProcessMemory(hProcess, (void*)maxmood_addr, &maxmood, 1, NULL);
		WriteProcessMemory(hProcess, (void*)co_condition_addr, &co_condition,
			1, NULL);
		WriteProcessMemory(hProcess, (void*)condition1_addr, &condition1,
			1, NULL);
		WriteProcessMemory(hProcess, (void*)condition2_addr, &condition2,
			2, NULL);
		if (get_addr_by_name("main_condition") == 0x3BA4F3) {
			WriteProcessMemory(hProcess, (void*)con3_addr, con3, 6, NULL);
			WriteProcessMemory(hProcess, (void*)con4_addr, con4, 6, NULL);
		}
	}
	else {
		char dwarfs = 20;
		char maxmood = 0;
		char co_condition = 0x85;
		char condition1 = 0;
		char condition2[] = {0x74, 0x0A};
		WriteProcessMemory(hProcess, (void*)block_addr, old, 6, NULL);
		WriteProcessMemory(hProcess, (void*)dwarf_addr, &dwarfs, 1, NULL);
		WriteProcessMemory(hProcess, (void*)maxmood_addr, &maxmood, 1, NULL);
		WriteProcessMemory(hProcess, (void*)co_condition_addr, &co_condition,
			1, NULL);
		WriteProcessMemory(hProcess, (void*)condition1_addr, &condition1,
			1, NULL);
		WriteProcessMemory(hProcess, (void*)condition2_addr, &condition2,
			2, NULL);
		if (get_addr_by_name("main_condition") == 0x3BA4F3) {
			WriteProcessMemory(hProcess, (void*)con3_addr, con3_old, 6, NULL);
			WriteProcessMemory(hProcess, (void*)con4_addr, con4_old, 6, NULL);
		}
	}
	//
	PauseState = 0;
	WriteProcessMemory(hProcess, (void*)pause, &PauseState, 1, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button33Click(TObject *Sender) {
	__int64 counter_addr = (__int64)StartAddr + get_addr_by_name("counter");
	__int64 byte_addr = (__int64)StartAddr + get_addr_by_name("main_condition");
	int a = 1;
	if (CheckBox24->Checked)
		a = 0;
	char byte = 0x84;
	WriteProcessMemory(hProcess, (void*)counter_addr, &a, 4, NULL);
	WriteProcessMemory(hProcess, (void*)byte_addr, &byte, 1, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Slaught_creature(TObject *Sender) {
	__int64 num_addr = StartAddr + get_addr_by_name("selected_unit");
	__int64 offset_addr = StartAddr + get_addr_by_name("active_creature_vect");
	int num;
	ReadProcessMemory(hProcess, (void*)num_addr, &num, 4, NULL);
	int offset = num * 8;
	ReadProcessMemory(hProcess, (void*)offset_addr, &offset_addr, 8, NULL);
	offset_addr += offset;
	ReadProcessMemory(hProcess, (void*)offset_addr, &offset_addr, 8, NULL);

	char flags2;
	ReadProcessMemory(hProcess, (void*)(offset_addr + 0x10C+2), &flags2,
		1, NULL);
	char buf[] = {0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0, k = 7; i < 8; i++, k--) {
		buf[k] = (flags2 & (int)pow((double)2, i)) ? 49 : 48;
		flags2 << 1;
	}
	buf[6] = (int)CheckBox25->Checked + 48;
	flags2 = strtol(buf, NULL, 2);
	WriteProcessMemory(hProcess, (void*)(offset_addr + 0x10C+2), &flags2,
		1, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender) {
	try {
		if (OpenDialog1->Execute()) {
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
	}
	catch (Exception &exception) {
		fclose(ini_file);
		Application->ShowException(&exception);
		Application->~TApplication();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Cancel_job(TObject *Sender) {
	__int64 num_addr = StartAddr + get_addr_by_name("selected_unit");
	__int64 offset_addr = StartAddr + get_addr_by_name("active_creature_vect");
	int num;
	// ïîëó÷àåì íîìåð äâàðôà â âåêòîðå
	ReadProcessMemory(hProcess, (void*)num_addr, &num, 4, NULL);
	// îïðåäåëÿåì ñäâèã îò åãî íà÷àëà
	ReadProcessMemory(hProcess, (void*)offset_addr, &offset_addr, 8, NULL);
	offset_addr += num * 8;
	ReadProcessMemory(hProcess, (void*)offset_addr, &offset_addr, 8, NULL);

	// job
	// 0x364(job) 0x30(current, set 0 to cancel)    0x8(job_type)
	__int64 job = offset_addr + 0x4B0;
	// ReadProcessMemory(hProcess,(void*)job,&job,4,NULL);
	__int64 current_job = 0;
	WriteProcessMemory(hProcess, (void*)job, &current_job, 8, NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Loadini1Click(TObject *Sender) {
	try {
		if (OpenDialog1->Execute()) {
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
	}
	catch (Exception &exception) {
		fclose(ini_file);
		Application->ShowException(&exception);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button35Click(TObject *Sender) { // heal unit
	int num_addr = StartAddr + get_addr_by_name("selected_unit");
	int offset_addr = StartAddr + get_addr_by_name("active_creature_vect");
	int num;
	ReadProcessMemory(hProcess, (void*)num_addr, &num, 4, NULL);
	ReadProcessMemory(hProcess, (void*)offset_addr, &offset_addr, 4, NULL);
	offset_addr += num * 4;
	ReadProcessMemory(hProcess, (void*)offset_addr, &offset_addr, 4, NULL);

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button36Click(TObject *Sender) {
	TForm *Dialog = get_dwarfedit_pointer();
	change_mode(EMBARK);
	Dialog->Visible = Dialog->Visible ? false : true;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender) {
	TForm *Form = get_dwarfedit_pointer();
	__int64 num_addr = StartAddr + get_addr_by_name("selected_unit");
	int num;
	ReadProcessMemory(hProcess, (void*)num_addr, &num, 4, NULL);
	// offset_addr+=num*4;
	change_mode(SINGLE, num);
	Form->Visible = Form->Visible ? false : true;
}
// ---------------------------------------------------------------------------
