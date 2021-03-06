#include <Windows.h>
#include <Psapi.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "mainform.h"
#include "DwarfEditor.h"

void DFTool::DwarfEditor::ChangeMode(int _mode)
{
	EditMode = _mode;
	DwarfListUpdateBtn->Enabled = true;
	DwarfList->Enabled = true;
	DwarfList->Items->Clear();
	SetAllSkill5Btn->Enabled = true;
	SetAllSkill5NBtn->Text = "Set L + 5 skills, only above \"Novice\"";
	CpySkillBtn->Enabled = true;
	ClrAllSkillsBtn->Text = "Clear all skills";
	SetDwarfSP->Enabled = true;
	DwarfSPEd->Enabled = true;
}

void DFTool::DwarfEditor::ChangeMode(int _mode, int dwarfnum)
{
	HANDLE hDF = mainform::GetDFHandle();
	EditMode = _mode;
	DwarfListUpdateBtn->Enabled = false;
	DwarfList->Items->Clear();
	for (int i = 0; i < dwarfnum + 1; i++) {
		if (i == dwarfnum) {
			char buf[120];
			strcpy_s(buf, 120, "");
			mainform::GetFullName(buf, 120, dwarfnum, mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect"));
			strcat_s(buf, 120, " id:");
			uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
			ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
			addr = addr + dwarfnum * 8;
			ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
			addr += 0x128;
			ReadProcessMemory(hDF, (void*)addr, &addr, 4, NULL);
			char temp[20];
			sprintf_s(temp, 20, "%d", (int)addr);
			strcat_s(buf, 120, temp);
			DwarfList->Items->Add(gcnew String(buf));
		}
		else
			DwarfList->Items->Add(" ");
	}
	DwarfList->SelectedIndexChanged -= gcnew System::EventHandler(this, &DwarfEditor::DwarfList_SelectedIndexChanged);
	DwarfList->SelectedIndex = dwarfnum;
	DwarfList->SelectedIndexChanged += gcnew System::EventHandler(this, &DwarfEditor::DwarfList_SelectedIndexChanged);
	DwarfList->Enabled = false;
	SetAllSkill5Btn->Enabled = false;
	SetAllSkill5NBtn->Text = "Set L + 5 skills, only above \"Dabbling\"";
	CpySkillBtn->Enabled = false;
	ClrAllSkillsBtn->Text = "Clear all prof skills";
	SetDwarfSP->Enabled = false;
	DwarfSPEd->Enabled = false;
}

void DFTool::DwarfEditor::LoadDwarfInForm()
{
	int SelectedDwarf = DwarfList->SelectedIndex;
	HANDLE hProcess = mainform::GetDFHandle();
	//read dwarf SP
	uint64_t tempAddr;
	uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("main");
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x8;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x120;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x2B4;
	int16_t count = 0;
	ReadProcessMemory(hProcess, (void*)addr, &count, 2, NULL);
	DwarfSPEd->Text = count.ToString();

	//name
	uint64_t NameOffset = (EditMode == EMBARK) ? mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect") : mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
	uint64_t ColNameOffset = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("names");
	//char buf[100];
	//strcpy(buf,"");

	uint64_t fnameaddr;
	char firstname[28];
	ReadProcessMemory(hProcess, (void*)NameOffset, &fnameaddr, 8, NULL);
	fnameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)fnameaddr, &fnameaddr, 8, NULL);

	UCHAR name_mode = 0;
	ReadProcessMemory(hProcess, (void*)(fnameaddr + 0x14), &name_mode, 1, NULL);
	if (name_mode == 0x1F) {
		ReadProcessMemory(hProcess, (void*)fnameaddr, &fnameaddr, 8, NULL);
		ReadProcessMemory(hProcess, (void*)fnameaddr, firstname, 28, NULL);
		firstname[0] = toupper(firstname[0]);
		//strcat(buf,firstname);
		NameFirstEd->Text = gcnew String(firstname);
	}
	else {
		ReadProcessMemory(hProcess, (void*)fnameaddr, firstname, 28, NULL);
		firstname[0] = toupper(firstname[0]);
		//strcat(buf,firstname);
		NameFirstEd->Text = gcnew String(firstname);
	}
	//
	//strcat(buf," ");
	//
	uint64_t l1nameaddr;
	uint32_t l1nameind, l2nameind;
	String^ temp = String::Empty;
	//��������� �������� ����, ������ �����
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x40;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameind, 4, NULL);
	//if (l1nameind >= 0) NameSecondP1Ind->SelectedIndex = l1nameind;
	ValNamesDict.TryGetValue(l1nameind, temp);
	NameSecondP1Ind->SelectedItem = temp;

	//������
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x44;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l2nameind, 4, NULL);
	//if (l2nameind >= 0) NameSecondP2Ind->SelectedIndex = l2nameind;
	ValNamesDict.TryGetValue(l2nameind, temp);
	NameSecondP2Ind->SelectedItem = temp;

	uint64_t stat_addr;
	ReadProcessMemory(hProcess, (void*)NameOffset, &stat_addr, 8, NULL);
	stat_addr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)stat_addr, &stat_addr, 8, NULL);
	stat_addr += 0xA70;    //current soul
						   //ReadProcessMemory(hProcess,(void*)stat_addr,&stat_addr,8,NULL); //soul 0
	ReadProcessMemory(hProcess, (void*)stat_addr, &stat_addr, 8, NULL);

	char gender = 2;
	ReadProcessMemory(hProcess, (void*)(stat_addr + 0x84), &gender, 1, NULL);
	if (gender == 0) {
		FemaleBtn->Checked = true;
	}
	else if (gender == 1) {
		MaleBtn->Checked = true;
	}
	int orientation = 0;
	ReadProcessMemory(hProcess, (void*)(stat_addr + 0x88), &orientation, 4, NULL);
	orientation >>= 1;
	for (int i = 0; i < 4; i++) {
		o_Boxes[i]->Checked = (orientation & 0x1) ? 1 : 0;
		orientation >>= 1;
	}
	//attributes
	uint64_t AttrOffset = (EditMode == EMBARK) ? mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect") : mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
	//dwarf offset1 soul offset2
	//0     470                     +1C  phys
	//0     80C     0    9C         +1C  soul
	//int tempAddr;
	ReadProcessMemory(hProcess, (void*)AttrOffset, &tempAddr, 8, NULL);
	tempAddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
	tempAddr += 0x5DC;     //body
	for (int j = 0; j < 6; j++) {
		int temp;
		ReadProcessMemory(hProcess, (void*)(tempAddr + j * 0x1C), &temp, 4, NULL);
		att_boxes[j]->Text = temp.ToString();
	}
	ReadProcessMemory(hProcess, (void*)AttrOffset, &tempAddr, 8, NULL);
	tempAddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
	tempAddr += 0xA70;    //current soul
						  //ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);
						  //tempAddr+=0x0;        //soul 0
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
	tempAddr += 0xAC;
	for (int j = 0; j < 13; j++) {
		int temp;
		ReadProcessMemory(hProcess, (void*)(tempAddr + j * 0x1C), &temp, 4, NULL);
		att_boxes[j + 6]->Text = temp.ToString();
	}
	//age

	ReadProcessMemory(hProcess, (void*)AttrOffset, &tempAddr, 8, NULL);
	tempAddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);

	int b_year, b_time, o_year, o_time, spouse, mother, father, lover;
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x36c), &b_year, 4, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x370), &b_time, 4, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x384), &o_year, 4, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x388), &o_time, 4, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x3a0), &spouse, 4, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x3a4), &mother, 4, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x3a8), &father, 4, NULL);
	ReadProcessMemory(hProcess, (void*)(tempAddr + 0x3c0), &lover, 4, NULL);

	MotherID->Text = mother.ToString();
	FatherID->Text = father.ToString();
	LoverID->Text = lover.ToString();
	SpouseID->Text = spouse.ToString();

	AgeBirthYear->Text = b_year.ToString();
	AgeDeathYear->Text = o_year.ToString();
	b_time++;
	o_time++;
	int b_month, d_month;
	b_month = ((int)((double)b_time / (28 * 1200)) + 1);
	d_month = ((int)((double)o_time / (28 * 1200)) + 1);
	AgeBirthMonth->Text = b_month.ToString();
	AgeDeathMonth->Text = d_month.ToString();

	AgeBirthDay->Text = ((int)((((double)b_time - (b_month - 1) * 28 * 1200)) / 1200) + 1).ToString();
	AgeDeathDay->Text = ((int)((((double)o_time - (d_month - 1) * 28 * 1200)) / 1200) + 1).ToString();
}

