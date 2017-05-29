//----------------------------------------------------------------------------
#ifndef Unit4H
#define Unit4H
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
#include <vcl\ExtCtrls.hpp>   */
#include <Menus.hpp>
#include <System.Classes.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
//----------------------------------------------------------------------------
class TOKBottomDlg2 : public TForm
{
__published:
        TListBox *UpBodySlots;
        TListBox *HeadSlots;
        TListBox *LowBodySlots;
        TListBox *RightHandSlots;
        TListBox *LeftHandSlots;
        TListBox *RightFootSlots;
        TListBox *LeftFootSlots;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TButton *Button1;
        TListBox *OtherSlots;
        TLabel *Label8;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TEdit *Edit7;
        TComboBox *ComboBox1;
        TSpeedButton *SpeedButton1;
        TComboBox *ComboBox2;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall HeadSlotsClick(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:
public:
	virtual __fastcall TOKBottomDlg2(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TOKBottomDlg2 *OKBottomDlg2;
//----------------------------------------------------------------------------
#endif    
