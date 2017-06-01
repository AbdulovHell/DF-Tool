#pragma once

#define SINGLE 1
#define EMBARK 2

namespace DFTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
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
	private: System::Windows::Forms::Button^  button1;

	private: System::Windows::Forms::OpenFileDialog^  openINI;
	protected:

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
		enum class ProgState : uint8_t {
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
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openINI = (gcnew System::Windows::Forms::OpenFileDialog());
			this->CnctBtn = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->TimeWarpEnBtn = (gcnew System::Windows::Forms::Button());
			this->TimeWarpSetMultBtn = (gcnew System::Windows::Forms::Button());
			this->TimeWarpMultEd = (gcnew System::Windows::Forms::TextBox());
			this->TimeWarpControls = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
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
			this->tabControl1->Location = System::Drawing::Point(12, 67);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(500, 294);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(492, 268);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(492, 268);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
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
			this->TimeWarpControls->Location = System::Drawing::Point(93, 12);
			this->TimeWarpControls->Name = L"TimeWarpControls";
			this->TimeWarpControls->Size = System::Drawing::Size(243, 49);
			this->TimeWarpControls->TabIndex = 5;
			this->TimeWarpControls->TabStop = false;
			this->TimeWarpControls->Text = L"Time warp";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(125, 111);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(230, 50);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Dwarfs editor";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &mainform::button1_Click);
			// 
			// mainform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(770, 441);
			this->Controls->Add(this->TimeWarpControls);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->CnctBtn);
			this->Name = L"mainform";
			this->Text = L"DFTool";
			this->Load += gcnew System::EventHandler(this, &mainform::mainform_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->TimeWarpControls->ResumeLayout(false);
			this->TimeWarpControls->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void mainform_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TimeWarpSetMultBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TimeWarpEnBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CnctBtn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
};
}