void DFTool::DwarfEditor::DwarfListUpdate()
{
	int dwarfs = mainform::GetDwarfCount();
	DwarfList->Items->Clear();
	HANDLE hDF = mainform::GetDFHandle();
	for (int i = 0; i < dwarfs; i++)
	{
		char buf[120];
		strcpy_s(buf, 120, "");
		if (dwarfs < 10) sprintf_s(buf, 120, "%d. ", i + 1);
		else if (dwarfs < 100) sprintf_s(buf, 120, "%2d. ", i + 1);
		else if (dwarfs < 1000) sprintf_s(buf, 120, "%3d. ", i + 1);

		mainform::GetFullName(buf, 120, i, mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect"));

		strcat_s(buf, 120, " id:");

		uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect");
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		addr = addr + i * 8;
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		addr += 0x128;
		ReadProcessMemory(hDF, (void*)addr, &addr, 4, NULL);
		char temp[20];
		sprintf_s(temp, 20, "%d", (int)addr);
		strcat_s(buf, 120, temp);
		DwarfList->Items->Add(gcnew String(buf));
	}
}

int DFTool::DwarfEditor::RangeRand(int range_min, int range_max)
{
	double u = ((double)rand() / (RAND_MAX + 1)) * (range_max - range_min) +
		range_min;
	return (int)u;
}

System::Void DFTool::DwarfEditor::DwarfListUpdateBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DwarfListUpdate();
}

