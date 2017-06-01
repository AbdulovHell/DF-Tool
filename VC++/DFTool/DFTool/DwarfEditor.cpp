#define _CRT_SECURE_NO_WARNINGS
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
	NameEd->Enabled = true;
	NameEd->Visible = true;
}

void DFTool::DwarfEditor::ChangeMode(int _mode, int dwarfnum)
{
	EditMode = _mode;
	DwarfListUpdateBtn->Enabled = false;
	DwarfList->Items->Clear();
	for (int i = 0; i < dwarfnum + 1; i++) {
		DwarfList->Items->Add(" ");
	}
	DwarfList->SelectedIndex = dwarfnum;
	LoadDwarfInForm();
	DwarfList->Enabled = false;
	NameEd->Enabled = false;
	NameEd->Visible = false;
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
	//получение индексов имен, первой части
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x40;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameind, 4, NULL);
	NameSecondP1Ind->SelectedIndex = l1nameind;
	//второй
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x44;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l2nameind, 4, NULL);
	NameSecondP2Ind->SelectedIndex = l2nameind;

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

int DFTool::DwarfEditor::RangeRand(int range_min, int range_max)
{
	double u = ((double)rand() / (RAND_MAX + 1)) * (range_max - range_min) +
		range_min;
	return u;
}

System::Void DFTool::DwarfEditor::DwarfListUpdateBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int dwarfs = mainform::GetDwarfCount();
	DwarfList->Items->Clear();
	HANDLE hDF = mainform::GetDFHandle();
	for (int i = 0; i < dwarfs; i++)
	{
		char buf[120];
		strcpy(buf, "");
		if (dwarfs < 10) sprintf(buf, "%d. ", i + 1);
		else if (dwarfs < 100) sprintf(buf, "%2d. ", i + 1);
		else if (dwarfs < 1000) sprintf(buf, "%3d. ", i + 1);

		mainform::GetFullName(buf, i, mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect"));

		strcat(buf, " id:");

		uint64_t addr = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect");
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		addr = addr + i * 8;
		ReadProcessMemory(hDF, (void*)addr, &addr, 8, NULL);
		addr += 0x128;
		ReadProcessMemory(hDF, (void*)addr, &addr, 4, NULL);
		char temp[20];
		sprintf(temp, "%d", addr);
		strcat(buf, temp);
		DwarfList->Items->Add(gcnew String(buf));
	}
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

	for (int i = 0; i < 0x3000; i++) {
		ReadProcessMemory(hProcess, (void*)ColNameOffset, &NameAddr, 8, NULL);
		ReadProcessMemory(hProcess, (void*)NameAddr, &NameAddr, 8, NULL);
		NameAddr += 0x50;
		ReadProcessMemory(hProcess, (void*)NameAddr, &NameAddr, 8, NULL);
		NameAddr += 8 * i;
		ReadProcessMemory(hProcess, (void*)NameAddr, &NameAddr, 8, NULL);
		ReadProcessMemory(hProcess, (void*)NameAddr, Name, 10, NULL);

		NameSecondP1Ind->Items->Add(gcnew String(Name));
		NameSecondP2Ind->Items->Add(gcnew String(Name));
	}
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

	UCHAR len = strlen(firstname);
	UCHAR mode = 0x0F;
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
	int l1nameind = NameSecondP1Ind->SelectedIndex, l2nameind = NameSecondP2Ind->SelectedIndex;
	//получение индексов имен, первой части
	ReadProcessMemory(hProcess, (void*)NameOffset, &l1nameaddr, 8, NULL);
	l1nameaddr += SelectedDwarf * 8;
	ReadProcessMemory(hProcess, (void*)l1nameaddr, &l1nameaddr, 8, NULL);
	l1nameaddr += 0x40;
	WriteProcessMemory(hProcess, (void*)l1nameaddr, &l1nameind, 4, NULL);
	//второй
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
		orientation += (o_Boxes[i]->Checked) ? 1 * Math::Pow(2, i) : 0;
	orientation <<= 1;
	WriteProcessMemory(hProcess, (void*)(stat_addr + 0x88), &orientation, 4, NULL);

	//attributes
	uint64_t AttrOffset = (EditMode == EMBARK) ? mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("creature_vect") : mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
	//dwarf offset1 soul offset2
	//0     470                     +1C  phys
	//0     80C     0    9C         +1C  soul
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
