//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "mirror.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TOKBottomDlg *OKBottomDlg;
TForm *get_about_pointer(void){
return OKBottomDlg;
}
//---------------------------------------------------------------------
__fastcall TOKBottomDlg::TOKBottomDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//--------------------------------------------------------------------- 
