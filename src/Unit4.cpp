// ---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "mirror.h"
// ---------------------------------------------------------------------
#pragma resource "*.dfm"
TOKBottomDlg2 *OKBottomDlg2;

TForm *get_invedit_pointer(void) {
	return OKBottomDlg2;
}

class Items {
public:
	int weight;
	int stack_size;
	int wear_stat;
	int wear_timer;
	int mat_type;
	int mat_index;
	short race;
	short quality;
	char name[28];
	DWORD type_st;
};

class EquipItem {
public:
	int ItemAddr;
	short mode;
	short body_part_id;
	Items *Item;
	int i;
};

EquipItem *HeadItems[500];
EquipItem *LBItems[500];
EquipItem *UBItems[500];
EquipItem *LHItems[500];
EquipItem *RHItems[500];
EquipItem *LFItems[500];
EquipItem *RFItems[500];
EquipItem *OtherItems[5000];
int ItemsCount[200];
TListBox *Boxes[200];
EquipItem **Slots[200];
int LastEditedID;
int LastEditedBox;

void Load_Inventory(void) {
	// очистка
	for (int k = 0; k < 16; k++) {
		if (ItemsCount[k] > 0)
			for (; ItemsCount[k] > 0; ItemsCount[k]--)
				if (Slots[k][ItemsCount[k]])
					delete Slots[k][ItemsCount[k]];
		if (Boxes[k])
			Boxes[k]->Clear();
	}
	// получаем список вещей
	DWORD InventoryOffset = get_dfstartaddr() + get_addr_by_name
		("active_creature_vect");
	HANDLE hProcess = get_process();
	ReadProcessMemory(hProcess, (void*)InventoryOffset, &InventoryOffset,
		4, NULL);
	ReadProcessMemory(hProcess, (void*)InventoryOffset, &InventoryOffset,
		4, NULL);
	DWORD InventoryOffset_end = InventoryOffset + 0x31C;
	InventoryOffset += 0x318;
	ReadProcessMemory(hProcess, (void*)InventoryOffset, &InventoryOffset,
		4, NULL);
	ReadProcessMemory(hProcess, (void*)InventoryOffset_end,
		&InventoryOffset_end, 4, NULL);
	DWORD count = (InventoryOffset_end - InventoryOffset) / 4;
	// добавляем каждую в базу
	DWORD Item = NULL;
	for (DWORD i = 0; i < count; i++) {
		Item = InventoryOffset + i * 0x4;
		ReadProcessMemory(hProcess, (void*)Item, &Item, 4, NULL);
		if (Item) {
			unsigned short body_part_id;
			// 0x6 - body_part      //0x4 - mode   //0x0 - item
			ReadProcessMemory(hProcess, (void*)(Item + 0x6), &body_part_id,
				2, NULL);
			if (body_part_id < 16) {
				Slots[body_part_id][ItemsCount[body_part_id]] = new EquipItem;
				Slots[body_part_id][ItemsCount[body_part_id]]->i = i;
				Slots[body_part_id][ItemsCount[body_part_id]]->body_part_id =
					body_part_id;
				ReadProcessMemory(hProcess, (void*)(Item + 0x4),
					&Slots[body_part_id][ItemsCount[body_part_id]]->mode,
					2, NULL);
				ReadProcessMemory(hProcess, (void*)(Item + 0x0),
					&Slots[body_part_id][ItemsCount[body_part_id]]->ItemAddr,
					4, NULL);
				Slots[body_part_id][ItemsCount[body_part_id]]->Item = new Items;
				// 0x5C - weight         0x64 - stack_size       0x78 - wear_stat        0x7C - wear_time
				// 0x88 - mat_type       0x8C - mat_index        0x90 - race     0x92 - quality
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x0),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->type_st, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x5c),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->weight, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x64),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->stack_size, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x78),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->wear_stat, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x7c),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->wear_timer, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x88),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->mat_type, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x8c),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->mat_index, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x90),
					&Slots[body_part_id][ItemsCount[body_part_id]]->Item->race,
					2, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x92),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->quality, 2, NULL);
				int subtype;
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0xb0), &subtype, 4, NULL);
				ReadProcessMemory(hProcess, (void*)(subtype + 0x44),
					Slots[body_part_id][ItemsCount[body_part_id]]->Item->name,
					28, NULL);
				if (Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->type_st == get_dfstartaddr() + get_addr_by_name
					("bckpck")) {
					ZeroMemory(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, 28);
					strcpy(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, "backpack");
					Boxes[body_part_id]->Items->Add
						(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name);
					ItemsCount[body_part_id]++;
				}
				else if (Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->type_st == get_dfstartaddr() + get_addr_by_name
					("flask")) {
					ZeroMemory(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, 28);
					strcpy(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, "flask/waterskin");
					Boxes[body_part_id]->Items->Add
						(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name);
					ItemsCount[body_part_id]++;
				}
				else if (Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->type_st == get_dfstartaddr() + get_addr_by_name
					("quiver")) {
					ZeroMemory(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, 28);
					strcpy(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, "quiver");
					Boxes[body_part_id]->Items->Add
						(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name);
					ItemsCount[body_part_id]++;
				}
				else if (subtype + 0x40 /* <0x1557E19E */) {
					Boxes[body_part_id]->Items->Add
						(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name);
					ItemsCount[body_part_id]++;
				}
			}
		}
		else
			break;
	}

}

