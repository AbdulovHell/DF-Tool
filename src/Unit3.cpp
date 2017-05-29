//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "mirror.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TOKBottomDlg1 *OKBottomDlg1;
TEdit *Sample[20];
int lastCount=-1;
int GlobalScroll=0;

TForm *get_attedit_pointer(void){
return OKBottomDlg1;
}
//---------------------------------------------------------------------
__fastcall TOKBottomDlg1::TOKBottomDlg1(TComponent* AOwner)
	: TForm(AOwner)
{
Sample[0]=new TEdit(Owner);
Sample[0]->ReadOnly=Edit1->ReadOnly;
Sample[0]->Width=Edit1->Width;
Sample[0]->Height=Edit1->Height;
Sample[0]->Top=Edit1->Top;
Sample[0]->Left=Edit1->Left;
Sample[0]->ParentWindow=Edit1->ParentWindow;
Sample[0]->Visible=false;
Edit1->~TEdit();

Sample[1]=new TEdit(Owner);
Sample[1]->Width=Edit2->Width;
Sample[1]->Height=Edit2->Height;
Sample[1]->Top=Edit2->Top;
Sample[1]->Left=Edit2->Left;
Sample[1]->ParentWindow=Edit2->ParentWindow;
Sample[1]->Visible=false;
Edit2->~TEdit();

Sample[2]=new TEdit(Owner);
Sample[2]->Width=Edit3->Width;
Sample[2]->Height=Edit3->Height;
Sample[2]->Top=Edit3->Top;
Sample[2]->Left=Edit3->Left;
Sample[2]->ParentWindow=Edit3->ParentWindow;
Sample[2]->Visible=false;
Edit3->~TEdit();

Sample[3]=new TEdit(Owner);
Sample[3]->Width=Edit4->Width;
Sample[3]->Height=Edit4->Height;
Sample[3]->Top=Edit4->Top;
Sample[3]->Left=Edit4->Left;
Sample[3]->ParentWindow=Edit4->ParentWindow;
Sample[3]->Visible=false;
Edit4->~TEdit();

Sample[4]=new TEdit(Owner);
Sample[4]->Width=Edit5->Width;
Sample[4]->Height=Edit5->Height;
Sample[4]->Top=Edit5->Top;
Sample[4]->Left=Edit5->Left;
Sample[4]->ParentWindow=Edit5->ParentWindow;
Sample[4]->Visible=false;
Edit5->~TEdit();

Sample[5]=new TEdit(Owner);
Sample[5]->Width=Edit6->Width;
Sample[5]->Height=Edit6->Height;
Sample[5]->Top=Edit6->Top;
Sample[5]->Left=Edit6->Left;
Sample[5]->ParentWindow=Edit6->ParentWindow;
Sample[5]->Visible=false;
Edit6->~TEdit();

Sample[6]=new TEdit(Owner);
Sample[6]->Width=Edit7->Width;
Sample[6]->Height=Edit7->Height;
Sample[6]->Top=Edit7->Top;
Sample[6]->Left=Edit7->Left;
Sample[6]->ParentWindow=Edit7->ParentWindow;
Sample[6]->Visible=false;
Edit7->~TEdit();

Sample[7]=new TEdit(Owner);
Sample[7]->Width=Edit8->Width;
Sample[7]->Height=Edit8->Height;
Sample[7]->Top=Edit8->Top;
Sample[7]->Left=Edit8->Left;
Sample[7]->ParentWindow=Edit8->ParentWindow;
Sample[7]->Visible=false;
Edit8->~TEdit();

Sample[8]=new TEdit(Owner);
Sample[8]->Width=Edit9->Width;
Sample[8]->Height=Edit9->Height;
Sample[8]->Top=Edit9->Top;
Sample[8]->Left=Edit9->Left;
Sample[8]->ParentWindow=Edit9->ParentWindow;
Sample[8]->Visible=false;
Edit9->~TEdit();

Sample[9]=new TEdit(Owner);
Sample[9]->Width=Edit10->Width;
Sample[9]->Height=Edit10->Height;
Sample[9]->Top=Edit10->Top;
Sample[9]->Left=Edit10->Left;
Sample[9]->ParentWindow=Edit10->ParentWindow;
Sample[9]->Visible=false;
Edit10->~TEdit();

Sample[10]=new TEdit(Owner);
Sample[10]->Width=Edit11->Width;
Sample[10]->Height=Edit11->Height;
Sample[10]->Top=Edit11->Top;
Sample[10]->Left=Edit11->Left;
Sample[10]->ParentWindow=Edit11->ParentWindow;
Sample[10]->Visible=false;
Edit11->~TEdit();

Sample[11]=new TEdit(Owner);
Sample[11]->Width=Edit12->Width;
Sample[11]->Height=Edit12->Height;
Sample[11]->Top=Edit12->Top;
Sample[11]->Left=Edit12->Left;
Sample[11]->ParentWindow=Edit12->ParentWindow;
Sample[11]->Visible=false;
Edit12->~TEdit();

Sample[12]=new TEdit(Owner);
Sample[12]->Width=Edit13->Width;
Sample[12]->Height=Edit13->Height;
Sample[12]->Top=Edit13->Top;
Sample[12]->Left=Edit13->Left;
Sample[12]->ParentWindow=Edit13->ParentWindow;
Sample[12]->Visible=false;
Edit13->~TEdit();

Sample[13]=new TEdit(Owner);
Sample[13]->Width=Edit14->Width;
Sample[13]->Height=Edit14->Height;
Sample[13]->Top=Edit14->Top;
Sample[13]->Left=Edit14->Left;
Sample[13]->ParentWindow=Edit14->ParentWindow;
Sample[13]->Visible=false;
Edit14->~TEdit();

Sample[14]=new TEdit(Owner);
Sample[14]->Width=Edit15->Width;
Sample[14]->Height=Edit15->Height;
Sample[14]->Top=Edit15->Top;
Sample[14]->Left=Edit15->Left;
Sample[14]->ParentWindow=Edit15->ParentWindow;
Sample[14]->Visible=false;
Edit15->~TEdit();

Sample[15]=new TEdit(Owner);
Sample[15]->Width=Edit16->Width;
Sample[15]->Height=Edit16->Height;
Sample[15]->Top=Edit16->Top;
Sample[15]->Left=Edit16->Left;
Sample[15]->ParentWindow=Edit16->ParentWindow;
Sample[15]->Visible=false;
Edit16->~TEdit();

Sample[16]=new TEdit(Owner);
Sample[16]->Width=Edit17->Width;
Sample[16]->Height=Edit17->Height;
Sample[16]->Top=Edit17->Top;
Sample[16]->Left=Edit17->Left;
Sample[16]->ParentWindow=Edit17->ParentWindow;
Sample[16]->Visible=false;
Edit17->~TEdit();

Sample[17]=new TEdit(Owner);
Sample[17]->Width=Edit18->Width;
Sample[17]->Height=Edit18->Height;
Sample[17]->Top=Edit18->Top;
Sample[17]->Left=Edit18->Left;
Sample[17]->ParentWindow=Edit18->ParentWindow;
Sample[17]->Visible=false;
Edit18->~TEdit();

Sample[18]=new TEdit(Owner);
Sample[18]->Width=Edit19->Width;
Sample[18]->Height=Edit19->Height;
Sample[18]->Top=Edit19->Top;
Sample[18]->Left=Edit19->Left;
Sample[18]->ParentWindow=Edit19->ParentWindow;
Sample[18]->Visible=false;
Edit19->~TEdit();

Sample[19]=new TEdit(Owner);
Sample[19]->Width=Edit20->Width;
Sample[19]->Height=Edit20->Height;
Sample[19]->Top=Edit20->Top;
Sample[19]->Left=Edit20->Left;
Sample[19]->ParentWindow=Edit20->ParentWindow;
Sample[19]->Visible=false;
Edit20->~TEdit();
}
//---------------------------------------------------------------------


