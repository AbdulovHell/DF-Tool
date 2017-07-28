#pragma once

#define SINGLE 1
#define EMBARK 2

namespace DFTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ mainform
	/// </summary>
	public ref class mainform : public System::Windows::Forms::Form
	{
	public:
		mainform(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~mainform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  CnctBtn;
	protected:
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Button^  TimeWarpEnBtn;
	private: System::Windows::Forms::Button^  TimeWarpSetMultBtn;
	private: System::Windows::Forms::TextBox^  TimeWarpMultEd;
	private: System::Windows::Forms::GroupBox^  TimeWarpControls;
	private: System::Windows::Forms::Button^  OpenDwarfEditorBtn;
	private: System::Windows::Forms::Button^  SetEmbarkPtBtn;
	private: System::Windows::Forms::TextBox^  EmbarkPointsEd;

	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::Timer^  CheckStatTmr;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  SetWinterBtn;
	private: System::Windows::Forms::Button^  SetSummerBtn;
	private: System::Windows::Forms::Button^  SetAutumnBtn;
	private: System::Windows::Forms::Button^  SetSpringBtn;
	private: System::Windows::Forms::Button^  SetEndSeasonBtn;
	private: System::Windows::Forms::Button^  SetMidSeasonBtn;
	private: System::Windows::Forms::Button^  SetBeginningSeasonBtn;
	private: System::Windows::Forms::CheckedListBox^  DebugFeatures;
	private: System::Windows::Forms::TextBox^  StartDwarfEd;
	private: System::Windows::Forms::Button^  SetStartDwarfBtn;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  SelCreatureName;
	private: System::Windows::Forms::CheckBox^  SlaughtFlag;
	private: System::Windows::Forms::Button^  EditCreatureBtn;
	private: System::Windows::Forms::Button^  CancelJobBtn;
	private: System::Windows::Forms::Button^  KillUnitBtn;
	private: System::Windows::Forms::Button^  HealUnitBtn;


	private: System::Windows::Forms::ToolStripStatusLabel^  infoLabel;
	private: System::Windows::Forms::TextBox^  SPEdit;
	private: System::Windows::Forms::TextBox^  APEdit;
	private: System::Windows::Forms::Button^  SetAllSkillsAt5Btn;

	private: System::Windows::Forms::ComboBox^  AllAttrSet;
	private: System::Windows::Forms::Button^  SetSPBtn;
	private: System::Windows::Forms::Button^  SetAPBtn;
	private: System::Windows::Forms::ListBox^  RaceList;
	private: System::Windows::Forms::NumericUpDown^  RaceValue;
	private: System::Windows::Forms::Button^  SetRaceBtn;
	private: System::Windows::Forms::GroupBox^  LocalCoordGrp;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  SetCoordBtn;

	private: System::Windows::Forms::NumericUpDown^  ZCoordEd;

	private: System::Windows::Forms::NumericUpDown^  YCoordEd;

	private: System::Windows::Forms::NumericUpDown^  XCoordEd;

	private: System::Windows::Forms::Button^  CopyCoordBtn;
	private: System::Windows::Forms::TextBox^  CurZCoord;

	private: System::Windows::Forms::TextBox^  CurYCoord;

	private: System::Windows::Forms::TextBox^  CurXCoord;
	private: System::Windows::Forms::Button^  HealAdvBtn;
	private: System::Windows::Forms::NumericUpDown^  SkipIntValue;
	private: System::Windows::Forms::CheckBox^  SkipTurnCkh;
	private: System::Windows::Forms::CheckBox^  IntsMaxSpdChk;
	private: System::Windows::Forms::Timer^  DecSpam;
	private: System::Windows::Forms::Button^  InvEditStartBtn;



	private: System::Windows::Forms::OpenFileDialog^  openINI;
	public:
		ref class MemoryLayout {
		private:
			size_t length;
			char* buffer;
			bool loaded = false;
		public:
			MemoryLayout(const char* Dest);
			bool isLoaded();
			uint64_t GetAddrByName(char* name);
		};

		static HANDLE GetDFHandle() {
			return hDF;
		}
		static HWND GetDFHwnd() {
			return hDFWnd;
		}
		static uint64_t GetDFStartAddr() {
			return DFStartAddr;
		}
		static MemoryLayout^ GetMemLayout() {
			return ml;
		}
		static uint32_t GetDwarfCount() {
			uint32_t dwarfs = 7;
			uint64_t StartDwarfCountAddr = DFStartAddr + ml->GetAddrByName("start_dwarf");
			ReadProcessMemory(hDF, (void*)StartDwarfCountAddr, &dwarfs, 4, NULL);
			return dwarfs;
		}
		static void GetFullName(char *buf, uint32_t len, int i, uint64_t vect);
	private:
		enum class ProgState : int {
			STATE_MAIN = 3,
			STATE_FORT = 0,
			STATE_ADV = 1,
			STATE_START = 0xFF,
			STATE_DISCON = 0xFF - 1,
			STATE_IDLE = 0xFF - 2
		};
		static char* fix_name(char* name);
		void OpenDF();
		void InitTimeWarp();
		void EnableTimeWarp();
		void InitDebugFunction();
		int InitStartDwarf();
		void UpdateSelectedUnitInfo();
		int SetAttPoints(int num, bool mode);
		int SetSkillPoints(int num, bool mode);
		void UpdateCoordinates(bool mode, short X, short Y, short Z);
		void HealUnit(int unit);
		void UpdateSpeed();
		String^ InHex(uint64_t addr);
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		ProgState progSt;
		bool adv_first = true;
		static MemoryLayout^ ml;
		static HANDLE hDF;
		static HWND hDFWnd;
		static uint64_t DFStartAddr;
		uint64_t TimeWarpMultAddr;
		uint64_t PauseStateAddr;
		uint64_t SeasonAddr;
		uint64_t SeasonTickAddr;
		uint64_t StateAddr;
		List<uint64_t> DebugFuncAddr;
	private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
			 /// содержимое этого метода с помощью редактора кода.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->openINI = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->CnctBtn = (gcnew System::Windows::Forms::Button());
				 this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				 this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->SetEmbarkPtBtn = (gcnew System::Windows::Forms::Button());
				 this->EmbarkPointsEd = (gcnew System::Windows::Forms::TextBox());
				 this->OpenDwarfEditorBtn = (gcnew System::Windows::Forms::Button());
				 this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->KillUnitBtn = (gcnew System::Windows::Forms::Button());
				 this->HealUnitBtn = (gcnew System::Windows::Forms::Button());
				 this->CancelJobBtn = (gcnew System::Windows::Forms::Button());
				 this->EditCreatureBtn = (gcnew System::Windows::Forms::Button());
				 this->SlaughtFlag = (gcnew System::Windows::Forms::CheckBox());
				 this->SelCreatureName = (gcnew System::Windows::Forms::Label());
				 this->DebugFeatures = (gcnew System::Windows::Forms::CheckedListBox());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->SetEndSeasonBtn = (gcnew System::Windows::Forms::Button());
				 this->SetMidSeasonBtn = (gcnew System::Windows::Forms::Button());
				 this->SetBeginningSeasonBtn = (gcnew System::Windows::Forms::Button());
				 this->SetWinterBtn = (gcnew System::Windows::Forms::Button());
				 this->SetSummerBtn = (gcnew System::Windows::Forms::Button());
				 this->SetAutumnBtn = (gcnew System::Windows::Forms::Button());
				 this->SetSpringBtn = (gcnew System::Windows::Forms::Button());
				 this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
				 this->RaceList = (gcnew System::Windows::Forms::ListBox());
				 this->RaceValue = (gcnew System::Windows::Forms::NumericUpDown());
				 this->SetRaceBtn = (gcnew System::Windows::Forms::Button());
				 this->SPEdit = (gcnew System::Windows::Forms::TextBox());
				 this->APEdit = (gcnew System::Windows::Forms::TextBox());
				 this->SetAllSkillsAt5Btn = (gcnew System::Windows::Forms::Button());
				 this->AllAttrSet = (gcnew System::Windows::Forms::ComboBox());
				 this->SetSPBtn = (gcnew System::Windows::Forms::Button());
				 this->SetAPBtn = (gcnew System::Windows::Forms::Button());
				 this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
				 this->InvEditStartBtn = (gcnew System::Windows::Forms::Button());
				 this->HealAdvBtn = (gcnew System::Windows::Forms::Button());
				 this->SkipIntValue = (gcnew System::Windows::Forms::NumericUpDown());
				 this->SkipTurnCkh = (gcnew System::Windows::Forms::CheckBox());
				 this->IntsMaxSpdChk = (gcnew System::Windows::Forms::CheckBox());
				 this->LocalCoordGrp = (gcnew System::Windows::Forms::GroupBox());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->SetCoordBtn = (gcnew System::Windows::Forms::Button());
				 this->ZCoordEd = (gcnew System::Windows::Forms::NumericUpDown());
				 this->YCoordEd = (gcnew System::Windows::Forms::NumericUpDown());
				 this->XCoordEd = (gcnew System::Windows::Forms::NumericUpDown());
				 this->CopyCoordBtn = (gcnew System::Windows::Forms::Button());
				 this->CurZCoord = (gcnew System::Windows::Forms::TextBox());
				 this->CurYCoord = (gcnew System::Windows::Forms::TextBox());
				 this->CurXCoord = (gcnew System::Windows::Forms::TextBox());
				 this->TimeWarpEnBtn = (gcnew System::Windows::Forms::Button());
				 this->TimeWarpSetMultBtn = (gcnew System::Windows::Forms::Button());
				 this->TimeWarpMultEd = (gcnew System::Windows::Forms::TextBox());
				 this->TimeWarpControls = (gcnew System::Windows::Forms::GroupBox());
				 this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
				 this->infoLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				 this->CheckStatTmr = (gcnew System::Windows::Forms::Timer(this->components));
				 this->StartDwarfEd = (gcnew System::Windows::Forms::TextBox());
				 this->SetStartDwarfBtn = (gcnew System::Windows::Forms::Button());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->DecSpam = (gcnew System::Windows::Forms::Timer(this->components));
				 this->tabControl1->SuspendLayout();
				 this->tabPage1->SuspendLayout();
				 this->tabPage2->SuspendLayout();
				 this->groupBox2->SuspendLayout();
				 this->groupBox1->SuspendLayout();
				 this->tabPage3->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RaceValue))->BeginInit();
				 this->tabPage4->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SkipIntValue))->BeginInit();
				 this->LocalCoordGrp->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ZCoordEd))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YCoordEd))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XCoordEd))->BeginInit();
				 this->TimeWarpControls->SuspendLayout();
				 this->statusStrip1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // CnctBtn
				 // 
				 this->CnctBtn->Location = System::Drawing::Point(12, 12);
				 this->CnctBtn->Name = L"CnctBtn";
				 this->CnctBtn->Size = System::Drawing::Size(75, 49);
				 this->CnctBtn->TabIndex = 0;
				 this->CnctBtn->Text = L"Connect";
				 this->CnctBtn->UseVisualStyleBackColor = true;
				 this->CnctBtn->Click += gcnew System::EventHandler(this, &mainform::CnctBtn_Click);
				 // 
				 // tabControl1
				 // 
				 this->tabControl1->Controls->Add(this->tabPage1);
				 this->tabControl1->Controls->Add(this->tabPage2);
				 this->tabControl1->Controls->Add(this->tabPage3);
				 this->tabControl1->Controls->Add(this->tabPage4);
				 this->tabControl1->Location = System::Drawing::Point(12, 122);
				 this->tabControl1->Name = L"tabControl1";
				 this->tabControl1->SelectedIndex = 0;
				 this->tabControl1->Size = System::Drawing::Size(324, 373);
				 this->tabControl1->TabIndex = 1;
				 // 
				 // tabPage1
				 // 
				 this->tabPage1->Controls->Add(this->label1);
				 this->tabPage1->Controls->Add(this->SetEmbarkPtBtn);
				 this->tabPage1->Controls->Add(this->EmbarkPointsEd);
				 this->tabPage1->Controls->Add(this->OpenDwarfEditorBtn);
				 this->tabPage1->Location = System::Drawing::Point(4, 22);
				 this->tabPage1->Name = L"tabPage1";
				 this->tabPage1->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage1->Size = System::Drawing::Size(316, 347);
				 this->tabPage1->TabIndex = 0;
				 this->tabPage1->Text = L"Embark";
				 this->tabPage1->UseVisualStyleBackColor = true;
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(3, 9);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(77, 13);
				 this->label1->TabIndex = 3;
				 this->label1->Text = L"Embark points:";
				 // 
				 // SetEmbarkPtBtn
				 // 
				 this->SetEmbarkPtBtn->Location = System::Drawing::Point(235, 6);
				 this->SetEmbarkPtBtn->Name = L"SetEmbarkPtBtn";
				 this->SetEmbarkPtBtn->Size = System::Drawing::Size(75, 21);
				 this->SetEmbarkPtBtn->TabIndex = 2;
				 this->SetEmbarkPtBtn->Text = L"Set";
				 this->SetEmbarkPtBtn->UseVisualStyleBackColor = true;
				 this->SetEmbarkPtBtn->Click += gcnew System::EventHandler(this, &mainform::SetEmbarkPtBtn_Click);
				 // 
				 // EmbarkPointsEd
				 // 
				 this->EmbarkPointsEd->Location = System::Drawing::Point(83, 6);
				 this->EmbarkPointsEd->Name = L"EmbarkPointsEd";
				 this->EmbarkPointsEd->Size = System::Drawing::Size(146, 20);
				 this->EmbarkPointsEd->TabIndex = 1;
				 // 
				 // OpenDwarfEditorBtn
				 // 
				 this->OpenDwarfEditorBtn->Location = System::Drawing::Point(6, 32);
				 this->OpenDwarfEditorBtn->Name = L"OpenDwarfEditorBtn";
				 this->OpenDwarfEditorBtn->Size = System::Drawing::Size(304, 21);
				 this->OpenDwarfEditorBtn->TabIndex = 0;
				 this->OpenDwarfEditorBtn->Text = L"Dwarfs editor";
				 this->OpenDwarfEditorBtn->UseVisualStyleBackColor = true;
				 this->OpenDwarfEditorBtn->Click += gcnew System::EventHandler(this, &mainform::button1_Click);
				 // 
				 // tabPage2
				 // 
				 this->tabPage2->Controls->Add(this->groupBox2);
				 this->tabPage2->Controls->Add(this->DebugFeatures);
				 this->tabPage2->Controls->Add(this->groupBox1);
				 this->tabPage2->Location = System::Drawing::Point(4, 22);
				 this->tabPage2->Name = L"tabPage2";
				 this->tabPage2->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage2->Size = System::Drawing::Size(316, 347);
				 this->tabPage2->TabIndex = 1;
				 this->tabPage2->Text = L"Fortress";
				 this->tabPage2->UseVisualStyleBackColor = true;
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->Controls->Add(this->KillUnitBtn);
				 this->groupBox2->Controls->Add(this->HealUnitBtn);
				 this->groupBox2->Controls->Add(this->CancelJobBtn);
				 this->groupBox2->Controls->Add(this->EditCreatureBtn);
				 this->groupBox2->Controls->Add(this->SlaughtFlag);
				 this->groupBox2->Controls->Add(this->SelCreatureName);
				 this->groupBox2->Location = System::Drawing::Point(6, 148);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(304, 78);
				 this->groupBox2->TabIndex = 2;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"Selected creature in \'v\' mode";
				 // 
				 // KillUnitBtn
				 // 
				 this->KillUnitBtn->Location = System::Drawing::Point(223, 48);
				 this->KillUnitBtn->Name = L"KillUnitBtn";
				 this->KillUnitBtn->Size = System::Drawing::Size(75, 23);
				 this->KillUnitBtn->TabIndex = 5;
				 this->KillUnitBtn->Text = L"Kill unit";
				 this->KillUnitBtn->UseVisualStyleBackColor = true;
				 this->KillUnitBtn->Click += gcnew System::EventHandler(this, &mainform::KillUnitBtn_Click);
				 // 
				 // HealUnitBtn
				 // 
				 this->HealUnitBtn->Location = System::Drawing::Point(223, 19);
				 this->HealUnitBtn->Name = L"HealUnitBtn";
				 this->HealUnitBtn->Size = System::Drawing::Size(75, 23);
				 this->HealUnitBtn->TabIndex = 4;
				 this->HealUnitBtn->Text = L"Heal unit";
				 this->HealUnitBtn->UseVisualStyleBackColor = true;
				 this->HealUnitBtn->Click += gcnew System::EventHandler(this, &mainform::HealUnitBtn_Click);
				 // 
				 // CancelJobBtn
				 // 
				 this->CancelJobBtn->Location = System::Drawing::Point(142, 48);
				 this->CancelJobBtn->Name = L"CancelJobBtn";
				 this->CancelJobBtn->Size = System::Drawing::Size(75, 23);
				 this->CancelJobBtn->TabIndex = 3;
				 this->CancelJobBtn->Text = L"Cancel Job";
				 this->CancelJobBtn->UseVisualStyleBackColor = true;
				 this->CancelJobBtn->Click += gcnew System::EventHandler(this, &mainform::CancelJobBtn_Click);
				 // 
				 // EditCreatureBtn
				 // 
				 this->EditCreatureBtn->Location = System::Drawing::Point(142, 19);
				 this->EditCreatureBtn->Name = L"EditCreatureBtn";
				 this->EditCreatureBtn->Size = System::Drawing::Size(75, 23);
				 this->EditCreatureBtn->TabIndex = 2;
				 this->EditCreatureBtn->Text = L"Edit";
				 this->EditCreatureBtn->UseVisualStyleBackColor = true;
				 this->EditCreatureBtn->Click += gcnew System::EventHandler(this, &mainform::EditCreatureBtn_Click);
				 // 
				 // SlaughtFlag
				 // 
				 this->SlaughtFlag->AutoSize = true;
				 this->SlaughtFlag->Location = System::Drawing::Point(9, 45);
				 this->SlaughtFlag->Name = L"SlaughtFlag";
				 this->SlaughtFlag->Size = System::Drawing::Size(62, 17);
				 this->SlaughtFlag->TabIndex = 1;
				 this->SlaughtFlag->Text = L"Slaught";
				 this->SlaughtFlag->UseVisualStyleBackColor = true;
				 this->SlaughtFlag->CheckedChanged += gcnew System::EventHandler(this, &mainform::SlaughtFlag_CheckedChanged);
				 // 
				 // SelCreatureName
				 // 
				 this->SelCreatureName->AutoSize = true;
				 this->SelCreatureName->Location = System::Drawing::Point(6, 24);
				 this->SelCreatureName->Name = L"SelCreatureName";
				 this->SelCreatureName->Size = System::Drawing::Size(75, 13);
				 this->SelCreatureName->TabIndex = 0;
				 this->SelCreatureName->Text = L"CreatureName";
				 // 
				 // DebugFeatures
				 // 
				 this->DebugFeatures->CheckOnClick = true;
				 this->DebugFeatures->FormattingEnabled = true;
				 this->DebugFeatures->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
					 L"No Pause", L"No Moods", L"No Drink", L"No Eat",
						 L"No Sleep", L"No Berserk", L"Fast Mining", L"Turbo Speed"
				 });
				 this->DebugFeatures->Location = System::Drawing::Point(164, 12);
				 this->DebugFeatures->Name = L"DebugFeatures";
				 this->DebugFeatures->Size = System::Drawing::Size(146, 124);
				 this->DebugFeatures->TabIndex = 1;
				 this->DebugFeatures->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &mainform::DebugFeatures_ItemCheck);
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->SetEndSeasonBtn);
				 this->groupBox1->Controls->Add(this->SetMidSeasonBtn);
				 this->groupBox1->Controls->Add(this->SetBeginningSeasonBtn);
				 this->groupBox1->Controls->Add(this->SetWinterBtn);
				 this->groupBox1->Controls->Add(this->SetSummerBtn);
				 this->groupBox1->Controls->Add(this->SetAutumnBtn);
				 this->groupBox1->Controls->Add(this->SetSpringBtn);
				 this->groupBox1->Location = System::Drawing::Point(6, 6);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(152, 136);
				 this->groupBox1->TabIndex = 0;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Season";
				 // 
				 // SetEndSeasonBtn
				 // 
				 this->SetEndSeasonBtn->Location = System::Drawing::Point(71, 91);
				 this->SetEndSeasonBtn->Name = L"SetEndSeasonBtn";
				 this->SetEndSeasonBtn->Size = System::Drawing::Size(75, 23);
				 this->SetEndSeasonBtn->TabIndex = 3;
				 this->SetEndSeasonBtn->Text = L"Late";
				 this->SetEndSeasonBtn->UseVisualStyleBackColor = true;
				 this->SetEndSeasonBtn->Click += gcnew System::EventHandler(this, &mainform::SetEndSeasonBtn_Click);
				 // 
				 // SetMidSeasonBtn
				 // 
				 this->SetMidSeasonBtn->Location = System::Drawing::Point(71, 62);
				 this->SetMidSeasonBtn->Name = L"SetMidSeasonBtn";
				 this->SetMidSeasonBtn->Size = System::Drawing::Size(75, 23);
				 this->SetMidSeasonBtn->TabIndex = 2;
				 this->SetMidSeasonBtn->Text = L"Mid";
				 this->SetMidSeasonBtn->UseVisualStyleBackColor = true;
				 this->SetMidSeasonBtn->Click += gcnew System::EventHandler(this, &mainform::SetMidSeasonBtn_Click);
				 // 
				 // SetBeginningSeasonBtn
				 // 
				 this->SetBeginningSeasonBtn->Location = System::Drawing::Point(71, 33);
				 this->SetBeginningSeasonBtn->Name = L"SetBeginningSeasonBtn";
				 this->SetBeginningSeasonBtn->Size = System::Drawing::Size(75, 23);
				 this->SetBeginningSeasonBtn->TabIndex = 1;
				 this->SetBeginningSeasonBtn->Text = L"Early";
				 this->SetBeginningSeasonBtn->UseVisualStyleBackColor = true;
				 this->SetBeginningSeasonBtn->Click += gcnew System::EventHandler(this, &mainform::SetBeginningSeasonBtn_Click);
				 // 
				 // SetWinterBtn
				 // 
				 this->SetWinterBtn->Location = System::Drawing::Point(6, 106);
				 this->SetWinterBtn->Name = L"SetWinterBtn";
				 this->SetWinterBtn->Size = System::Drawing::Size(59, 23);
				 this->SetWinterBtn->TabIndex = 0;
				 this->SetWinterBtn->Text = L"Winter";
				 this->SetWinterBtn->UseVisualStyleBackColor = true;
				 this->SetWinterBtn->Click += gcnew System::EventHandler(this, &mainform::SetWinterBtn_Click);
				 // 
				 // SetSummerBtn
				 // 
				 this->SetSummerBtn->Location = System::Drawing::Point(6, 77);
				 this->SetSummerBtn->Name = L"SetSummerBtn";
				 this->SetSummerBtn->Size = System::Drawing::Size(59, 23);
				 this->SetSummerBtn->TabIndex = 0;
				 this->SetSummerBtn->Text = L"Summer";
				 this->SetSummerBtn->UseVisualStyleBackColor = true;
				 this->SetSummerBtn->Click += gcnew System::EventHandler(this, &mainform::SetSummerBtn_Click);
				 // 
				 // SetAutumnBtn
				 // 
				 this->SetAutumnBtn->Location = System::Drawing::Point(6, 48);
				 this->SetAutumnBtn->Name = L"SetAutumnBtn";
				 this->SetAutumnBtn->Size = System::Drawing::Size(59, 23);
				 this->SetAutumnBtn->TabIndex = 0;
				 this->SetAutumnBtn->Text = L"Autumn";
				 this->SetAutumnBtn->UseVisualStyleBackColor = true;
				 this->SetAutumnBtn->Click += gcnew System::EventHandler(this, &mainform::SetAutumnBtn_Click);
				 // 
				 // SetSpringBtn
				 // 
				 this->SetSpringBtn->Location = System::Drawing::Point(6, 19);
				 this->SetSpringBtn->Name = L"SetSpringBtn";
				 this->SetSpringBtn->Size = System::Drawing::Size(59, 23);
				 this->SetSpringBtn->TabIndex = 0;
				 this->SetSpringBtn->Text = L"Spring";
				 this->SetSpringBtn->UseVisualStyleBackColor = true;
				 this->SetSpringBtn->Click += gcnew System::EventHandler(this, &mainform::SetSpringBtn_Click);
				 // 
				 // tabPage3
				 // 
				 this->tabPage3->Controls->Add(this->RaceList);
				 this->tabPage3->Controls->Add(this->RaceValue);
				 this->tabPage3->Controls->Add(this->SetRaceBtn);
				 this->tabPage3->Controls->Add(this->SPEdit);
				 this->tabPage3->Controls->Add(this->APEdit);
				 this->tabPage3->Controls->Add(this->SetAllSkillsAt5Btn);
				 this->tabPage3->Controls->Add(this->AllAttrSet);
				 this->tabPage3->Controls->Add(this->SetSPBtn);
				 this->tabPage3->Controls->Add(this->SetAPBtn);
				 this->tabPage3->Location = System::Drawing::Point(4, 22);
				 this->tabPage3->Name = L"tabPage3";
				 this->tabPage3->Size = System::Drawing::Size(316, 347);
				 this->tabPage3->TabIndex = 2;
				 this->tabPage3->Text = L"Creating Character";
				 this->tabPage3->UseVisualStyleBackColor = true;
				 // 
				 // RaceList
				 // 
				 this->RaceList->FormattingEnabled = true;
				 this->RaceList->Items->AddRange(gcnew cli::array< System::Object^  >(17) {
					 L"572 - dwarf", L"573 - human", L"574 - elf", L"575 - goblin",
						 L"576 - cobold", L"577 - gremlin", L"578 - troll", L"579 - ogre", L"580 - unicorn", L"581 - dragon", L"582 - satyr", L"583 - bronze colossus",
						 L"584 - gigant", L"585 - cyclop", L"586 - ettin", L"587 - minotaur", L"588 - yeti"
				 });
				 this->RaceList->Location = System::Drawing::Point(190, 62);
				 this->RaceList->Name = L"RaceList";
				 this->RaceList->Size = System::Drawing::Size(120, 173);
				 this->RaceList->TabIndex = 11;
				 this->RaceList->SelectedIndexChanged += gcnew System::EventHandler(this, &mainform::RaceList_SelectedIndexChanged);
				 // 
				 // RaceValue
				 // 
				 this->RaceValue->Location = System::Drawing::Point(190, 35);
				 this->RaceValue->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 832, 0, 0, 0 });
				 this->RaceValue->Name = L"RaceValue";
				 this->RaceValue->Size = System::Drawing::Size(120, 20);
				 this->RaceValue->TabIndex = 10;
				 this->RaceValue->ValueChanged += gcnew System::EventHandler(this, &mainform::RaceValue_ValueChanged);
				 // 
				 // SetRaceBtn
				 // 
				 this->SetRaceBtn->Location = System::Drawing::Point(190, 6);
				 this->SetRaceBtn->Name = L"SetRaceBtn";
				 this->SetRaceBtn->Size = System::Drawing::Size(120, 23);
				 this->SetRaceBtn->TabIndex = 8;
				 this->SetRaceBtn->Text = L"Set race";
				 this->SetRaceBtn->UseVisualStyleBackColor = true;
				 this->SetRaceBtn->Click += gcnew System::EventHandler(this, &mainform::SetRaceBtn_Click);
				 // 
				 // SPEdit
				 // 
				 this->SPEdit->Location = System::Drawing::Point(116, 34);
				 this->SPEdit->Name = L"SPEdit";
				 this->SPEdit->Size = System::Drawing::Size(67, 20);
				 this->SPEdit->TabIndex = 7;
				 // 
				 // APEdit
				 // 
				 this->APEdit->Location = System::Drawing::Point(116, 6);
				 this->APEdit->Name = L"APEdit";
				 this->APEdit->Size = System::Drawing::Size(67, 20);
				 this->APEdit->TabIndex = 6;
				 // 
				 // SetAllSkillsAt5Btn
				 // 
				 this->SetAllSkillsAt5Btn->Location = System::Drawing::Point(3, 87);
				 this->SetAllSkillsAt5Btn->Name = L"SetAllSkillsAt5Btn";
				 this->SetAllSkillsAt5Btn->Size = System::Drawing::Size(180, 23);
				 this->SetAllSkillsAt5Btn->TabIndex = 5;
				 this->SetAllSkillsAt5Btn->Text = L"Set all skills at L+5";
				 this->SetAllSkillsAt5Btn->UseVisualStyleBackColor = true;
				 this->SetAllSkillsAt5Btn->Click += gcnew System::EventHandler(this, &mainform::SetAllSkillsAt5Btn_Click);
				 // 
				 // AllAttrSet
				 // 
				 this->AllAttrSet->FormattingEnabled = true;
				 this->AllAttrSet->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
					 L"Very Low", L"Low", L"Below", L"Average", L"Above Average",
						 L"High", L"Superior"
				 });
				 this->AllAttrSet->Location = System::Drawing::Point(3, 60);
				 this->AllAttrSet->Name = L"AllAttrSet";
				 this->AllAttrSet->Size = System::Drawing::Size(180, 21);
				 this->AllAttrSet->TabIndex = 3;
				 this->AllAttrSet->SelectedIndexChanged += gcnew System::EventHandler(this, &mainform::AllAttrSet_SelectedIndexChanged);
				 // 
				 // SetSPBtn
				 // 
				 this->SetSPBtn->Location = System::Drawing::Point(3, 33);
				 this->SetSPBtn->Name = L"SetSPBtn";
				 this->SetSPBtn->Size = System::Drawing::Size(107, 21);
				 this->SetSPBtn->TabIndex = 1;
				 this->SetSPBtn->Text = L"Set Skill points";
				 this->SetSPBtn->UseVisualStyleBackColor = true;
				 this->SetSPBtn->Click += gcnew System::EventHandler(this, &mainform::SetSPBtn_Click);
				 // 
				 // SetAPBtn
				 // 
				 this->SetAPBtn->Location = System::Drawing::Point(3, 6);
				 this->SetAPBtn->Name = L"SetAPBtn";
				 this->SetAPBtn->Size = System::Drawing::Size(107, 21);
				 this->SetAPBtn->TabIndex = 0;
				 this->SetAPBtn->Text = L"Set Attribute points";
				 this->SetAPBtn->UseVisualStyleBackColor = true;
				 this->SetAPBtn->Click += gcnew System::EventHandler(this, &mainform::SetAPBtn_Click);
				 // 
				 // tabPage4
				 // 
				 this->tabPage4->Controls->Add(this->InvEditStartBtn);
				 this->tabPage4->Controls->Add(this->HealAdvBtn);
				 this->tabPage4->Controls->Add(this->SkipIntValue);
				 this->tabPage4->Controls->Add(this->SkipTurnCkh);
				 this->tabPage4->Controls->Add(this->IntsMaxSpdChk);
				 this->tabPage4->Controls->Add(this->LocalCoordGrp);
				 this->tabPage4->Location = System::Drawing::Point(4, 22);
				 this->tabPage4->Name = L"tabPage4";
				 this->tabPage4->Size = System::Drawing::Size(316, 347);
				 this->tabPage4->TabIndex = 3;
				 this->tabPage4->Text = L"Adventurer";
				 this->tabPage4->UseVisualStyleBackColor = true;
				 // 
				 // InvEditStartBtn
				 // 
				 this->InvEditStartBtn->Location = System::Drawing::Point(92, 172);
				 this->InvEditStartBtn->Name = L"InvEditStartBtn";
				 this->InvEditStartBtn->Size = System::Drawing::Size(95, 23);
				 this->InvEditStartBtn->TabIndex = 5;
				 this->InvEditStartBtn->Text = L"Inventory Editor";
				 this->InvEditStartBtn->UseVisualStyleBackColor = true;
				 this->InvEditStartBtn->Click += gcnew System::EventHandler(this, &mainform::InvEditStartBtn_Click);
				 // 
				 // HealAdvBtn
				 // 
				 this->HealAdvBtn->Location = System::Drawing::Point(7, 172);
				 this->HealAdvBtn->Name = L"HealAdvBtn";
				 this->HealAdvBtn->Size = System::Drawing::Size(75, 23);
				 this->HealAdvBtn->TabIndex = 4;
				 this->HealAdvBtn->Text = L"Heal";
				 this->HealAdvBtn->UseVisualStyleBackColor = true;
				 this->HealAdvBtn->Click += gcnew System::EventHandler(this, &mainform::HealAdvBtn_Click);
				 // 
				 // SkipIntValue
				 // 
				 this->SkipIntValue->Location = System::Drawing::Point(131, 139);
				 this->SkipIntValue->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
				 this->SkipIntValue->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->SkipIntValue->Name = L"SkipIntValue";
				 this->SkipIntValue->Size = System::Drawing::Size(79, 20);
				 this->SkipIntValue->TabIndex = 3;
				 this->SkipIntValue->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 // 
				 // SkipTurnCkh
				 // 
				 this->SkipTurnCkh->AutoSize = true;
				 this->SkipTurnCkh->Location = System::Drawing::Point(3, 140);
				 this->SkipTurnCkh->Name = L"SkipTurnCkh";
				 this->SkipTurnCkh->Size = System::Drawing::Size(131, 17);
				 this->SkipTurnCkh->TabIndex = 2;
				 this->SkipTurnCkh->Text = L"Skip turn. Interval, ms:";
				 this->SkipTurnCkh->UseVisualStyleBackColor = true;
				 this->SkipTurnCkh->CheckedChanged += gcnew System::EventHandler(this, &mainform::SkipTurnCkh_CheckedChanged);
				 // 
				 // IntsMaxSpdChk
				 // 
				 this->IntsMaxSpdChk->AutoSize = true;
				 this->IntsMaxSpdChk->Location = System::Drawing::Point(3, 110);
				 this->IntsMaxSpdChk->Name = L"IntsMaxSpdChk";
				 this->IntsMaxSpdChk->Size = System::Drawing::Size(149, 17);
				 this->IntsMaxSpdChk->TabIndex = 1;
				 this->IntsMaxSpdChk->Text = L"Instant max moving speed";
				 this->IntsMaxSpdChk->UseVisualStyleBackColor = true;
				 // 
				 // LocalCoordGrp
				 // 
				 this->LocalCoordGrp->Controls->Add(this->label5);
				 this->LocalCoordGrp->Controls->Add(this->label4);
				 this->LocalCoordGrp->Controls->Add(this->label3);
				 this->LocalCoordGrp->Controls->Add(this->SetCoordBtn);
				 this->LocalCoordGrp->Controls->Add(this->ZCoordEd);
				 this->LocalCoordGrp->Controls->Add(this->YCoordEd);
				 this->LocalCoordGrp->Controls->Add(this->XCoordEd);
				 this->LocalCoordGrp->Controls->Add(this->CopyCoordBtn);
				 this->LocalCoordGrp->Controls->Add(this->CurZCoord);
				 this->LocalCoordGrp->Controls->Add(this->CurYCoord);
				 this->LocalCoordGrp->Controls->Add(this->CurXCoord);
				 this->LocalCoordGrp->Location = System::Drawing::Point(3, 3);
				 this->LocalCoordGrp->Name = L"LocalCoordGrp";
				 this->LocalCoordGrp->Size = System::Drawing::Size(310, 98);
				 this->LocalCoordGrp->TabIndex = 0;
				 this->LocalCoordGrp->TabStop = false;
				 this->LocalCoordGrp->Text = L"Local coordinates";
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(185, 21);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(14, 13);
				 this->label5->TabIndex = 4;
				 this->label5->Text = L"Z";
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(125, 21);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(14, 13);
				 this->label4->TabIndex = 4;
				 this->label4->Text = L"Y";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(65, 21);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(14, 13);
				 this->label3->TabIndex = 4;
				 this->label3->Text = L"X";
				 // 
				 // SetCoordBtn
				 // 
				 this->SetCoordBtn->Location = System::Drawing::Point(225, 63);
				 this->SetCoordBtn->Name = L"SetCoordBtn";
				 this->SetCoordBtn->Size = System::Drawing::Size(47, 20);
				 this->SetCoordBtn->TabIndex = 3;
				 this->SetCoordBtn->Text = L"set";
				 this->SetCoordBtn->UseVisualStyleBackColor = true;
				 this->SetCoordBtn->Click += gcnew System::EventHandler(this, &mainform::SetCoordBtn_Click);
				 // 
				 // ZCoordEd
				 // 
				 this->ZCoordEd->Location = System::Drawing::Point(165, 63);
				 this->ZCoordEd->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				 this->ZCoordEd->Name = L"ZCoordEd";
				 this->ZCoordEd->Size = System::Drawing::Size(54, 20);
				 this->ZCoordEd->TabIndex = 2;
				 // 
				 // YCoordEd
				 // 
				 this->YCoordEd->Location = System::Drawing::Point(105, 63);
				 this->YCoordEd->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				 this->YCoordEd->Name = L"YCoordEd";
				 this->YCoordEd->Size = System::Drawing::Size(54, 20);
				 this->YCoordEd->TabIndex = 2;
				 // 
				 // XCoordEd
				 // 
				 this->XCoordEd->Location = System::Drawing::Point(45, 63);
				 this->XCoordEd->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				 this->XCoordEd->Name = L"XCoordEd";
				 this->XCoordEd->Size = System::Drawing::Size(54, 20);
				 this->XCoordEd->TabIndex = 2;
				 // 
				 // CopyCoordBtn
				 // 
				 this->CopyCoordBtn->Location = System::Drawing::Point(225, 37);
				 this->CopyCoordBtn->Name = L"CopyCoordBtn";
				 this->CopyCoordBtn->Size = System::Drawing::Size(47, 21);
				 this->CopyCoordBtn->TabIndex = 1;
				 this->CopyCoordBtn->Text = L"copy";
				 this->CopyCoordBtn->UseVisualStyleBackColor = true;
				 this->CopyCoordBtn->Click += gcnew System::EventHandler(this, &mainform::CopyCoordBtn_Click);
				 // 
				 // CurZCoord
				 // 
				 this->CurZCoord->Location = System::Drawing::Point(165, 37);
				 this->CurZCoord->Name = L"CurZCoord";
				 this->CurZCoord->ReadOnly = true;
				 this->CurZCoord->Size = System::Drawing::Size(54, 20);
				 this->CurZCoord->TabIndex = 0;
				 this->CurZCoord->Text = L"0";
				 this->CurZCoord->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->CurZCoord->Click += gcnew System::EventHandler(this, &mainform::CurZCoord_Click);
				 // 
				 // CurYCoord
				 // 
				 this->CurYCoord->Location = System::Drawing::Point(105, 37);
				 this->CurYCoord->Name = L"CurYCoord";
				 this->CurYCoord->ReadOnly = true;
				 this->CurYCoord->Size = System::Drawing::Size(54, 20);
				 this->CurYCoord->TabIndex = 0;
				 this->CurYCoord->Text = L"0";
				 this->CurYCoord->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->CurYCoord->Click += gcnew System::EventHandler(this, &mainform::CurYCoord_Click);
				 // 
				 // CurXCoord
				 // 
				 this->CurXCoord->Location = System::Drawing::Point(45, 37);
				 this->CurXCoord->Name = L"CurXCoord";
				 this->CurXCoord->ReadOnly = true;
				 this->CurXCoord->Size = System::Drawing::Size(54, 20);
				 this->CurXCoord->TabIndex = 0;
				 this->CurXCoord->Text = L"0";
				 this->CurXCoord->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->CurXCoord->Click += gcnew System::EventHandler(this, &mainform::CurXCoord_Click);
				 // 
				 // TimeWarpEnBtn
				 // 
				 this->TimeWarpEnBtn->Location = System::Drawing::Point(6, 19);
				 this->TimeWarpEnBtn->Name = L"TimeWarpEnBtn";
				 this->TimeWarpEnBtn->Size = System::Drawing::Size(75, 23);
				 this->TimeWarpEnBtn->TabIndex = 2;
				 this->TimeWarpEnBtn->Text = L"Enable";
				 this->TimeWarpEnBtn->UseVisualStyleBackColor = true;
				 this->TimeWarpEnBtn->Click += gcnew System::EventHandler(this, &mainform::TimeWarpEnBtn_Click);
				 // 
				 // TimeWarpSetMultBtn
				 // 
				 this->TimeWarpSetMultBtn->Enabled = false;
				 this->TimeWarpSetMultBtn->Location = System::Drawing::Point(161, 18);
				 this->TimeWarpSetMultBtn->Name = L"TimeWarpSetMultBtn";
				 this->TimeWarpSetMultBtn->Size = System::Drawing::Size(75, 23);
				 this->TimeWarpSetMultBtn->TabIndex = 3;
				 this->TimeWarpSetMultBtn->Text = L"Set multiplier";
				 this->TimeWarpSetMultBtn->UseVisualStyleBackColor = true;
				 this->TimeWarpSetMultBtn->Click += gcnew System::EventHandler(this, &mainform::TimeWarpSetMultBtn_Click);
				 // 
				 // TimeWarpMultEd
				 // 
				 this->TimeWarpMultEd->Enabled = false;
				 this->TimeWarpMultEd->Location = System::Drawing::Point(87, 21);
				 this->TimeWarpMultEd->Name = L"TimeWarpMultEd";
				 this->TimeWarpMultEd->Size = System::Drawing::Size(68, 20);
				 this->TimeWarpMultEd->TabIndex = 4;
				 this->TimeWarpMultEd->Text = L"1";
				 // 
				 // TimeWarpControls
				 // 
				 this->TimeWarpControls->Controls->Add(this->TimeWarpEnBtn);
				 this->TimeWarpControls->Controls->Add(this->TimeWarpSetMultBtn);
				 this->TimeWarpControls->Controls->Add(this->TimeWarpMultEd);
				 this->TimeWarpControls->Location = System::Drawing::Point(12, 67);
				 this->TimeWarpControls->Name = L"TimeWarpControls";
				 this->TimeWarpControls->Size = System::Drawing::Size(324, 49);
				 this->TimeWarpControls->TabIndex = 5;
				 this->TimeWarpControls->TabStop = false;
				 this->TimeWarpControls->Text = L"Time warp";
				 // 
				 // statusStrip1
				 // 
				 this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->infoLabel });
				 this->statusStrip1->Location = System::Drawing::Point(0, 498);
				 this->statusStrip1->Name = L"statusStrip1";
				 this->statusStrip1->Size = System::Drawing::Size(343, 22);
				 this->statusStrip1->SizingGrip = false;
				 this->statusStrip1->TabIndex = 6;
				 this->statusStrip1->Text = L"statusStrip1";
				 // 
				 // infoLabel
				 // 
				 this->infoLabel->Name = L"infoLabel";
				 this->infoLabel->Size = System::Drawing::Size(0, 17);
				 // 
				 // CheckStatTmr
				 // 
				 this->CheckStatTmr->Interval = 200;
				 this->CheckStatTmr->Tick += gcnew System::EventHandler(this, &mainform::CheckStatTmr_Tick);
				 // 
				 // StartDwarfEd
				 // 
				 this->StartDwarfEd->Location = System::Drawing::Point(189, 13);
				 this->StartDwarfEd->Name = L"StartDwarfEd";
				 this->StartDwarfEd->Size = System::Drawing::Size(100, 20);
				 this->StartDwarfEd->TabIndex = 7;
				 // 
				 // SetStartDwarfBtn
				 // 
				 this->SetStartDwarfBtn->Location = System::Drawing::Point(293, 13);
				 this->SetStartDwarfBtn->Name = L"SetStartDwarfBtn";
				 this->SetStartDwarfBtn->Size = System::Drawing::Size(43, 21);
				 this->SetStartDwarfBtn->TabIndex = 8;
				 this->SetStartDwarfBtn->Text = L"Set";
				 this->SetStartDwarfBtn->UseVisualStyleBackColor = true;
				 this->SetStartDwarfBtn->Click += gcnew System::EventHandler(this, &mainform::SetStartDwarfBtn_Click);
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(93, 16);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(90, 13);
				 this->label2->TabIndex = 9;
				 this->label2->Text = L"Start Dwarf count";
				 // 
				 // DecSpam
				 // 
				 this->DecSpam->Interval = 1;
				 this->DecSpam->Tick += gcnew System::EventHandler(this, &mainform::DecSpam_Tick);
				 // 
				 // mainform
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->AutoSize = true;
				 this->ClientSize = System::Drawing::Size(343, 520);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->SetStartDwarfBtn);
				 this->Controls->Add(this->StartDwarfEd);
				 this->Controls->Add(this->statusStrip1);
				 this->Controls->Add(this->TimeWarpControls);
				 this->Controls->Add(this->tabControl1);
				 this->Controls->Add(this->CnctBtn);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->Name = L"mainform";
				 this->Text = L"DFTool";
				 this->Load += gcnew System::EventHandler(this, &mainform::mainform_Load);
				 this->tabControl1->ResumeLayout(false);
				 this->tabPage1->ResumeLayout(false);
				 this->tabPage1->PerformLayout();
				 this->tabPage2->ResumeLayout(false);
				 this->groupBox2->ResumeLayout(false);
				 this->groupBox2->PerformLayout();
				 this->groupBox1->ResumeLayout(false);
				 this->tabPage3->ResumeLayout(false);
				 this->tabPage3->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RaceValue))->EndInit();
				 this->tabPage4->ResumeLayout(false);
				 this->tabPage4->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SkipIntValue))->EndInit();
				 this->LocalCoordGrp->ResumeLayout(false);
				 this->LocalCoordGrp->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ZCoordEd))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YCoordEd))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XCoordEd))->EndInit();
				 this->TimeWarpControls->ResumeLayout(false);
				 this->TimeWarpControls->PerformLayout();
				 this->statusStrip1->ResumeLayout(false);
				 this->statusStrip1->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void mainform_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TimeWarpSetMultBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TimeWarpEnBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CnctBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetEmbarkPtBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CheckStatTmr_Tick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetSpringBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetSummerBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetAutumnBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetWinterBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetBeginningSeasonBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetMidSeasonBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetEndSeasonBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DebugFeatures_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e);
	private: System::Void SetStartDwarfBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void EditCreatureBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SlaughtFlag_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CancelJobBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void KillUnitBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void HealUnitBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetAPBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetSPBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void AllAttrSet_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetAllSkillsAt5Btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetRaceBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void RaceValue_ValueChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void RaceList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CopyCoordBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SetCoordBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CurXCoord_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CurYCoord_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CurZCoord_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void HealAdvBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SkipTurnCkh_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void DecSpam_Tick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void InvEditStartBtn_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