void Save_Item(void) {
	HANDLE hProcess = get_process();

	Slots[LastEditedBox][LastEditedID]->Item->weight =
		StrToInt(OKBottomDlg2->Edit1->Text);
	Slots[LastEditedBox][LastEditedID]->Item->stack_size =
		StrToInt(OKBottomDlg2->Edit2->Text);
	Slots[LastEditedBox][LastEditedID]->Item->wear_stat =
		OKBottomDlg2->ComboBox2->ItemIndex;
	Slots[LastEditedBox][LastEditedID]->Item->wear_timer =
		StrToInt(OKBottomDlg2->Edit4->Text);
	Slots[LastEditedBox][LastEditedID]->Item->mat_type =
		StrToInt(OKBottomDlg2->Edit5->Text);
	Slots[LastEditedBox][LastEditedID]->Item->mat_index =
		StrToInt(OKBottomDlg2->Edit6->Text);
	Slots[LastEditedBox][LastEditedID]->Item->race =
		StrToInt(OKBottomDlg2->Edit7->Text);
	Slots[LastEditedBox][LastEditedID]->Item->quality =
		OKBottomDlg2->ComboBox1->ItemIndex;

	WriteProcessMemory(hProcess,
		(void*)(Slots[LastEditedBox][LastEditedID]->ItemAddr + 0x5c),
		&Slots[LastEditedBox][LastEditedID]->Item->weight, 4, NULL);
	WriteProcessMemory(hProcess,
		(void*)(Slots[LastEditedBox][LastEditedID]->ItemAddr + 0x64),
		&Slots[LastEditedBox][LastEditedID]->Item->stack_size, 4, NULL);
	WriteProcessMemory(hProcess,
		(void*)(Slots[LastEditedBox][LastEditedID]->ItemAddr + 0x78),
		&Slots[LastEditedBox][LastEditedID]->Item->wear_stat, 4, NULL);
	WriteProcessMemory(hProcess,
		(void*)(Slots[LastEditedBox][LastEditedID]->ItemAddr + 0x7c),
		&Slots[LastEditedBox][LastEditedID]->Item->wear_timer, 4, NULL);
	WriteProcessMemory(hProcess,
		(void*)(Slots[LastEditedBox][LastEditedID]->ItemAddr + 0x88),
		&Slots[LastEditedBox][LastEditedID]->Item->mat_type, 4, NULL);
	WriteProcessMemory(hProcess,
		(void*)(Slots[LastEditedBox][LastEditedID]->ItemAddr + 0x8c),
		&Slots[LastEditedBox][LastEditedID]->Item->mat_index, 4, NULL);
	WriteProcessMemory(hProcess,
		(void*)(Slots[LastEditedBox][LastEditedID]->ItemAddr + 0x90),
		&Slots[LastEditedBox][LastEditedID]->Item->race, 2, NULL);
	WriteProcessMemory(hProcess,
		(void*)(Slots[LastEditedBox][LastEditedID]->ItemAddr + 0x92),
		&Slots[LastEditedBox][LastEditedID]->Item->quality, 2, NULL);
}