TEdit ***EditBoxes;

void __fastcall TOKBottomDlg1::Button8Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();

if(EditBoxes!=NULL){
for(int i=0;i<lastCount;i++){
        for(int j=0;j<20;j++){
                if(EditBoxes[i][j]!=NULL)
                        EditBoxes[i][j]->~TEdit();
        }
        if(EditBoxes[i]!=NULL)
                free(EditBoxes[i]);
}
free(EditBoxes);
}
EditBoxes=(TEdit***)malloc(sizeof(TEdit)*dwarfcount);
for(int i=0;i<dwarfcount;i++){
EditBoxes[i]=(TEdit**)malloc(sizeof(TEdit)*20);
for(int j=0;j<20;j++){
EditBoxes[i][j]=new TEdit(Owner);
EditBoxes[i][j]->Width=Sample[j]->Width;
EditBoxes[i][j]->Height=Sample[j]->Height;
EditBoxes[i][j]->Top=Sample[j]->Top+i*21;
EditBoxes[i][j]->Left=Sample[j]->Left;
if(!j) EditBoxes[i][j]->ParentWindow=ScrollBox2->Handle;
else  EditBoxes[i][j]->ParentWindow=ScrollBox1->Handle;
//EditBoxes[i][j]->Text="NULL";
if(i==dwarfcount-1){
        Panel1->Top=EditBoxes[i][j]->Top;
        Panel1->SendToBack();
        Panel1->Visible=true;
        Panel2->Top=EditBoxes[i][j]->Top;
        Panel2->Left=EditBoxes[i][j]->Left;
        Panel2->SendToBack();
        Panel2->Visible=true;
}
}
}

