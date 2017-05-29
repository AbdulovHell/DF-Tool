#pragma once

#define STATE_MAIN 3
#define STATE_FORT 0
#define STATE_ADV 1
#define STATE_START 0xFF
#define STATE_DISCON 0xFF-1
#define STATE_IDLE 0xFF-2

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
	private: System::Windows::Forms::OpenFileDialog^  openINI;
	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openINI = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// mainform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(770, 441);
			this->Name = L"mainform";
			this->Text = L"mainform";
			this->Load += gcnew System::EventHandler(this, &mainform::mainform_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void mainform_Load(System::Object^  sender, System::EventArgs^  e);
	};
}