int Find_Item(int Fid) {
	DWORD item_vectors[13];
	item_vectors[0] = get_addr_by_name("weapons_vector");
	item_vectors[1] = get_addr_by_name("shields_vector");
	item_vectors[2] = get_addr_by_name("quivers_vector");
	item_vectors[3] = get_addr_by_name("crutches_vector");
	item_vectors[4] = get_addr_by_name("backpacks_vector");
	item_vectors[5] = get_addr_by_name("ammo_vector");
	item_vectors[6] = get_addr_by_name("flasks_vector");
	item_vectors[7] = get_addr_by_name("pants_vector");
	item_vectors[8] = get_addr_by_name("armor_vector");
	item_vectors[9] = get_addr_by_name("shoes_vector");
	item_vectors[10] = get_addr_by_name("helms_vector");
	item_vectors[11] = get_addr_by_name("gloves_vector");
	item_vectors[12] = get_addr_by_name("artifacts_vector");

	int last_type;
	HANDLE hProcess = get_process();

	for (int i = 0; i < 13; i++) {
		DWORD offset = get_dfstartaddr() + item_vectors[i];
		DWORD first_item = get_dfstartaddr() + item_vectors[i];
		DWORD last_item = get_dfstartaddr() + item_vectors[i]+0x4;
		ReadProcessMemory(hProcess, (void*)first_item, &first_item, 4, NULL);
		ReadProcessMemory(hProcess, (void*)last_item, &last_item, 4, NULL);
		DWORD count = (last_item - first_item) / 4;

		for (int k = 0;	k<count ; k++) {
			int temp;
			ReadProcessMemory(hProcess, (void*)offset, &temp, 4, NULL);
			temp += k * 4;
			ReadProcessMemory(hProcess, (void*)temp, &temp, 4, NULL);

			int type;
			ReadProcessMemory(hProcess, (void*)temp, &type, 4, NULL);
			/* if(k==0) last_type=type;
			 else */ if (last_type == type)
				break;
			int id;
			ReadProcessMemory(hProcess, (void*)(temp + 0x18), &id, 4, NULL);

			if (id == Fid)
				return temp;
		}
	}
	return -1;
}

// ---------------------------------------------------------------------
__fastcall TOKBottomDlg2::TOKBottomDlg2(TComponent* AOwner) : TForm(AOwner) {
	//
	Boxes[0] = UpBodySlots;
	Boxes[1] = LowBodySlots;

	Boxes[3] = HeadSlots;

	Boxes[8] = RightHandSlots;
	Boxes[9] = LeftHandSlots;

	Boxes[14] = RightFootSlots;
	Boxes[15] = LeftFootSlots;

	Boxes[5] = OtherSlots;
	//
	Slots[0] = UBItems;
	Slots[1] = LBItems;

	Slots[3] = HeadItems;

	Slots[8] = RHItems;
	Slots[9] = LHItems;

	Slots[14] = RFItems;
	Slots[15] = LFItems;

	Slots[5] = OtherItems;
}

// ---------------------------------------------------------------------
void __fastcall TOKBottomDlg2::Button1Click(TObject *Sender) {
	Load_Inventory();
}
// ---------------------------------------------------------------------------

void __fastcall TOKBottomDlg2::Button2Click(TObject *Sender) {
	Save_Item();
}
// ---------------------------------------------------------------------------

