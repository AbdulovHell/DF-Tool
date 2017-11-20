#pragma once

namespace DFTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ DwarfEditor
	/// </summary>
	public ref class DwarfEditor : public System::Windows::Forms::Form
	{
	public:
		DwarfEditor(void)
		{
			InitializeComponent();
		}
		DwarfEditor(uint8_t _mode)
		{
			InitializeComponent();
			ChangeMode(_mode);
		}
		DwarfEditor(uint8_t _mode, int _dwarfnum)
		{
			InitializeComponent();
			ChangeMode(_mode, _dwarfnum);
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~DwarfEditor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  DwarfList;
	protected:
	private: System::Windows::Forms::Button^  DwarfListUpdateBtn;
	private: System::Windows::Forms::GroupBox^  NameEd;
	private: System::Windows::Forms::ComboBox^  NameSecondP2Ind;

	private: System::Windows::Forms::ComboBox^  NameSecondP1Ind;

	private: System::Windows::Forms::Button^  ApplyNameBtn;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  SkillEd;
	private: System::Windows::Forms::Button^  ClrAllSkillsBtn;
	private: System::Windows::Forms::Button^  CpySkillBtn;


	private: System::Windows::Forms::Button^  SetAllSkill5NBtn;


	private: System::Windows::Forms::Button^  SetAllSkill5Btn;

	private: System::Windows::Forms::TextBox^  DwarfSPEd;


	private: System::Windows::Forms::Button^  SetDwarfSP;
	private: System::Windows::Forms::GroupBox^  AgeEd;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  AgeBirthYear;

	private: System::Windows::Forms::TextBox^  AgeBirthMonth;

	private: System::Windows::Forms::TextBox^  AgeBirthDay;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  AgeDeathYear;

	private: System::Windows::Forms::TextBox^  AgeDeathMonth;

	private: System::Windows::Forms::TextBox^  AgeDeathDay;

	private: System::Windows::Forms::GroupBox^  RelationsEd;
	private: System::Windows::Forms::TextBox^  MotherID;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::GroupBox^  GenderEd;
	private: System::Windows::Forms::RadioButton^  FemaleBtn;
	private: System::Windows::Forms::RadioButton^  MaleBtn;
	private: System::Windows::Forms::TextBox^  SpouseID;

	private: System::Windows::Forms::TextBox^  LoverID;

	private: System::Windows::Forms::TextBox^  FatherID;
	private: System::Windows::Forms::GroupBox^  OrientationEd;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::TextBox^  textBox15;
	private: System::Windows::Forms::TextBox^  textBox16;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::Windows::Forms::TextBox^  textBox18;
	private: System::Windows::Forms::TextBox^  textBox19;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::Button^  button19;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::Button^  button20;

	private: System::Windows::Forms::TextBox^  NameFirstEd;

	private:
		void ChangeMode(int _mode);
		void ChangeMode(int _mode, int dwarfnum);
		void LoadDwarfInForm();
		void DwarfListUpdate();
		int RangeRand(int range_min, int range_max);
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		uint8_t EditMode;
		System::Collections::Generic::Dictionary<size_t, String^> ValNamesDict;
		System::Collections::Generic::Dictionary<String^, size_t> NamesValDict;
		List<CheckBox^> o_Boxes;
		List<TextBox^> att_boxes;
		List<Button^> att_5k_buttons;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->DwarfList = (gcnew System::Windows::Forms::ComboBox());
			this->DwarfListUpdateBtn = (gcnew System::Windows::Forms::Button());
			this->NameEd = (gcnew System::Windows::Forms::GroupBox());
			this->NameSecondP2Ind = (gcnew System::Windows::Forms::ComboBox());
			this->NameSecondP1Ind = (gcnew System::Windows::Forms::ComboBox());
			this->ApplyNameBtn = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->NameFirstEd = (gcnew System::Windows::Forms::TextBox());
			this->SkillEd = (gcnew System::Windows::Forms::GroupBox());
			this->ClrAllSkillsBtn = (gcnew System::Windows::Forms::Button());
			this->CpySkillBtn = (gcnew System::Windows::Forms::Button());
			this->SetAllSkill5NBtn = (gcnew System::Windows::Forms::Button());
			this->SetAllSkill5Btn = (gcnew System::Windows::Forms::Button());
			this->DwarfSPEd = (gcnew System::Windows::Forms::TextBox());
			this->SetDwarfSP = (gcnew System::Windows::Forms::Button());
			this->AgeEd = (gcnew System::Windows::Forms::GroupBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->AgeDeathYear = (gcnew System::Windows::Forms::TextBox());
			this->AgeBirthYear = (gcnew System::Windows::Forms::TextBox());
			this->AgeDeathMonth = (gcnew System::Windows::Forms::TextBox());
			this->AgeBirthMonth = (gcnew System::Windows::Forms::TextBox());
			this->AgeDeathDay = (gcnew System::Windows::Forms::TextBox());
			this->AgeBirthDay = (gcnew System::Windows::Forms::TextBox());
			this->RelationsEd = (gcnew System::Windows::Forms::GroupBox());
			this->SpouseID = (gcnew System::Windows::Forms::TextBox());
			this->LoverID = (gcnew System::Windows::Forms::TextBox());
			this->FatherID = (gcnew System::Windows::Forms::TextBox());
			this->MotherID = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->GenderEd = (gcnew System::Windows::Forms::GroupBox());
			this->FemaleBtn = (gcnew System::Windows::Forms::RadioButton());
			this->MaleBtn = (gcnew System::Windows::Forms::RadioButton());
			this->OrientationEd = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->NameEd->SuspendLayout();
			this->SkillEd->SuspendLayout();
			this->AgeEd->SuspendLayout();
			this->RelationsEd->SuspendLayout();
			this->GenderEd->SuspendLayout();
			this->OrientationEd->SuspendLayout();
			this->SuspendLayout();
			// 
			// DwarfList
			// 
			this->DwarfList->FormattingEnabled = true;
			this->DwarfList->Location = System::Drawing::Point(12, 12);
			this->DwarfList->Name = L"DwarfList";
			this->DwarfList->Size = System::Drawing::Size(353, 21);
			this->DwarfList->TabIndex = 0;
			this->DwarfList->SelectedIndexChanged += gcnew System::EventHandler(this, &DwarfEditor::DwarfList_SelectedIndexChanged);
			// 
			// DwarfListUpdateBtn
			// 
			this->DwarfListUpdateBtn->Location = System::Drawing::Point(371, 12);
			this->DwarfListUpdateBtn->Name = L"DwarfListUpdateBtn";
			this->DwarfListUpdateBtn->Size = System::Drawing::Size(56, 21);
			this->DwarfListUpdateBtn->TabIndex = 1;
			this->DwarfListUpdateBtn->Text = L"Update";
			this->DwarfListUpdateBtn->UseVisualStyleBackColor = true;
			this->DwarfListUpdateBtn->Click += gcnew System::EventHandler(this, &DwarfEditor::DwarfListUpdateBtn_Click);
			// 
			// NameEd
			// 
			this->NameEd->Controls->Add(this->NameSecondP2Ind);
			this->NameEd->Controls->Add(this->NameSecondP1Ind);
			this->NameEd->Controls->Add(this->ApplyNameBtn);
			this->NameEd->Controls->Add(this->label3);
			this->NameEd->Controls->Add(this->label2);
			this->NameEd->Controls->Add(this->label1);
			this->NameEd->Controls->Add(this->NameFirstEd);
			this->NameEd->Location = System::Drawing::Point(12, 39);
			this->NameEd->Name = L"NameEd";
			this->NameEd->Size = System::Drawing::Size(415, 87);
			this->NameEd->TabIndex = 2;
			this->NameEd->TabStop = false;
			this->NameEd->Text = L"Name Editor";
			// 
			// NameSecondP2Ind
			// 
			this->NameSecondP2Ind->FormattingEnabled = true;
			this->NameSecondP2Ind->Location = System::Drawing::Point(284, 33);
			this->NameSecondP2Ind->Name = L"NameSecondP2Ind";
			this->NameSecondP2Ind->Size = System::Drawing::Size(125, 21);
			this->NameSecondP2Ind->TabIndex = 8;
			// 
			// NameSecondP1Ind
			// 
			this->NameSecondP1Ind->FormattingEnabled = true;
			this->NameSecondP1Ind->Location = System::Drawing::Point(153, 33);
			this->NameSecondP1Ind->Name = L"NameSecondP1Ind";
			this->NameSecondP1Ind->Size = System::Drawing::Size(125, 21);
			this->NameSecondP1Ind->TabIndex = 7;
			// 
			// ApplyNameBtn
			// 
			this->ApplyNameBtn->Location = System::Drawing::Point(6, 59);
			this->ApplyNameBtn->Name = L"ApplyNameBtn";
			this->ApplyNameBtn->Size = System::Drawing::Size(403, 21);
			this->ApplyNameBtn->TabIndex = 6;
			this->ApplyNameBtn->Text = L"Apply";
			this->ApplyNameBtn->UseVisualStyleBackColor = true;
			this->ApplyNameBtn->Click += gcnew System::EventHandler(this, &DwarfEditor::ApplyNameBtn_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(281, 17);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Second name p2:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(150, 17);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(91, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Second name p1:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"First name:";
			// 
			// NameFirstEd
			// 
			this->NameFirstEd->Location = System::Drawing::Point(6, 33);
			this->NameFirstEd->MaxLength = 27;
			this->NameFirstEd->Name = L"NameFirstEd";
			this->NameFirstEd->Size = System::Drawing::Size(141, 20);
			this->NameFirstEd->TabIndex = 0;
			// 
			// SkillEd
			// 
			this->SkillEd->Controls->Add(this->ClrAllSkillsBtn);
			this->SkillEd->Controls->Add(this->CpySkillBtn);
			this->SkillEd->Controls->Add(this->SetAllSkill5NBtn);
			this->SkillEd->Controls->Add(this->SetAllSkill5Btn);
			this->SkillEd->Controls->Add(this->DwarfSPEd);
			this->SkillEd->Controls->Add(this->SetDwarfSP);
			this->SkillEd->Location = System::Drawing::Point(433, 12);
			this->SkillEd->Name = L"SkillEd";
			this->SkillEd->Size = System::Drawing::Size(319, 114);
			this->SkillEd->TabIndex = 3;
			this->SkillEd->TabStop = false;
			this->SkillEd->Text = L"Skill Editor";
			// 
			// ClrAllSkillsBtn
			// 
			this->ClrAllSkillsBtn->Location = System::Drawing::Point(226, 84);
			this->ClrAllSkillsBtn->Name = L"ClrAllSkillsBtn";
			this->ClrAllSkillsBtn->Size = System::Drawing::Size(87, 23);
			this->ClrAllSkillsBtn->TabIndex = 5;
			this->ClrAllSkillsBtn->Text = L"Clear all skills";
			this->ClrAllSkillsBtn->UseVisualStyleBackColor = true;
			this->ClrAllSkillsBtn->Click += gcnew System::EventHandler(this, &DwarfEditor::ClrAllSkillsBtn_Click);
			// 
			// CpySkillBtn
			// 
			this->CpySkillBtn->Location = System::Drawing::Point(6, 84);
			this->CpySkillBtn->Name = L"CpySkillBtn";
			this->CpySkillBtn->Size = System::Drawing::Size(214, 23);
			this->CpySkillBtn->TabIndex = 4;
			this->CpySkillBtn->Text = L"Copy skill form selected Dwarf to the other";
			this->CpySkillBtn->UseVisualStyleBackColor = true;
			this->CpySkillBtn->Click += gcnew System::EventHandler(this, &DwarfEditor::CpySkillBtn_Click);
			// 
			// SetAllSkill5NBtn
			// 
			this->SetAllSkill5NBtn->Location = System::Drawing::Point(116, 52);
			this->SetAllSkill5NBtn->Name = L"SetAllSkill5NBtn";
			this->SetAllSkill5NBtn->Size = System::Drawing::Size(197, 23);
			this->SetAllSkill5NBtn->TabIndex = 3;
			this->SetAllSkill5NBtn->Text = L"Set L+5 skills, only above \"Novice\"";
			this->SetAllSkill5NBtn->UseVisualStyleBackColor = true;
			this->SetAllSkill5NBtn->Click += gcnew System::EventHandler(this, &DwarfEditor::SetAllSkill5NBtn_Click);
			// 
			// SetAllSkill5Btn
			// 
			this->SetAllSkill5Btn->Location = System::Drawing::Point(6, 52);
			this->SetAllSkill5Btn->Name = L"SetAllSkill5Btn";
			this->SetAllSkill5Btn->Size = System::Drawing::Size(104, 23);
			this->SetAllSkill5Btn->TabIndex = 2;
			this->SetAllSkill5Btn->Text = L"All skills on L+5";
			this->SetAllSkill5Btn->UseVisualStyleBackColor = true;
			this->SetAllSkill5Btn->Click += gcnew System::EventHandler(this, &DwarfEditor::SetAllSkill5Btn_Click);
			// 
			// DwarfSPEd
			// 
			this->DwarfSPEd->Location = System::Drawing::Point(102, 20);
			this->DwarfSPEd->Name = L"DwarfSPEd";
			this->DwarfSPEd->Size = System::Drawing::Size(100, 20);
			this->DwarfSPEd->TabIndex = 1;
			this->DwarfSPEd->Text = L"0";
			// 
			// SetDwarfSP
			// 
			this->SetDwarfSP->Location = System::Drawing::Point(6, 19);
			this->SetDwarfSP->Name = L"SetDwarfSP";
			this->SetDwarfSP->Size = System::Drawing::Size(90, 22);
			this->SetDwarfSP->TabIndex = 0;
			this->SetDwarfSP->Text = L"Set dwarf SP";
			this->SetDwarfSP->UseVisualStyleBackColor = true;
			this->SetDwarfSP->Click += gcnew System::EventHandler(this, &DwarfEditor::SetDwarfSP_Click);
			// 
			// AgeEd
			// 
			this->AgeEd->Controls->Add(this->label8);
			this->AgeEd->Controls->Add(this->label7);
			this->AgeEd->Controls->Add(this->label6);
			this->AgeEd->Controls->Add(this->label5);
			this->AgeEd->Controls->Add(this->label4);
			this->AgeEd->Controls->Add(this->AgeDeathYear);
			this->AgeEd->Controls->Add(this->AgeBirthYear);
			this->AgeEd->Controls->Add(this->AgeDeathMonth);
			this->AgeEd->Controls->Add(this->AgeBirthMonth);
			this->AgeEd->Controls->Add(this->AgeDeathDay);
			this->AgeEd->Controls->Add(this->AgeBirthDay);
			this->AgeEd->Location = System::Drawing::Point(12, 132);
			this->AgeEd->Name = L"AgeEd";
			this->AgeEd->Size = System::Drawing::Size(170, 83);
			this->AgeEd->TabIndex = 4;
			this->AgeEd->TabStop = false;
			this->AgeEd->Text = L"Age";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(118, 14);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(29, 13);
			this->label8->TabIndex = 7;
			this->label8->Text = L"Year";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(79, 14);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(37, 13);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Month";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(42, 14);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(26, 13);
			this->label6->TabIndex = 5;
			this->label6->Text = L"Day";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 59);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(36, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Death";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 33);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(28, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Birth";
			// 
			// AgeDeathYear
			// 
			this->AgeDeathYear->Location = System::Drawing::Point(119, 56);
			this->AgeDeathYear->MaxLength = 5;
			this->AgeDeathYear->Name = L"AgeDeathYear";
			this->AgeDeathYear->Size = System::Drawing::Size(44, 20);
			this->AgeDeathYear->TabIndex = 2;
			// 
			// AgeBirthYear
			// 
			this->AgeBirthYear->Location = System::Drawing::Point(119, 30);
			this->AgeBirthYear->MaxLength = 5;
			this->AgeBirthYear->Name = L"AgeBirthYear";
			this->AgeBirthYear->Size = System::Drawing::Size(44, 20);
			this->AgeBirthYear->TabIndex = 2;
			// 
			// AgeDeathMonth
			// 
			this->AgeDeathMonth->Location = System::Drawing::Point(82, 56);
			this->AgeDeathMonth->MaxLength = 2;
			this->AgeDeathMonth->Name = L"AgeDeathMonth";
			this->AgeDeathMonth->Size = System::Drawing::Size(31, 20);
			this->AgeDeathMonth->TabIndex = 1;
			// 
			// AgeBirthMonth
			// 
			this->AgeBirthMonth->Location = System::Drawing::Point(82, 30);
			this->AgeBirthMonth->MaxLength = 2;
			this->AgeBirthMonth->Name = L"AgeBirthMonth";
			this->AgeBirthMonth->Size = System::Drawing::Size(31, 20);
			this->AgeBirthMonth->TabIndex = 1;
			// 
			// AgeDeathDay
			// 
			this->AgeDeathDay->Location = System::Drawing::Point(45, 56);
			this->AgeDeathDay->MaxLength = 2;
			this->AgeDeathDay->Name = L"AgeDeathDay";
			this->AgeDeathDay->Size = System::Drawing::Size(31, 20);
			this->AgeDeathDay->TabIndex = 0;
			// 
			// AgeBirthDay
			// 
			this->AgeBirthDay->Location = System::Drawing::Point(45, 30);
			this->AgeBirthDay->MaxLength = 2;
			this->AgeBirthDay->Name = L"AgeBirthDay";
			this->AgeBirthDay->Size = System::Drawing::Size(31, 20);
			this->AgeBirthDay->TabIndex = 0;
			// 
			// RelationsEd
			// 
			this->RelationsEd->Controls->Add(this->SpouseID);
			this->RelationsEd->Controls->Add(this->LoverID);
			this->RelationsEd->Controls->Add(this->FatherID);
			this->RelationsEd->Controls->Add(this->MotherID);
			this->RelationsEd->Controls->Add(this->label12);
			this->RelationsEd->Controls->Add(this->label11);
			this->RelationsEd->Controls->Add(this->label10);
			this->RelationsEd->Controls->Add(this->label9);
			this->RelationsEd->Location = System::Drawing::Point(188, 132);
			this->RelationsEd->Name = L"RelationsEd";
			this->RelationsEd->Size = System::Drawing::Size(239, 125);
			this->RelationsEd->TabIndex = 5;
			this->RelationsEd->TabStop = false;
			this->RelationsEd->Text = L"Relations";
			// 
			// SpouseID
			// 
			this->SpouseID->Location = System::Drawing::Point(69, 97);
			this->SpouseID->Name = L"SpouseID";
			this->SpouseID->Size = System::Drawing::Size(164, 20);
			this->SpouseID->TabIndex = 4;
			// 
			// LoverID
			// 
			this->LoverID->Location = System::Drawing::Point(69, 71);
			this->LoverID->Name = L"LoverID";
			this->LoverID->Size = System::Drawing::Size(164, 20);
			this->LoverID->TabIndex = 4;
			// 
			// FatherID
			// 
			this->FatherID->Location = System::Drawing::Point(69, 45);
			this->FatherID->Name = L"FatherID";
			this->FatherID->Size = System::Drawing::Size(164, 20);
			this->FatherID->TabIndex = 4;
			// 
			// MotherID
			// 
			this->MotherID->Location = System::Drawing::Point(69, 19);
			this->MotherID->Name = L"MotherID";
			this->MotherID->Size = System::Drawing::Size(164, 20);
			this->MotherID->TabIndex = 4;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(6, 100);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(57, 13);
			this->label12->TabIndex = 3;
			this->label12->Text = L"Spouse ID";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(6, 74);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(48, 13);
			this->label11->TabIndex = 2;
			this->label11->Text = L"Lover ID";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(6, 48);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(51, 13);
			this->label10->TabIndex = 1;
			this->label10->Text = L"Father ID";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(6, 22);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(54, 13);
			this->label9->TabIndex = 0;
			this->label9->Text = L"Mother ID";
			// 
			// GenderEd
			// 
			this->GenderEd->Controls->Add(this->FemaleBtn);
			this->GenderEd->Controls->Add(this->MaleBtn);
			this->GenderEd->Location = System::Drawing::Point(12, 221);
			this->GenderEd->Name = L"GenderEd";
			this->GenderEd->Size = System::Drawing::Size(170, 36);
			this->GenderEd->TabIndex = 6;
			this->GenderEd->TabStop = false;
			this->GenderEd->Text = L"Gender";
			// 
			// FemaleBtn
			// 
			this->FemaleBtn->AutoSize = true;
			this->FemaleBtn->Location = System::Drawing::Point(9, 13);
			this->FemaleBtn->Name = L"FemaleBtn";
			this->FemaleBtn->Size = System::Drawing::Size(59, 17);
			this->FemaleBtn->TabIndex = 7;
			this->FemaleBtn->TabStop = true;
			this->FemaleBtn->Text = L"Female";
			this->FemaleBtn->UseVisualStyleBackColor = true;
			// 
			// MaleBtn
			// 
			this->MaleBtn->AutoSize = true;
			this->MaleBtn->Location = System::Drawing::Point(116, 13);
			this->MaleBtn->Name = L"MaleBtn";
			this->MaleBtn->Size = System::Drawing::Size(48, 17);
			this->MaleBtn->TabIndex = 7;
			this->MaleBtn->TabStop = true;
			this->MaleBtn->Text = L"Male";
			this->MaleBtn->UseVisualStyleBackColor = true;
			// 
			// OrientationEd
			// 
			this->OrientationEd->Controls->Add(this->checkBox4);
			this->OrientationEd->Controls->Add(this->checkBox3);
			this->OrientationEd->Controls->Add(this->checkBox2);
			this->OrientationEd->Controls->Add(this->checkBox1);
			this->OrientationEd->Location = System::Drawing::Point(12, 263);
			this->OrientationEd->Name = L"OrientationEd";
			this->OrientationEd->Size = System::Drawing::Size(170, 108);
			this->OrientationEd->TabIndex = 7;
			this->OrientationEd->TabStop = false;
			this->OrientationEd->Text = L"Orientation";
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(6, 88);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(86, 17);
			this->checkBox4->TabIndex = 8;
			this->checkBox4->Text = L"Marry female";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(6, 65);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(106, 17);
			this->checkBox3->TabIndex = 8;
			this->checkBox3->Text = L"Romance female";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(6, 42);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(77, 17);
			this->checkBox2->TabIndex = 8;
			this->checkBox2->Text = L"Marry male";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(6, 19);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(97, 17);
			this->checkBox1->TabIndex = 8;
			this->checkBox1->Text = L"Romance male";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(265, 263);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 8;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(265, 289);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 8;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(265, 315);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 8;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(265, 341);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 8;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(265, 367);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 8;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(265, 393);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 8;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(584, 133);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 20);
			this->textBox7->TabIndex = 8;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(584, 159);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(100, 20);
			this->textBox8->TabIndex = 8;
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(584, 185);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(100, 20);
			this->textBox9->TabIndex = 8;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(584, 211);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(100, 20);
			this->textBox10->TabIndex = 8;
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(584, 237);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(100, 20);
			this->textBox11->TabIndex = 8;
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(584, 263);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(100, 20);
			this->textBox12->TabIndex = 8;
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(584, 289);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(100, 20);
			this->textBox13->TabIndex = 8;
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(584, 315);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(100, 20);
			this->textBox14->TabIndex = 8;
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(584, 341);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(100, 20);
			this->textBox15->TabIndex = 8;
			// 
			// textBox16
			// 
			this->textBox16->Location = System::Drawing::Point(584, 368);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(100, 20);
			this->textBox16->TabIndex = 8;
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(584, 394);
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(100, 20);
			this->textBox17->TabIndex = 8;
			// 
			// textBox18
			// 
			this->textBox18->Location = System::Drawing::Point(584, 420);
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(100, 20);
			this->textBox18->TabIndex = 8;
			// 
			// textBox19
			// 
			this->textBox19->Location = System::Drawing::Point(584, 446);
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(100, 20);
			this->textBox19->TabIndex = 8;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(371, 262);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(56, 21);
			this->button1->TabIndex = 9;
			this->button1->Text = L"5000";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(371, 288);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(56, 21);
			this->button2->TabIndex = 9;
			this->button2->Text = L"5000";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(371, 314);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(56, 21);
			this->button3->TabIndex = 9;
			this->button3->Text = L"5000";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(371, 340);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(56, 21);
			this->button4->TabIndex = 9;
			this->button4->Text = L"5000";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(371, 366);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(56, 21);
			this->button5->TabIndex = 9;
			this->button5->Text = L"5000";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(371, 392);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(56, 21);
			this->button6->TabIndex = 9;
			this->button6->Text = L"5000";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(690, 132);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(56, 21);
			this->button7->TabIndex = 9;
			this->button7->Text = L"5000";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(690, 158);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(56, 21);
			this->button8->TabIndex = 9;
			this->button8->Text = L"5000";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(690, 184);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(56, 21);
			this->button9->TabIndex = 9;
			this->button9->Text = L"5000";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(690, 210);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(56, 21);
			this->button10->TabIndex = 9;
			this->button10->Text = L"5000";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(690, 236);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(56, 21);
			this->button11->TabIndex = 9;
			this->button11->Text = L"5000";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(690, 262);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(56, 21);
			this->button12->TabIndex = 9;
			this->button12->Text = L"5000";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(690, 288);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(56, 21);
			this->button13->TabIndex = 9;
			this->button13->Text = L"5000";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(690, 314);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(56, 21);
			this->button14->TabIndex = 9;
			this->button14->Text = L"5000";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(690, 340);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(56, 21);
			this->button15->TabIndex = 9;
			this->button15->Text = L"5000";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(690, 367);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(56, 21);
			this->button16->TabIndex = 9;
			this->button16->Text = L"5000";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(690, 393);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(56, 21);
			this->button17->TabIndex = 9;
			this->button17->Text = L"5000";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button18
			// 
			this->button18->Location = System::Drawing::Point(690, 419);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(56, 21);
			this->button18->TabIndex = 9;
			this->button18->Text = L"5000";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// button19
			// 
			this->button19->Location = System::Drawing::Point(690, 445);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(56, 21);
			this->button19->TabIndex = 9;
			this->button19->Text = L"5000";
			this->button19->UseVisualStyleBackColor = true;
			this->button19->Click += gcnew System::EventHandler(this, &DwarfEditor::button1_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(497, 136);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(81, 13);
			this->label13->TabIndex = 10;
			this->label13->Text = L"Analytical ability";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(542, 162);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(36, 13);
			this->label14->TabIndex = 10;
			this->label14->Text = L"Focus";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(525, 188);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(53, 13);
			this->label15->TabIndex = 10;
			this->label15->Text = L"Willpower";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(528, 214);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(50, 13);
			this->label16->TabIndex = 10;
			this->label16->Text = L"Creativity";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(534, 240);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(44, 13);
			this->label17->TabIndex = 10;
			this->label17->Text = L"Intuition";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(529, 266);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(49, 13);
			this->label18->TabIndex = 10;
			this->label18->Text = L"Patience";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(534, 292);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(44, 13);
			this->label19->TabIndex = 10;
			this->label19->Text = L"Memory";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(498, 318);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(80, 13);
			this->label20->TabIndex = 10;
			this->label20->Text = L"Linguistic ability";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(508, 344);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(70, 13);
			this->label21->TabIndex = 10;
			this->label21->Text = L"Spatial sense";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(525, 371);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(53, 13);
			this->label22->TabIndex = 10;
			this->label22->Text = L"Musicality";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(488, 397);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(90, 13);
			this->label23->TabIndex = 10;
			this->label23->Text = L"Kinesthetic sense";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(530, 423);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(48, 13);
			this->label24->TabIndex = 10;
			this->label24->Text = L"Empathy";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(488, 449);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(90, 13);
			this->label25->TabIndex = 10;
			this->label25->Text = L"Social awareness";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(212, 266);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(47, 13);
			this->label26->TabIndex = 11;
			this->label26->Text = L"Strength";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(225, 292);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(34, 13);
			this->label27->TabIndex = 11;
			this->label27->Text = L"Agility";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(199, 318);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(60, 13);
			this->label28->TabIndex = 12;
			this->label28->Text = L"Toughness";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(200, 344);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(59, 13);
			this->label29->TabIndex = 13;
			this->label29->Text = L"Endurance";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(188, 370);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(71, 13);
			this->label30->TabIndex = 14;
			this->label30->Text = L"Recuperation";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(163, 397);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(96, 13);
			this->label31->TabIndex = 15;
			this->label31->Text = L"Disease resistance";
			// 
			// button20
			// 
			this->button20->Location = System::Drawing::Point(286, 423);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(119, 39);
			this->button20->TabIndex = 16;
			this->button20->Text = L"Save";
			this->button20->UseVisualStyleBackColor = true;
			this->button20->Click += gcnew System::EventHandler(this, &DwarfEditor::button20_Click);
			// 
			// DwarfEditor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(763, 478);
			this->Controls->Add(this->button20);
			this->Controls->Add(this->label31);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->label28);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->button19);
			this->Controls->Add(this->button18);
			this->Controls->Add(this->button17);
			this->Controls->Add(this->button16);
			this->Controls->Add(this->button15);
			this->Controls->Add(this->button14);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox19);
			this->Controls->Add(this->textBox18);
			this->Controls->Add(this->textBox17);
			this->Controls->Add(this->textBox16);
			this->Controls->Add(this->textBox15);
			this->Controls->Add(this->textBox14);
			this->Controls->Add(this->textBox13);
			this->Controls->Add(this->textBox12);
			this->Controls->Add(this->textBox11);
			this->Controls->Add(this->textBox10);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->OrientationEd);
			this->Controls->Add(this->GenderEd);
			this->Controls->Add(this->RelationsEd);
			this->Controls->Add(this->AgeEd);
			this->Controls->Add(this->SkillEd);
			this->Controls->Add(this->NameEd);
			this->Controls->Add(this->DwarfListUpdateBtn);
			this->Controls->Add(this->DwarfList);
			this->Name = L"DwarfEditor";
			this->Text = L"DwarfEditor";
			this->Load += gcnew System::EventHandler(this, &DwarfEditor::DwarfEditor_Load);
			this->NameEd->ResumeLayout(false);
			this->NameEd->PerformLayout();
			this->SkillEd->ResumeLayout(false);
			this->SkillEd->PerformLayout();
			this->AgeEd->ResumeLayout(false);
			this->AgeEd->PerformLayout();
			this->RelationsEd->ResumeLayout(false);
			this->RelationsEd->PerformLayout();
			this->GenderEd->ResumeLayout(false);
			this->GenderEd->PerformLayout();
			this->OrientationEd->ResumeLayout(false);
			this->OrientationEd->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void DwarfListUpdateBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DwarfEditor_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ApplyNameBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DwarfList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetDwarfSP_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetAllSkill5Btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetAllSkill5NBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CpySkillBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ClrAllSkillsBtn_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
