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
			//
			//TODO: добавьте код конструктора
			//
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
	private: System::Windows::Forms::TextBox^  textBox1;
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
			//uint64_t StartDwarfCountAddr = DFStartAddr + ml->GetAddrByName("start_dwarf");
			//ReadProcessMemory(hDF, (void*)StartDwarfCountAddr, &dwarfs, 4, NULL);
			return dwarfs;
		}
		static void GetFullName(char *buf, int i, uint64_t vect);
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
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		ProgState progSt;
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
		List<bool> DebugFeaturesLastState;
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
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->OpenDwarfEditorBtn = (gcnew System::Windows::Forms::Button());
				 this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
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
				 this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
				 this->TimeWarpEnBtn = (gcnew System::Windows::Forms::Button());
				 this->TimeWarpSetMultBtn = (gcnew System::Windows::Forms::Button());
				 this->TimeWarpMultEd = (gcnew System::Windows::Forms::TextBox());
				 this->TimeWarpControls = (gcnew System::Windows::Forms::GroupBox());
				 this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
				 this->CheckStatTmr = (gcnew System::Windows::Forms::Timer(this->components));
				 this->StartDwarfEd = (gcnew System::Windows::Forms::TextBox());
				 this->SetStartDwarfBtn = (gcnew System::Windows::Forms::Button());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->tabControl1->SuspendLayout();
				 this->tabPage1->SuspendLayout();
				 this->tabPage2->SuspendLayout();
				 this->groupBox1->SuspendLayout();
				 this->TimeWarpControls->SuspendLayout();
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
				 this->tabPage1->Controls->Add(this->textBox1);
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
				 // textBox1
				 // 
				 this->textBox1->Location = System::Drawing::Point(83, 6);
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(146, 20);
				 this->textBox1->TabIndex = 1;
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
				 this->tabPage3->Location = System::Drawing::Point(4, 22);
				 this->tabPage3->Name = L"tabPage3";
				 this->tabPage3->Size = System::Drawing::Size(316, 347);
				 this->tabPage3->TabIndex = 2;
				 this->tabPage3->Text = L"Creating Character";
				 this->tabPage3->UseVisualStyleBackColor = true;
				 // 
				 // tabPage4
				 // 
				 this->tabPage4->Location = System::Drawing::Point(4, 22);
				 this->tabPage4->Name = L"tabPage4";
				 this->tabPage4->Size = System::Drawing::Size(316, 347);
				 this->tabPage4->TabIndex = 3;
				 this->tabPage4->Text = L"Adventurer";
				 this->tabPage4->UseVisualStyleBackColor = true;
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
				 this->TimeWarpControls->Location = System::Drawing::Point(16, 67);
				 this->TimeWarpControls->Name = L"TimeWarpControls";
				 this->TimeWarpControls->Size = System::Drawing::Size(315, 49);
				 this->TimeWarpControls->TabIndex = 5;
				 this->TimeWarpControls->TabStop = false;
				 this->TimeWarpControls->Text = L"Time warp";
				 // 
				 // statusStrip1
				 // 
				 this->statusStrip1->Location = System::Drawing::Point(0, 498);
				 this->statusStrip1->Name = L"statusStrip1";
				 this->statusStrip1->Size = System::Drawing::Size(343, 22);
				 this->statusStrip1->SizingGrip = false;
				 this->statusStrip1->TabIndex = 6;
				 this->statusStrip1->Text = L"statusStrip1";
				 // 
				 // CheckStatTmr
				 // 
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
				 this->SetStartDwarfBtn->Size = System::Drawing::Size(39, 21);
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
				 this->groupBox1->ResumeLayout(false);
				 this->TimeWarpControls->ResumeLayout(false);
				 this->TimeWarpControls->PerformLayout();
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
};
}
