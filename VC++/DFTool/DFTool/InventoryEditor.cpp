#include <Windows.h>
#include <string.h>
#include "InventoryEditor.h"
#include "mainform.h"

using namespace System;

DFTool::InventoryEditor::InventoryEditor(void)
{
	InitializeComponent();

	SortedItems = gcnew List<List<Item^>^>;
	for (int i = 0; i < 22; i++)
		SortedItems->Add(gcnew List<Item^>);
	UnsortedItems = gcnew List<Item^>;

	hDF = mainform::GetDFHandle();
}

DFTool::InventoryEditor::InventoryEditor(uint32_t _CreatureID)
{
	InitializeComponent();

	SortedItems = gcnew List<List<Item^>^>;
	for (int i = 0; i < 22; i++)
		SortedItems->Add(gcnew List<Item^>);
	UnsortedItems = gcnew List<Item^>;

	CreatureID = _CreatureID;
	hDF = mainform::GetDFHandle();
}

DFTool::InventoryEditor::~InventoryEditor()
{
	if (components)
	{
		delete components;
	}
}

void DFTool::InventoryEditor::LoadInventory()
{
	uint64_t InventoryOffset = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");

	ReadProcessMemory(hDF, (void*)InventoryOffset, &InventoryOffset, 8, NULL);
	ReadProcessMemory(hDF, (void*)(InventoryOffset + CreatureID * 8), &InventoryOffset, 8, NULL);
	uint64_t InventoryOffset_end = InventoryOffset + 0x3F8;
	InventoryOffset += 0x3F0;
	ReadProcessMemory(hDF, (void*)InventoryOffset, &InventoryOffset, 8, NULL);
	ReadProcessMemory(hDF, (void*)InventoryOffset_end, &InventoryOffset_end, 8, NULL);
	uint32_t count = (uint32_t)((InventoryOffset_end - InventoryOffset) / 8);
	uint64_t ItemAddr = NULL;
	for (uint32_t i = 0; i < count; i++) {
		ItemAddr = InventoryOffset + i * 8;
		ReadProcessMemory(hDF, (void*)ItemAddr, &ItemAddr, 8, NULL);
		UnsortedItems->Add(gcnew Item(ItemAddr, i));
	}
	uint16_t id;
	for (int i = 0; i < UnsortedItems->Count; i++) {
		id = UnsortedItems[i]->body_part_id;
		if (id < 0 || id>20)
			SortedItems[21]->Add(gcnew Item(UnsortedItems[i]));
		else
			SortedItems[id]->Add(gcnew Item(UnsortedItems[i]));
		UnsortedItems->RemoveAt(i);
		i--;
		/*
		case 0:	//Upper Body
		case 1: //Lower Body
		case 2: //Neck
		case 3: //Head
		case 4: //Right upper arm
		case 5: //Left upper arm
		case 6:	//Right lower arm
		case 7:	//Left lower arm
		case 8:	//Right hand
		case 9:	//Left hand
		case 10:	//Right upper leg
		case 11:	//Left upper leg
		case 12:	//Right lower leg
		case 13:	//Left lower leg
		case 14:	//Right foor
		case 15:	//Left foot
		case 16:	//Right eye
		case 17:	//Left eye
		case 18:	//Right ear
		case 19:	//Left ear
		case 20:	//Nose
		default:	//R/L lung,Heart,Guts,Liver,Stomach,Pancreas ...
		*/
	}

}