System::Void DFTool::DwarfEditor::DwarfEditor_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	o_Boxes.Add(checkBox1);
	o_Boxes.Add(checkBox2);
	o_Boxes.Add(checkBox3);
	o_Boxes.Add(checkBox4);

	att_boxes.Add(textBox1);
	att_boxes.Add(textBox2);
	att_boxes.Add(textBox3);
	att_boxes.Add(textBox4);
	att_boxes.Add(textBox5);
	att_boxes.Add(textBox6);
	att_boxes.Add(textBox7);
	att_boxes.Add(textBox8);
	att_boxes.Add(textBox9);
	att_boxes.Add(textBox10);
	att_boxes.Add(textBox11);
	att_boxes.Add(textBox12);
	att_boxes.Add(textBox13);
	att_boxes.Add(textBox14);
	att_boxes.Add(textBox15);
	att_boxes.Add(textBox16);
	att_boxes.Add(textBox17);
	att_boxes.Add(textBox18);
	att_boxes.Add(textBox19);

	att_5k_buttons.Add(button1);
	att_5k_buttons.Add(button2);
	att_5k_buttons.Add(button3);
	att_5k_buttons.Add(button4);
	att_5k_buttons.Add(button5);
	att_5k_buttons.Add(button6);
	att_5k_buttons.Add(button7);
	att_5k_buttons.Add(button8);
	att_5k_buttons.Add(button9);
	att_5k_buttons.Add(button10);
	att_5k_buttons.Add(button11);
	att_5k_buttons.Add(button12);
	att_5k_buttons.Add(button13);
	att_5k_buttons.Add(button14);
	att_5k_buttons.Add(button15);
	att_5k_buttons.Add(button16);
	att_5k_buttons.Add(button17);
	att_5k_buttons.Add(button18);
	att_5k_buttons.Add(button19);
	//fill second name comboboxes
	uint64_t ColNameOffset = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("names");
	HANDLE hProcess = mainform::GetDFHandle();
	uint64_t NameAddr = NULL;
	char Name[10];

	ReadProcessMemory(hProcess, (void*)ColNameOffset, &ColNameOffset, 8, NULL);
	ReadProcessMemory(hProcess, (void*)ColNameOffset, &ColNameOffset, 8, NULL);
	ColNameOffset += 0x50;
	uint64_t ColNameOffsetEnd = ColNameOffset + 8;
	ReadProcessMemory(hProcess, (void*)ColNameOffset, &ColNameOffset, 8, NULL);
	ReadProcessMemory(hProcess, (void*)ColNameOffsetEnd, &ColNameOffsetEnd, 8, NULL);
	size_t vSize = (ColNameOffsetEnd - ColNameOffset) / 8;
	List<String^> NamesStrs;

	for (size_t i = 0; i < vSize; i++) {
		NameAddr = ColNameOffset + 8 * i;
		ReadProcessMemory(hProcess, (void*)NameAddr, &NameAddr, 8, NULL);
		ReadProcessMemory(hProcess, (void*)NameAddr, Name, 10, NULL);

		try {
			NamesValDict.Add(gcnew String(Name), i);
			ValNamesDict.Add(i, gcnew String(Name));
			NamesStrs.Add(gcnew String(Name));
		}
		catch (...) {

		}
	}

	NamesStrs.Sort();

	for (int i = 0; i < NamesStrs.Count; i++) {
		NameSecondP1Ind->Items->Add(NamesStrs[i]);
		NameSecondP2Ind->Items->Add(NamesStrs[i]);
	}
	//
	if (EditMode == EMBARK) {
		DwarfListUpdate();
		DwarfList->SelectedIndex = 0;
	}
	else
		LoadDwarfInForm();
}

