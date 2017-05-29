//----------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//----------------------------------------------------------------------------
/*#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp> */
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <DBGrids.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
//----------------------------------------------------------------------------
class TOKBottomDlg1 : public TForm
{
__published:
        TEdit *Edit1;
        TEdit *Edit2;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TEdit *Edit7;
        TButton *Button8;
        TButton *Button9;
        TButton *Button10;
        TEdit *Edit8;
        TButton *Button11;
        TEdit *Edit9;
        TEdit *Edit10;
        TButton *Button12;
        TEdit *Edit11;
        TButton *Button13;
        TEdit *Edit12;
        TButton *Button14;
        TButton *Button15;
        TEdit *Edit13;
        TButton *Button16;
        TEdit *Edit14;
        TButton *Button17;
        TEdit *Edit15;
        TEdit *Edit16;
        TButton *Button18;
        TEdit *Edit17;
        TButton *Button19;
        TButton *Button20;
        TEdit *Edit18;
        TButton *Button21;
        TEdit *Edit19;
        TButton *Button22;
        TEdit *Edit20;
        TScrollBox *ScrollBox1;
        TScrollBox *ScrollBox2;
        TPanel *Panel1;
        TPanel *Panel2;
        TScrollBox *ScrollBox3;
        TTimer *Timer1;
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Button14Click(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall Button16Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall Button18Click(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Button20Click(TObject *Sender);
        void __fastcall Button21Click(TObject *Sender);
        void __fastcall Button22Click(TObject *Sender);
private:
public:
	virtual __fastcall TOKBottomDlg1(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TOKBottomDlg1 *OKBottomDlg1;
//----------------------------------------------------------------------------
#endif    