void DFTool::InventoryEditor::LoadItem(Item ^ item, bool wCont)
{
	SelectedItem = item;
	ItemNameLbl->Text = item->sName;
	WeightEdit->Text = item->weight.ToString();
	StackSizeEdit->Text = item->stack_size.ToString();
	WearTimerEdit->Text = item->wear_timer.ToString();
	MaterialTypeEdit->Text = item->mat_type.ToString();
	MaterialIndexEdit->Text = item->mat_index.ToString();
	RaceEdit->Text = item->race.ToString();

	if (item->quality >= 0 && item->quality <= 6)
		QualityList->SelectedIndex = item->quality;
	else
		QualityList->SelectedIndex = 0;

	if (item->wear_stat >= 0 && item->wear_stat <= 3)
		WearStatusList->SelectedIndex = item->wear_stat;
	else
		WearStatusList->SelectedIndex = 0;

	ItemsInContBox->Visible = false;
	label1->Visible = false;

	if (item->isContainer && wCont) {
		ItemsInContBox->Items->Clear();
		ItemsInContBox->Visible = true;
		label1->Visible = true;
		if (InContainerItems == nullptr) {
			InContainerItems = gcnew List<Item^>;
		}
		else {
			for (int i = 0; i < InContainerItems->Count; i++) {
				delete InContainerItems[i];
			}
			delete InContainerItems;

			InContainerItems = gcnew List<Item^>;
		}
		uint64_t first_item = item->ItemAddr + 0x38;
		uint64_t last_item = item->ItemAddr + 0x40;
		ReadProcessMemory(hDF, (void*)first_item, &first_item, 8, NULL);
		ReadProcessMemory(hDF, (void*)last_item, &last_item, 8, NULL);
		uint32_t count = (uint32_t)((last_item - first_item) / 8);
		for (uint32_t i = 0; i < count; i++) {		//D50A38+df
			uint64_t itemAddr = first_item + 8 * i;
			ReadProcessMemory(hDF, (void*)itemAddr, &itemAddr, 8, NULL);

			uint64_t def;
			ReadProcessMemory(hDF, (void*)(itemAddr), &def, 8, NULL);
			if (def != 0xD50A38 + mainform::GetDFStartAddr())
				continue;

			uint32_t id;
			ReadProcessMemory(hDF, (void*)(itemAddr + 0x8), &id, 4, NULL);
			itemAddr = FindItem(id);
			if (itemAddr) {
				InContainerItems->Add(gcnew Item(itemAddr));
			}
		}
		for (int i = 0; i < InContainerItems->Count; i++) {
			ItemsInContBox->Items->Add(InContainerItems[i]->sName);
		}
	}
}

uint64_t DFTool::InventoryEditor::FindItem(uint32_t fId)
{
	List<uint64_t> item_vectors;
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("weapons_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("shields_vector"));
	/*item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("ammo_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("pants_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("armor_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("shoes_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("helms_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("gloves_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("food_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("tools_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("instruments_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("toys_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("trapcomps_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("siegeammo_vector"));
	item_vectors.Add(mainform::GetMemLayout()->GetAddrByName("other_vector"));*/

	for (int i = 0; i < item_vectors.Count; i++) {
		uint64_t offset_sta = mainform::GetDFStartAddr() + item_vectors[i];
		uint64_t offset_end = mainform::GetDFStartAddr() + item_vectors[i] + 8;
		ReadProcessMemory(hDF, (void*)offset_sta, &offset_sta, 8, NULL);
		ReadProcessMemory(hDF, (void*)offset_end, &offset_end, 8, NULL);
		uint32_t count = (uint32_t)((offset_end - offset_sta) / 8);
		for (uint32_t k = 0; k < count; k++) {
			uint64_t temp;
			//ReadProcessMemory(hDF, (void*)offset_sta, &temp, 8, NULL);
			ReadProcessMemory(hDF, (void*)(offset_sta + k * 8), &temp, 8, NULL);

			uint32_t id;
			ReadProcessMemory(hDF, (void*)(temp + 0x1C), &id, 4, NULL);
			if (id == fId)
				return temp;
		}
	}
	return 0;
}

System::Void DFTool::InventoryEditor::InventoryEditor_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	LoadInventory();
}

System::Void DFTool::InventoryEditor::BodyPartList_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	int index = BodyPartList->SelectedIndex;
	ItemsOnPartBox->Items->Clear();
	SelectedBodyPart = SortedItems[index];
	for (int i = 0; i < SelectedBodyPart->Count; i++)
		ItemsOnPartBox->Items->Add(SelectedBodyPart[i]->GetName());
}

System::Void DFTool::InventoryEditor::ItemsOnPartBox_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	int index = ItemsOnPartBox->SelectedIndex;
	if (index != 0xffffffff)
		LoadItem(SelectedBodyPart[index], true);
}