System::Void DFTool::DwarfEditor::ApplyNameBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int SelectedDwarf = DwarfList->SelectedIndex;
	HANDLE hProcess = mainform::GetDFHandle();
	uint64_t NameOffset = (EditMode == EMBARK) ? mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect") : mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
	uint64_t ColNameOffset = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("names");

	uint64_t fnameaddr;
	char firstname[28];
	char *temp = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(NameFirstEd->Text);
	for (size_t i = 0; i < 28; i++)
		firstname[i] = temp[i];
	ReadProcessMemory(hProcess, (void*)NameOffset, &fnameaddr, 8, NULL);
	fnameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)fnameaddr, &fnameaddr, 8, NULL);

	size_t len = strlen(firstname);
	uint8_t mode = 0x0F;
	if (len < 16 && len>0) {
		WriteProcessMemory(hProcess, (void*)fnameaddr, firstname, strlen(firstname) + 1, NULL);
		WriteProcessMemory(hProcess, (void*)(fnameaddr + 0x10), &len, 1, NULL);
		WriteProcessMemory(hProcess, (void*)(fnameaddr + 0x18), &mode, 1, NULL);
	}
	else {
		uint64_t new_addr_name = (uint64_t)VirtualAllocEx(hProcess, NULL, strlen(firstname) + 2, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		WriteProcessMemory(hProcess, (void*)new_addr_name, firstname, strlen(firstname) + 1, NULL);
		WriteProcessMemory(hProcess, (void*)fnameaddr, &new_addr_name, 8, NULL);
		mode = 0x1F;
		WriteProcessMemory(hProcess, (void*)(fnameaddr + 0x10), &len, 1, NULL);
		WriteProcessMemory(hProcess, (void*)(fnameaddr + 0x18), &mode, 1, NULL);
	}
	uint64_t l1nameaddr = 0;
	int l1nameind = 0, l2nameind = 0;
	size_t tempInd = 0;
	NamesValDict.TryGetValue((String^)NameSecondP1Ind->SelectedItem, tempInd);
	l1nameind = tempInd;
	NamesValDict.TryGetValue((String^)NameSecondP2Ind->SelectedItem, tempInd);
	l2nameind = tempInd;
	//������� ����, ������ �����
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x40;
	WriteProcessMemory(hProcess, (void*)l1nameaddr, &l1nameind, 4, NULL);
	//������
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x44;
	WriteProcessMemory(hProcess, (void*)l1nameaddr, &l2nameind, 4, NULL);
}

System::Void DFTool::DwarfEditor::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	for (int i = 0; i < 19; i++)
		if (safe_cast<Button^>(sender) == att_5k_buttons[i])
			att_boxes[i]->Text = (5000).ToString();
}

