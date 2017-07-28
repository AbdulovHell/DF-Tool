#pragma once
#include <stdint.h>

namespace DFTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ InventoryEditor
	/// </summary>
	public ref class InventoryEditor : public System::Windows::Forms::Form
	{
	public:
		InventoryEditor(void);
		InventoryEditor(uint32_t _CreatureID);

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~InventoryEditor();

	private:
		ref class Item {
			uint64_t type_st;
			uint64_t subtype;
			uint16_t mode;
			uint32_t index_in_inventory;	//?
			char* name;	//32
		public:
			uint64_t ItemAddr;
			String^ sName;
			uint16_t body_part_id;
			bool isContainer;

			int weight;
			int stack_size;
			short wear_stat;
			int wear_timer;
			short mat_type;
			int mat_index;
			short race;
			short quality;

			Item();
			Item(uint64_t ItemOffset, uint32_t index);
			Item(uint64_t ItemAddr);
			Item(Item^ _item);
			~Item();
			String^ GetName();
			void Save();
		};

		void LoadInventory();
		void LoadItem(Item^ item, bool wCont);
		uint64_t FindItem(uint32_t id);
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		static HANDLE hDF;
		uint32_t CreatureID;
		Item^ SelectedItem;
		List<List<Item^>^>^ SortedItems;
		List<Item^>^ UnsortedItems;
		List<Item^>^ SelectedBodyPart;
		List<Item^>^ InContainerItems;
	private: System::Windows::Forms::Button^  ReloadInvBtn;
	private: System::Windows::Forms::ListBox^  ItemsInContBox;









	private: System::Windows::Forms::ComboBox^  BodyPartList;
	private: System::Windows::Forms::ListBox^  ItemsOnPartBox;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  ItemNameLbl;
	private: System::Windows::Forms::TextBox^  WeightEdit;
	private: System::Windows::Forms::TextBox^  StackSizeEdit;
	private: System::Windows::Forms::ComboBox^  WearStatusList;
	private: System::Windows::Forms::TextBox^  WearTimerEdit;
	private: System::Windows::Forms::TextBox^  MaterialTypeEdit;
	private: System::Windows::Forms::TextBox^  MaterialIndexEdit;
	private: System::Windows::Forms::TextBox^  RaceEdit;
	private: System::Windows::Forms::ComboBox^  QualityList;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  SaveItemBtn;
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
			 /// содержимое этого метода с помощью редактора кода.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->ReloadInvBtn = (gcnew System::Windows::Forms::Button());
				 this->ItemsInContBox = (gcnew System::Windows::Forms::ListBox());
				 this->BodyPartList = (gcnew System::Windows::Forms::ComboBox());
				 this->ItemsOnPartBox = (gcnew System::Windows::Forms::ListBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->ItemNameLbl = (gcnew System::Windows::Forms::Label());
				 this->WeightEdit = (gcnew System::Windows::Forms::TextBox());
				 this->StackSizeEdit = (gcnew System::Windows::Forms::TextBox());
				 this->WearStatusList = (gcnew System::Windows::Forms::ComboBox());
				 this->WearTimerEdit = (gcnew System::Windows::Forms::TextBox());
				 this->MaterialTypeEdit = (gcnew System::Windows::Forms::TextBox());
				 this->MaterialIndexEdit = (gcnew System::Windows::Forms::TextBox());
				 this->RaceEdit = (gcnew System::Windows::Forms::TextBox());
				 this->QualityList = (gcnew System::Windows::Forms::ComboBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->label9 = (gcnew System::Windows::Forms::Label());
				 this->SaveItemBtn = (gcnew System::Windows::Forms::Button());
				 this->SuspendLayout();
				 // 
				 // ReloadInvBtn
				 // 
				 this->ReloadInvBtn->Location = System::Drawing::Point(12, 12);
				 this->ReloadInvBtn->Name = L"ReloadInvBtn";
				 this->ReloadInvBtn->Size = System::Drawing::Size(161, 23);
				 this->ReloadInvBtn->TabIndex = 0;
				 this->ReloadInvBtn->Text = L"Reload";
				 this->ReloadInvBtn->UseVisualStyleBackColor = true;
				 this->ReloadInvBtn->Click += gcnew System::EventHandler(this, &InventoryEditor::ReloadInvBtn_Click);
				 // 
				 // ItemsInContBox
				 // 
				 this->ItemsInContBox->FormattingEnabled = true;
				 this->ItemsInContBox->Location = System::Drawing::Point(445, 42);
				 this->ItemsInContBox->Name = L"ItemsInContBox";
				 this->ItemsInContBox->Size = System::Drawing::Size(161, 199);
				 this->ItemsInContBox->TabIndex = 1;
				 this->ItemsInContBox->SelectedIndexChanged += gcnew System::EventHandler(this, &InventoryEditor::ItemsInContBox_SelectedIndexChanged);
				 // 
				 // BodyPartList
				 // 
				 this->BodyPartList->FormattingEnabled = true;
				 this->BodyPartList->Items->AddRange(gcnew cli::array< System::Object^  >(22) {
					 L"Upper Body", L"Lower Body", L"Neck", L"Head",
						 L"Right upper arm", L"Left upper arm", L"Right lower arm", L"Left lower arm", L"Right hand", L"Left hand", L"Right upper leg",
						 L"Left upper leg", L"Right lower leg", L"Left lower leg", L"Right foor", L"Left foot", L"Right eye", L"Left eye", L"Right ear",
						 L"Left ear", L"Nose", L"Others"
				 });
				 this->BodyPartList->Location = System::Drawing::Point(12, 41);
				 this->BodyPartList->Name = L"BodyPartList";
				 this->BodyPartList->Size = System::Drawing::Size(161, 21);
				 this->BodyPartList->TabIndex = 2;
				 this->BodyPartList->SelectedIndexChanged += gcnew System::EventHandler(this, &InventoryEditor::BodyPartList_SelectedIndexChanged);
				 // 
				 // ItemsOnPartBox
				 // 
				 this->ItemsOnPartBox->FormattingEnabled = true;
				 this->ItemsOnPartBox->Location = System::Drawing::Point(12, 68);
				 this->ItemsOnPartBox->Name = L"ItemsOnPartBox";
				 this->ItemsOnPartBox->Size = System::Drawing::Size(161, 173);
				 this->ItemsOnPartBox->TabIndex = 3;
				 this->ItemsOnPartBox->SelectedIndexChanged += gcnew System::EventHandler(this, &InventoryEditor::ItemsOnPartBox_SelectedIndexChanged);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(503, 26);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(43, 13);
				 this->label1->TabIndex = 4;
				 this->label1->Text = L"Contain";
				 // 
				 // ItemNameLbl
				 // 
				 this->ItemNameLbl->AutoSize = true;
				 this->ItemNameLbl->Location = System::Drawing::Point(212, 17);
				 this->ItemNameLbl->Name = L"ItemNameLbl";
				 this->ItemNameLbl->Size = System::Drawing::Size(55, 13);
				 this->ItemNameLbl->TabIndex = 5;
				 this->ItemNameLbl->Text = L"ItemName";
				 // 
				 // WeightEdit
				 // 
				 this->WeightEdit->Location = System::Drawing::Point(215, 36);
				 this->WeightEdit->Name = L"WeightEdit";
				 this->WeightEdit->Size = System::Drawing::Size(131, 20);
				 this->WeightEdit->TabIndex = 6;
				 // 
				 // StackSizeEdit
				 // 
				 this->StackSizeEdit->Location = System::Drawing::Point(215, 62);
				 this->StackSizeEdit->Name = L"StackSizeEdit";
				 this->StackSizeEdit->Size = System::Drawing::Size(131, 20);
				 this->StackSizeEdit->TabIndex = 6;
				 // 
				 // WearStatusList
				 // 
				 this->WearStatusList->FormattingEnabled = true;
				 this->WearStatusList->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"(none)", L"x", L"X", L"XX" });
				 this->WearStatusList->Location = System::Drawing::Point(215, 88);
				 this->WearStatusList->Name = L"WearStatusList";
				 this->WearStatusList->Size = System::Drawing::Size(131, 21);
				 this->WearStatusList->TabIndex = 7;
				 // 
				 // WearTimerEdit
				 // 
				 this->WearTimerEdit->Location = System::Drawing::Point(215, 115);
				 this->WearTimerEdit->Name = L"WearTimerEdit";
				 this->WearTimerEdit->Size = System::Drawing::Size(131, 20);
				 this->WearTimerEdit->TabIndex = 6;
				 // 
				 // MaterialTypeEdit
				 // 
				 this->MaterialTypeEdit->Location = System::Drawing::Point(215, 141);
				 this->MaterialTypeEdit->Name = L"MaterialTypeEdit";
				 this->MaterialTypeEdit->Size = System::Drawing::Size(131, 20);
				 this->MaterialTypeEdit->TabIndex = 6;
				 // 
				 // MaterialIndexEdit
				 // 
				 this->MaterialIndexEdit->Location = System::Drawing::Point(215, 167);
				 this->MaterialIndexEdit->Name = L"MaterialIndexEdit";
				 this->MaterialIndexEdit->Size = System::Drawing::Size(131, 20);
				 this->MaterialIndexEdit->TabIndex = 6;
				 // 
				 // RaceEdit
				 // 
				 this->RaceEdit->Location = System::Drawing::Point(215, 193);
				 this->RaceEdit->Name = L"RaceEdit";
				 this->RaceEdit->Size = System::Drawing::Size(131, 20);
				 this->RaceEdit->TabIndex = 6;
				 this->RaceEdit->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &InventoryEditor::RaceEdit_MouseDoubleClick);
				 // 
				 // QualityList
				 // 
				 this->QualityList->FormattingEnabled = true;
				 this->QualityList->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
					 L"Ordinary", L"Well Crafted", L"Finely Crafted",
						 L"Superior", L"Exceptional", L"Masterful", L"Artifact"
				 });
				 this->QualityList->Location = System::Drawing::Point(215, 219);
				 this->QualityList->Name = L"QualityList";
				 this->QualityList->Size = System::Drawing::Size(131, 21);
				 this->QualityList->TabIndex = 7;
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(352, 39);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(41, 13);
				 this->label2->TabIndex = 8;
				 this->label2->Text = L"Weight";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(352, 65);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(56, 13);
				 this->label3->TabIndex = 8;
				 this->label3->Text = L"Stack size";
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(352, 91);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(64, 13);
				 this->label4->TabIndex = 8;
				 this->label4->Text = L"Wear status";
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(352, 118);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(58, 13);
				 this->label5->TabIndex = 8;
				 this->label5->Text = L"Wear timer";
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(352, 144);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(67, 13);
				 this->label6->TabIndex = 8;
				 this->label6->Text = L"Material type";
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(352, 170);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(72, 13);
				 this->label7->TabIndex = 8;
				 this->label7->Text = L"Material index";
				 // 
				 // label8
				 // 
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(352, 196);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(33, 13);
				 this->label8->TabIndex = 8;
				 this->label8->Text = L"Race";
				 // 
				 // label9
				 // 
				 this->label9->AutoSize = true;
				 this->label9->Location = System::Drawing::Point(352, 222);
				 this->label9->Name = L"label9";
				 this->label9->Size = System::Drawing::Size(39, 13);
				 this->label9->TabIndex = 8;
				 this->label9->Text = L"Quality";
				 // 
				 // SaveItemBtn
				 // 
				 this->SaveItemBtn->Location = System::Drawing::Point(271, 246);
				 this->SaveItemBtn->Name = L"SaveItemBtn";
				 this->SaveItemBtn->Size = System::Drawing::Size(75, 23);
				 this->SaveItemBtn->TabIndex = 9;
				 this->SaveItemBtn->Text = L"Save";
				 this->SaveItemBtn->UseVisualStyleBackColor = true;
				 this->SaveItemBtn->Click += gcnew System::EventHandler(this, &InventoryEditor::SaveItemBtn_Click);
				 // 
				 // InventoryEditor
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(619, 287);
				 this->Controls->Add(this->SaveItemBtn);
				 this->Controls->Add(this->label9);
				 this->Controls->Add(this->label8);
				 this->Controls->Add(this->label7);
				 this->Controls->Add(this->label6);
				 this->Controls->Add(this->label5);
				 this->Controls->Add(this->label4);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->QualityList);
				 this->Controls->Add(this->WearStatusList);
				 this->Controls->Add(this->RaceEdit);
				 this->Controls->Add(this->MaterialIndexEdit);
				 this->Controls->Add(this->MaterialTypeEdit);
				 this->Controls->Add(this->WearTimerEdit);
				 this->Controls->Add(this->StackSizeEdit);
				 this->Controls->Add(this->WeightEdit);
				 this->Controls->Add(this->ItemNameLbl);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->ItemsOnPartBox);
				 this->Controls->Add(this->BodyPartList);
				 this->Controls->Add(this->ItemsInContBox);
				 this->Controls->Add(this->ReloadInvBtn);
				 this->Name = L"InventoryEditor";
				 this->Text = L"InventoryEditor";
				 this->Load += gcnew System::EventHandler(this, &InventoryEditor::InventoryEditor_Load);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void InventoryEditor_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BodyPartList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ItemsOnPartBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SaveItemBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void RaceEdit_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void ItemsInContBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ReloadInvBtn_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