void __fastcall TOKBottomDlg2::HeadSlotsClick(TObject *Sender) {
	int BoxId = -1; // TODO
	if (Sender == Boxes[3])
		BoxId = 3;
	if (Sender == Boxes[0])
		BoxId = 0;
	if (Sender == Boxes[1])
		BoxId = 1;
	if (Sender == Boxes[8])
		BoxId = 8;
	if (Sender == Boxes[9])
		BoxId = 9;
	if (Sender == Boxes[14])
		BoxId = 14;
	if (Sender == Boxes[15])
		BoxId = 15;
	if (Sender == Boxes[5])
		BoxId = 5;

	int id = Boxes[BoxId]->ItemIndex;
	if (id == -1)
		return;
	Edit1->Text = IntToStr(Slots[BoxId][id]->Item->weight);
	Edit2->Text = IntToStr(Slots[BoxId][id]->Item->stack_size);
	ComboBox2->ItemIndex = Slots[BoxId][id]->Item->wear_stat;
	Edit4->Text = IntToStr(Slots[BoxId][id]->Item->wear_timer);
	Edit5->Text = IntToStr(Slots[BoxId][id]->Item->mat_type);
	Edit6->Text = IntToStr(Slots[BoxId][id]->Item->mat_index);
	Edit7->Text = IntToStr(Slots[BoxId][id]->Item->race);
	ComboBox1->ItemIndex = Slots[BoxId][id]->Item->quality;
	Label9->Caption = Slots[BoxId][id]->Item->name;

	LastEditedID = id;
	LastEditedBox = BoxId;
	HANDLE hProcess = get_process();
	if (Sender != Boxes[5])
		OtherSlots->Enabled = false;
	// 0x2C gen_refs
	if (Slots[BoxId][id]->Item->type_st == get_dfstartaddr() + get_addr_by_name
		("bckpck") || Slots[BoxId][id]->Item->type_st == get_dfstartaddr() +
		get_addr_by_name("flask") ||
		Slots[BoxId][id]->Item->type_st == get_dfstartaddr() + get_addr_by_name
		("quiver")) {

		// очистка
		if (ItemsCount[5] > 0)
			for (; ItemsCount[5] > 0; ItemsCount[5]--)
				if (Slots[5][ItemsCount[5]])
					delete Slots[5][ItemsCount[5]];
		if (Boxes[5])
			Boxes[5]->Clear();
		//
		OtherSlots->Enabled = true;
		DWORD first_item = Slots[BoxId][id]->ItemAddr + 0x2c;
		DWORD last_item = Slots[BoxId][id]->ItemAddr + 0x30;
		ReadProcessMemory(hProcess, (void*)first_item, &first_item, 4, NULL);
		ReadProcessMemory(hProcess, (void*)last_item, &last_item, 4, NULL);
		DWORD count = (last_item - first_item) / 4;
		for (DWORD k = 0; k < count; k++) {
			DWORD item = first_item + 4 * k;
			ReadProcessMemory(hProcess, (void*)item, &item, 4, NULL);
			DWORD item_id;
			ReadProcessMemory(hProcess, (void*)(item + 0x4), &item_id, 4, NULL);
			// if(!item_id) break;
			DWORD item_offset = Find_Item(item_id);
			if (!(item_offset == -1)) {
				DWORD body_part_id = 5;
				Slots[body_part_id][ItemsCount[body_part_id]] = new EquipItem;
				Slots[body_part_id][ItemsCount[body_part_id]]->i = k;
				Slots[body_part_id][ItemsCount[body_part_id]]->Item = new Items;
				Slots[body_part_id][ItemsCount[body_part_id]]->ItemAddr =
					item_offset;
				// 0x5C - weight         0x64 - stack_size       0x78 - wear_stat        0x7C - wear_time
				// 0x88 - mat_type       0x8C - mat_index        0x90 - race     0x92 - quality
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x0),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->type_st, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x5c),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->weight, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x64),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->stack_size, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x78),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->wear_stat, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x7c),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->wear_timer, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x88),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->mat_type, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x8c),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->mat_index, 4, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x90),
					&Slots[body_part_id][ItemsCount[body_part_id]]->Item->race,
					2, NULL);
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0x92),
					&Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->quality, 2, NULL);
				int subtype;
				ReadProcessMemory(hProcess,
					(void*)(Slots[body_part_id][ItemsCount[body_part_id]]
					->ItemAddr + 0xb0), &subtype, 4, NULL);
				ReadProcessMemory(hProcess, (void*)(subtype + 0x44),
					Slots[body_part_id][ItemsCount[body_part_id]]->Item->name,
					28, NULL);
				if (Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->type_st == get_dfstartaddr() + get_addr_by_name
					("bckpck")) {
					ZeroMemory(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, 28);
					strcpy(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, "backpack");
					Boxes[body_part_id]->Items->Add
						(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name);
					ItemsCount[body_part_id]++;
				}
				else if (Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->type_st == get_dfstartaddr() + get_addr_by_name
					("flask")) {
					ZeroMemory(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, 28);
					strcpy(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, "flask/waterskin");
					Boxes[body_part_id]->Items->Add
						(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name);
					ItemsCount[body_part_id]++;
				}
				else if (Slots[body_part_id][ItemsCount[body_part_id]]
					->Item->type_st == get_dfstartaddr() + get_addr_by_name
					("quiver")) {
					ZeroMemory(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, 28);
					strcpy(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name, "quiver");
					Boxes[body_part_id]->Items->Add
						(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name);
					ItemsCount[body_part_id]++;
				}
				else if (1) {
					Boxes[body_part_id]->Items->Add
						(Slots[body_part_id][ItemsCount[body_part_id]]
						->Item->name);
					ItemsCount[body_part_id]++;
				}
			}
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TOKBottomDlg2::SpeedButton1Click(TObject *Sender) {
	DWORD Offset = get_dfstartaddr() + get_addr_by_name("active_creature_vect");
	HANDLE hProcess = get_process();
	int avd_race;
	ReadProcessMemory(hProcess, (void*)Offset, &Offset, 4, NULL);
	ReadProcessMemory(hProcess, (void*)Offset, &Offset, 4, NULL);
	Offset += 0x8C;
	ReadProcessMemory(hProcess, (void*)Offset, &avd_race, 4, NULL);
	// TODO
	Edit7->Text = avd_race;
}
// ---------------------------------------------------------------------------