System::Void DFTool::DwarfEditor::button20_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int SelectedDwarf = DwarfList->SelectedIndex;
	HANDLE hProcess = mainform::GetDFHandle();
	uint64_t tempAddr;
	uint64_t NameOffset = (EditMode == EMBARK) ? mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect") : mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
	//gender and orientation
	uint64_t stat_addr, addrasd;
	char gender = 2;
	gender = (FemaleBtn->Checked) ? 0 : 1;
	ReadProcessMemory(hProcess, (void*)NameOffset, &stat_addr, 8, NULL);
	stat_addr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)stat_addr, &stat_addr, 8, NULL);
	addrasd = stat_addr + 0x126;
	WriteProcessMemory(hProcess, (void*)addrasd, &gender, 1, NULL);

	stat_addr += 0xA70;
	ReadProcessMemory(hProcess, (void*)stat_addr, &stat_addr, 8, NULL);
	//ReadProcessMemory(hProcess, (void*)stat_addr, &stat_addr, 8, NULL);
	//0xFE
	WriteProcessMemory(hProcess, (void*)(stat_addr + 0x84), &gender, 1, NULL);

	int orientation = 0;
	for (int i = 0; i < 4; i++)
		orientation += (int)((o_Boxes[i]->Checked) ? 1 * Math::Pow(2, i) : 0);
	orientation <<= 1;
	WriteProcessMemory(hProcess, (void*)(stat_addr + 0x88), &orientation, 4, NULL);

	//attributes
	uint64_t AttrOffset = (EditMode == EMBARK) ? mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect") : mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
	//dwarf offset1 soul offset2
	//0     5DC                     +1C  phys
	//0     A70     0    9C         +1C  soul
	//int tempAddr;
	ReadProcessMemory(hProcess, (void*)AttrOffset, &tempAddr, 8, NULL);
	tempAddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
	tempAddr += 0x5DC;
	for (int j = 0; j < 6; j++) {
		int temp = int::Parse(att_boxes[j]->Text);
		WriteProcessMemory(hProcess, (void*)(tempAddr + j * 0x1C), &temp, 4, NULL);
	}
	ReadProcessMemory(hProcess, (void*)AttrOffset, &tempAddr, 8, NULL);
	tempAddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
	tempAddr += 0xA70;
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
	tempAddr += 0xAC;
	for (int j = 0; j < 13; j++) {
		int temp = int::Parse(att_boxes[j + 6]->Text);
		WriteProcessMemory(hProcess, (void*)(tempAddr + j * 0x1C), &temp, 4, NULL);
	}
	//age
	ReadProcessMemory(hProcess, (void*)AttrOffset, &tempAddr, 8, NULL);
	tempAddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);

	int b_year = int::Parse(AgeBirthYear->Text), b_time
		, o_year = int::Parse(AgeDeathYear->Text), o_time
		, spouse = int::Parse(SpouseID->Text), mother = int::Parse(MotherID->Text), father = int::Parse(FatherID->Text), lover = int::Parse(LoverID->Text);

	srand((unsigned)time(NULL));																				//wtf?
	b_time = (int::Parse(AgeBirthMonth->Text) - 1)*(28 * 1200) + (int::Parse(AgeBirthDay->Text) - 1) * 1200 + RangeRand(0, 1199);
	o_time = (int::Parse(AgeDeathMonth->Text) - 1)*(28 * 1200) + (int::Parse(AgeDeathDay->Text) - 1) * 1200 + RangeRand(0, 1199);

	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x36c), &b_year, 4, NULL);
	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x370), &b_time, 4, NULL);
	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x384), &o_year, 4, NULL);
	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x388), &o_time, 4, NULL);
	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x3a0), &spouse, 4, NULL);
	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x3a4), &mother, 4, NULL);
	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x3a8), &father, 4, NULL);
	WriteProcessMemory(hProcess, (void*)(tempAddr + 0x3c0), &lover, 4, NULL);
}

System::Void DFTool::DwarfEditor::DwarfList_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	LoadDwarfInForm();
}

System::Void DFTool::DwarfEditor::SetDwarfSP_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	HANDLE hProcess = mainform::GetDFHandle();
	short count = short::Parse(DwarfSPEd->Text);
	if ((count >= 0) && (count < 0xFFFF)) {
		uint64_t tempAddr;
		uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("main");
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x8;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x120;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		int SelectedDwarf = DwarfList->SelectedIndex;
		addr = tempAddr + SelectedDwarf * 8;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x2B4;
		WriteProcessMemory(hProcess, (void*)addr, &count, 2, NULL);
	}
}

System::Void DFTool::DwarfEditor::SetAllSkill5Btn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	HANDLE hProcess = mainform::GetDFHandle();
	int mas[135];
	for (int i = 0; i < 135; i++) mas[i] = 20;

	uint64_t tempAddr;
	uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("main");
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x8;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x120;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	int SelectedDwarf = DwarfList->SelectedIndex;
	addr = tempAddr + SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x7C;
	WriteProcessMemory(hProcess, (void*)addr, mas, 135 * sizeof(int), NULL);
}