lastCount=dwarfcount;
HANDLE hProcess=get_process();
DWORD AttrOffset=get_dfstartaddr()+get_addr_by_name("creature_vect");
//dwarf offset1 soul offset2
//0     470                     +1C  phys
//0     80C     0    9C         +1C  soul
for(int i=0;i<dwarfcount;i++){
        //
        char buf[100];
        strcpy(buf,"");
        if(dwarfcount<10) sprintf(buf,"%d. ",i+1);
        else if(dwarfcount<100) sprintf(buf,"%2d. ",i+1);
        else if(dwarfcount<1000) sprintf(buf,"%3d. ",i+1);

        get_full_name(buf,i,get_dfstartaddr()+get_addr_by_name("creature_vect"));
        //
        EditBoxes[i][0]->Text=buf;
        //
        int tempAddr;
        ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,4,NULL);
        tempAddr+=i*4;
        ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
		tempAddr+=0x470;
		for(int j=0;j<6;j++){
				int temp;
                ReadProcessMemory(hProcess,(void*)(tempAddr+j*0x1C),&temp,4,NULL);
				EditBoxes[i][j+1]->Text=IntToStr(temp);
        }
        ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,4,NULL);
        tempAddr+=i*4;
        ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
		tempAddr+=0x80C;
        ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
		tempAddr+=0x0;
        ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
		tempAddr+=0x9C;
		for(int j=0;j<13;j++){
				int temp;
                ReadProcessMemory(hProcess,(void*)(tempAddr+j*0x1C),&temp,4,NULL);
                EditBoxes[i][j+7]->Text=IntToStr(temp);
        }
}
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button9Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
HANDLE hProcess=get_process();
DWORD AttrOffset=get_dfstartaddr()+get_addr_by_name("creature_vect");
//dwarf offset1 soul offset2
//0     46C                     +1C  phys
//0     80C     0    9C         +1C  soul
for(int i=0;i<dwarfcount;i++){
        int tempAddr;
        ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,4,NULL);
        tempAddr+=i*4;
        ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
		tempAddr+=0x470;
        for(int j=0;j<6;j++){
                int temp=StrToInt(EditBoxes[i][j+1]->Text);
                WriteProcessMemory(hProcess,(void*)(tempAddr+j*0x1C),&temp,4,NULL);
        }
        ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,4,NULL);
        tempAddr+=i*4;
        ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
        tempAddr+=0x80C;
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
		tempAddr+=0x0;
        ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
		tempAddr+=0x9C;
        for(int j=0;j<13;j++){
                int temp=StrToInt(EditBoxes[i][j+7]->Text);
                WriteProcessMemory(hProcess,(void*)(tempAddr+j*0x1C),&temp,4,NULL);
        }
}
}
//---------------------------------------------------------------------------







void __fastcall TOKBottomDlg1::Timer1Timer(TObject *Sender)
{
ScrollBox3->HorzScrollBar->Position=ScrollBox1->HorzScrollBar->Position;
ScrollBox2->VertScrollBar->Position=ScrollBox1->VertScrollBar->Position;
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button2Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][1]->Text=IntToStr(5000);
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button3Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][2]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button4Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][3]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button5Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][4]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button6Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][5]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button7Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][6]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button10Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][7]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button11Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][8]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button12Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][9]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button13Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][10]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button14Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][11]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button15Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][12]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button16Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][13]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button17Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][14]->Text=IntToStr(5000);
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button18Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][15]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button19Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][16]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button20Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][17]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button21Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][18]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

void __fastcall TOKBottomDlg1::Button22Click(TObject *Sender)
{
int dwarfcount=get_dwarfcount();
for(int i=0;i<dwarfcount;i++) EditBoxes[i][19]->Text=IntToStr(5000);        
}
//---------------------------------------------------------------------------