System::Void DFTool::InventoryEditor::SaveItemBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int temp_int = 0;
	//weight
	if (int::TryParse(WeightEdit->Text, temp_int)) {
		SelectedItem->weight = temp_int;
	}
	else {
		SelectedItem->weight = 1;
		WeightEdit->Text = "1";
	}
	//stack size
	if (int::TryParse(StackSizeEdit->Text, temp_int)) {
		SelectedItem->stack_size = temp_int;
	}
	else {
		SelectedItem->stack_size = 1;
		StackSizeEdit->Text = "1";
	}
	//wear time
	if (int::TryParse(WearTimerEdit->Text, temp_int)) {
		SelectedItem->wear_timer = temp_int;
	}
	else {
		SelectedItem->wear_timer = 0;
		WearTimerEdit->Text = "0";
	}
	//material type
	short temp_short = 0;
	if (short::TryParse(MaterialTypeEdit->Text, temp_short)) {
		SelectedItem->mat_type = temp_short;
	}
	else {
		SelectedItem->mat_type = 0;
		MaterialTypeEdit->Text = "0";
	}
	//wear time
	if (int::TryParse(WearTimerEdit->Text, temp_int)) {
		SelectedItem->wear_timer = temp_int;
	}
	else {
		SelectedItem->wear_timer = 0;
		WearTimerEdit->Text = "0";
	}
	//material index
	if (int::TryParse(MaterialIndexEdit->Text, temp_int)) {
		SelectedItem->mat_index = temp_int;
	}
	else {
		SelectedItem->mat_index = 0;
		MaterialIndexEdit->Text = "0";
	}
	//race
	if (short::TryParse(RaceEdit->Text, temp_short)) {
		SelectedItem->race = temp_short;
	}
	else {
		SelectedItem->race = 0;
		RaceEdit->Text = "0";
	}

	SelectedItem->wear_stat = WearStatusList->SelectedIndex;
	SelectedItem->quality = QualityList->SelectedIndex;
	SelectedItem->Save();
}

System::Void DFTool::InventoryEditor::RaceEdit_MouseDoubleClick(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	uint64_t offset = mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("active_creature_vect");
	int race;
	ReadProcessMemory(hDF, (void*)offset, &offset, 8, NULL);
	ReadProcessMemory(hDF, (void*)(offset + CreatureID * 8), &offset, 8, NULL);
	ReadProcessMemory(hDF, (void*)(offset + 0x9C), &race, 4, NULL);
	RaceEdit->Text = race.ToString();
}

System::Void DFTool::InventoryEditor::ItemsInContBox_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	int index = ItemsInContBox->SelectedIndex;
	if (index != 0xffffffff)
		LoadItem(InContainerItems[index], false);
}

System::Void DFTool::InventoryEditor::ReloadInvBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	for (int i = 0; i < SortedItems->Count; i++)
		SortedItems[i]->Clear();
	UnsortedItems->Clear();

	LoadInventory();
}

DFTool::InventoryEditor::Item::Item()
{
	name = new char[32];
}

DFTool::InventoryEditor::Item::Item(uint64_t ItemOffset, uint32_t index)
{
	name = new char[32];
	index_in_inventory = index;

	uint64_t temp8b;
	uint32_t temp4b;
	uint16_t temp2b;

	ReadProcessMemory(hDF, (void*)ItemOffset, &temp8b, 8, NULL);	ItemAddr = temp8b;
	ReadProcessMemory(hDF, (void*)(ItemOffset + 0x8), &temp2b, 2, NULL);	mode = temp2b;
	ReadProcessMemory(hDF, (void*)(ItemOffset + 0xA), &temp2b, 2, NULL);	body_part_id = temp2b;

	ReadProcessMemory(hDF, (void*)(ItemAddr + 0x0), &temp8b, 8, NULL);	type_st = temp8b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0x70), &temp4b, 4, NULL);	weight = temp4b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0x78), &temp4b, 4, NULL);	stack_size = temp4b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0x9C), &temp2b, 2, NULL);	wear_stat = temp2b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xA0), &temp4b, 4, NULL);	wear_stat = temp4b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xB0), &temp2b, 2, NULL);	mat_type = temp2b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xB4), &temp4b, 4, NULL);	mat_index = temp4b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xB8), &temp2b, 2, NULL);	race = temp2b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xBA), &temp2b, 2, NULL);	quality = temp2b;

	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xE0), &temp8b, 8, NULL); subtype = temp8b;

	if (type_st == mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("bckpck")) {
		strcpy_s(name, 32, "backpack");
		isContainer = true;
	}
	else if (type_st == mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("flask")) {
		strcpy_s(name, 32, "flask/waterskin");
		isContainer = true;
	}
	else if (type_st == mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("quiver")) {
		strcpy_s(name, 32, "quiver");
		isContainer = true;
	}
	else {
		ReadProcessMemory(hDF, (void*)(subtype + 0x60), name, 32, NULL);
		name[31] = 0;
		isContainer = false;
	}

	sName = gcnew String(name);
}