System::Void DFTool::DwarfEditor::SetAllSkill5NBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	HANDLE hProcess = mainform::GetDFHandle();
	if (EditMode == EMBARK) {
		int mas[135];
		for (int i = 0; i < 135; i++) mas[i] = -1;

		uint64_t tempAddr;
		uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("main");
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x8;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x120;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		int SelectedDwarf = DwarfList->SelectedIndex;
		addr = tempAddr + SelectedDwarf * 8;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x7C;
		ReadProcessMemory(hProcess, (void*)addr, mas, 135 * sizeof(int), NULL);

		for (int i = 0; i < 135; i++) if (mas[i] > 0) mas[i] = 20;

		WriteProcessMemory(hProcess, (void*)addr, mas, 135 * sizeof(int), NULL);
	}
	else {
		//unit-status-current_soul-skills
		uint64_t tempAddr;
		uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		tempAddr += DwarfList->SelectedIndex * 8;
		ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
		tempAddr += 0xA70;
		ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
		uint64_t Start;
		ReadProcessMemory(hProcess, (void*)(tempAddr + 0x218), &Start, 8, NULL);
		uint64_t End;
		ReadProcessMemory(hProcess, (void*)(tempAddr + 0x220), &End, 8, NULL);
		size_t vect_size = (End - Start) / 8;
		for (size_t i = 0; i < vect_size; i++) {
			uint64_t temp;
			ReadProcessMemory(hProcess, (void*)(Start + i * 8), &temp, 8, NULL);
			uint16_t id;
			uint32_t rating;
			ReadProcessMemory(hProcess, (void*)temp, &id, 2, NULL);
			ReadProcessMemory(hProcess, (void*)(temp + 4), &rating, 4, NULL);
			if ((id >= 0 && id < 38) || (id == 47) || (id == 48) || (id == 49) || (id == 55) || (id > 57 && id < 71) || (id > 108 && id < 116) || (id == 117) || (id == 133) || (id == 134)) {
				rating = 20;
				WriteProcessMemory(hProcess, (void*)(temp + 4), &rating, 4, NULL);
			}
		}
	}
}

System::Void DFTool::DwarfEditor::CpySkillBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	HANDLE hProcess = mainform::GetDFHandle();
	int mas[135];
	for (int i = 0; i < 135; i++) mas[i] = -1;

	uint64_t tempAddr;
	uint64_t dwarfsOffset;
	uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("main");
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x8;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x120;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	dwarfsOffset = tempAddr;
	int SelectedDwarf = DwarfList->SelectedIndex;
	addr = tempAddr + SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
	addr = tempAddr + 0x7C;
	ReadProcessMemory(hProcess, (void*)addr, mas, 135 * sizeof(int), NULL);

	int dwarfs = mainform::GetDwarfCount();
	for (int i = 0; i < dwarfs; i++) {
		addr = dwarfsOffset + i * 8;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x7C;
		WriteProcessMemory(hProcess, (void*)addr, mas, 135 * sizeof(int), NULL);
	}
}

System::Void DFTool::DwarfEditor::ClrAllSkillsBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	HANDLE hProcess = mainform::GetDFHandle();
	if (EditMode == EMBARK) {
		int mas[135];
		for (int i = 0; i < 135; i++) mas[i] = 0;

		uint64_t tempAddr;
		uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("main");
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x8;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x120;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		int SelectedDwarf = DwarfList->SelectedIndex;
		addr = tempAddr + SelectedDwarf * 8;
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		addr = tempAddr + 0x7C;
		WriteProcessMemory(hProcess, (void*)addr, mas, 135 * sizeof(int), NULL);
	}
	else {
		//unit-status-current_soul-skills
		uint64_t tempAddr;
		uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
		ReadProcessMemory(hProcess, (void*)addr, &tempAddr, 8, NULL);
		tempAddr += DwarfList->SelectedIndex * 8;
		ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
		tempAddr += 0xA70;
		ReadProcessMemory(hProcess, (void*)tempAddr, &tempAddr, 8, NULL);
		uint64_t Start;
		ReadProcessMemory(hProcess, (void*)(tempAddr + 0x218), &Start, 8, NULL);
		uint64_t End;
		ReadProcessMemory(hProcess, (void*)(tempAddr + 0x220), &End, 8, NULL);
		size_t vect_size = (End - Start) / 8;
		for (size_t i = 0; i < vect_size; i++) {
			uint64_t temp;
			ReadProcessMemory(hProcess, (void*)(Start + i * 8), &temp, 8, NULL);
			uint16_t id;
			ReadProcessMemory(hProcess, (void*)temp, &id, 2, NULL);
			if ((id >= 0 && id < 38) || (id == 47) || (id == 48) || (id == 49) || (id == 55) || (id > 57 && id < 71) || (id > 108 && id < 116) || (id == 117) || (id == 133) || (id == 134)) {
				for (size_t j = i; j < vect_size - 1; j++) {
					uint64_t tmp;
					ReadProcessMemory(hProcess, (void*)(Start + (j + 1) * 8), &tmp, 8, NULL);
					WriteProcessMemory(hProcess, (void*)(Start + j * 8), &tmp, 8, NULL);
				}
				vect_size--;
				i--;
				End -= 8;
				WriteProcessMemory(hProcess, (void*)(tempAddr + 0x220), &End, 8, NULL);
			}
		}
	}
}
