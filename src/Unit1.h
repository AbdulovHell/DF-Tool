//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TCheckBox *CheckBox1;
        TEdit *Edit1;
        TButton *Button2;
        TGroupBox *GroupBox1;
        TButton *Button4;
        TEdit *Edit3;
        TButton *Button5;
        TLabel *Label1;
        TButton *Button10;
        TEdit *Edit4;
        TButton *Button11;
        TButton *Button12;
        TGroupBox *GroupBox2;
        TButton *Button13;
        TButton *Button14;
        TButton *Button15;
        TButton *Button16;
        TButton *Button17;
        TButton *Button18;
        TButton *Button19;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TTimer *Timer1;
        TEdit *Edit5;
        TEdit *Edit6;
        TButton *Button21;
        TButton *Button22;
        TButton *Button23;
        TComboBox *ComboBox2;
        TButton *Button24;
        TButton *Button25;
        TButton *Button26;
        TButton *Button27;
        TEdit *Edit7;
        TButton *Button28;
        TListBox *ListBox1;
        TUpDown *UpDown1;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit10;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TButton *Button29;
        TMainMenu *MainMenu1;
        TMenuItem *Options1;
        TMenuItem *Exit1;
        TMenuItem *PrintSetup1;
        TMenuItem *About1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TCheckBox *CheckBox11;
        TMenuItem *Help;
        TMenuItem *Donate1;
        TMenuItem *ForumThread1;
        TButton *Button30;
        TUpDown *UpDown2;
        TUpDown *UpDown3;
        TUpDown *UpDown4;
        TGroupBox *GroupBox4;
        TTimer *DecimalRepeat;
        TEdit *Edit14;
        TUpDown *UpDown5;
        TLabel *Label2;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox6;
        TButton *Button32;
        TGroupBox *GroupBox7;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
        TCheckBox *CheckBox15;
        TCheckBox *CheckBox16;
        TComboBox *ComboBox3;
        TLabel *Label6;
        TCheckBox *CheckBox17;
        TCheckBox *CheckBox18;
        TCheckBox *CheckBox19;
        TCheckBox *CheckBox20;
        TCheckBox *CheckBox21;
        TCheckBox *CheckBox22;
        TCheckBox *CheckBox23;
        TCheckBox *CheckBox24;
        TButton *Button33;
        TLabel *Label7;
        TLabel *Label8;
        TGroupBox *GroupBox8;
        TLabel *Label9;
        TCheckBox *CheckBox25;
        TLabel *Label10;
        TButton *Button34;
	TOpenDialog *OpenDialog1;
	TLabel *Label11;
	TMenuItem *Loadini1;
	TButton *Button35;
	TCheckBox *CheckBox26;
	TButton *Button31;
	TButton *Button36;
	TButton *Button3;
        void __fastcall OpenDF(TObject *Sender);
        void __fastcall Change_Patch_state(TObject *Sender);
        void __fastcall Patch_StartDwarf(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall deb_func(TObject *Sender);
        void __fastcall Check_stat(TObject *Sender);
        void __fastcall Button21Click(TObject *Sender);
        void __fastcall Button22Click(TObject *Sender);
        void __fastcall Button23Click(TObject *Sender);
        void __fastcall Button24Click(TObject *Sender);
        void __fastcall Button27Click(TObject *Sender);
        void __fastcall Button28Click(TObject *Sender);
        void __fastcall Button29Click(TObject *Sender);
        void __fastcall setrace1(TObject *Sender, TUDBtnType Button);
        void __fastcall CopyCoords(TObject *Sender);
        void __fastcall MaxSpeedState(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall PrintSetup1Click(TObject *Sender);
        void __fastcall ForumThread1Click(TObject *Sender);
        void __fastcall Donate1Click(TObject *Sender);
        void __fastcall Button30Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall Skip(TObject *Sender);
        void __fastcall DecimalRepeatTimer(TObject *Sender);
        void __fastcall Change_d_init(TObject *Sender);
        void __fastcall Act_DeAct_mood_acc(TObject *Sender);
        void __fastcall Button33Click(TObject *Sender);
        void __fastcall Slaught_creature(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
		void __fastcall Cancel_job(TObject *Sender);
		void __fastcall OnKeyPress(TMessage &Message);
	void __fastcall Loadini1Click(TObject *Sender);
	void __fastcall Button35Click(TObject *Sender);
	void __fastcall Button36Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
		__fastcall TForm1(TComponent* Owner);
protected:
		BEGIN_MESSAGE_MAP
				MESSAGE_HANDLER(WM_HOTKEY, TMessage, OnKeyPress)
		END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