DFTool::InventoryEditor::Item::Item(uint64_t _ItemAddr)
{
	name = new char[32];
	index_in_inventory = -1;

	uint64_t temp8b;
	uint32_t temp4b;
	uint16_t temp2b;

	ItemAddr = _ItemAddr;
	mode = NULL;
	body_part_id = NULL;

	ReadProcessMemory(hDF, (void*)(ItemAddr + 0x0), &temp8b, 8, NULL);	type_st = temp8b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0x70), &temp4b, 4, NULL);	weight = temp4b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0x78), &temp4b, 4, NULL);	stack_size = temp4b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0x9C), &temp2b, 2, NULL);	wear_stat = temp2b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xA0), &temp4b, 4, NULL);	wear_stat = temp4b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xB0), &temp2b, 2, NULL);	mat_type = temp2b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xB4), &temp4b, 4, NULL);	mat_index = temp4b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xB8), &temp2b, 2, NULL);	race = temp2b;
	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xBA), &temp2b, 2, NULL);	quality = temp2b;

	ReadProcessMemory(hDF, (void*)(ItemAddr + 0xE0), &temp8b, 8, NULL); subtype = temp8b;

	if (type_st == mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("bckpck")) {
		strcpy_s(name, 32, "backpack");
		isContainer = true;
	}
	else if (type_st == mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("flask")) {
		strcpy_s(name, 32, "flask/waterskin");
		isContainer = true;
	}
	else if (type_st == mainform::GetDFStartAddr() + mainform::GetMemLayout()->GetAddrByName("quiver")) {
		strcpy_s(name, 32, "quiver");
		isContainer = true;
	}
	else {
		ReadProcessMemory(hDF, (void*)(subtype + 0x60), name, 32, NULL);
		name[31] = 0;
		isContainer = false;
	}

	sName = gcnew String(name);
}

DFTool::InventoryEditor::Item::Item(Item ^ _item)
{
	weight = _item->weight;
	stack_size = _item->stack_size;
	wear_stat = _item->wear_stat;
	wear_timer = _item->wear_timer;
	mat_type = _item->mat_type;
	mat_index = _item->mat_index;
	race = _item->race;
	quality = _item->quality;
	type_st = _item->type_st;
	subtype = _item->subtype;
	ItemAddr = _item->ItemAddr;
	mode = _item->mode;
	index_in_inventory = _item->index_in_inventory;
	isContainer = _item->isContainer;

	name = new char[32];
	strcpy_s(name, 32, _item->name);
	sName = gcnew String(name);
	body_part_id = _item->body_part_id;
}

DFTool::InventoryEditor::Item::~Item()
{
	delete[] name;
}

String^ DFTool::InventoryEditor::Item::GetName()
{
	return gcnew String(name);
}

void DFTool::InventoryEditor::Item::Save()
{
	uint32_t temp4b;
	uint16_t temp2b;

	temp4b = weight;	WriteProcessMemory(hDF, (void*)(ItemAddr + 0x70), &temp4b, 4, NULL);
	temp4b = stack_size; WriteProcessMemory(hDF, (void*)(ItemAddr + 0x78), &temp4b, 4, NULL);
	temp2b = wear_stat; WriteProcessMemory(hDF, (void*)(ItemAddr + 0x9C), &temp2b, 2, NULL);
	temp4b = wear_stat; WriteProcessMemory(hDF, (void*)(ItemAddr + 0xA0), &temp4b, 4, NULL);
	temp2b = mat_type; WriteProcessMemory(hDF, (void*)(ItemAddr + 0xB0), &temp2b, 2, NULL);
	temp4b = mat_index; WriteProcessMemory(hDF, (void*)(ItemAddr + 0xB4), &temp4b, 4, NULL);
	temp2b = race; WriteProcessMemory(hDF, (void*)(ItemAddr + 0xB8), &temp2b, 2, NULL);
	temp2b = quality; WriteProcessMemory(hDF, (void*)(ItemAddr + 0xBA), &temp2b, 2, NULL);
}
