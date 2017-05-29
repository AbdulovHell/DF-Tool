//----------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//----------------------------------------------------------------------------
//#include <vcl\System.hpp>
//#include <vcl\Windows.hpp>
//#include <vcl\SysUtils.hpp>
//#include <vcl\Classes.hpp>
//#include <vcl\Graphics.hpp>
//#include <vcl\StdCtrls.hpp>
//#include <vcl\Forms.hpp>
//#include <vcl\Controls.hpp>
//#include <vcl\Buttons.hpp>
//#include <vcl\ExtCtrls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
//----------------------------------------------------------------------------
class TOKBottomDlg : public TForm
{
__published:
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label2;
        TLabel *Label6;
        TLabel *Label7;
private:
public:
	virtual __fastcall TOKBottomDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TOKBottomDlg *OKBottomDlg;
//----------------------------------------------------------------------------
#endif    
