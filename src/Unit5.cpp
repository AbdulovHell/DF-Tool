//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "mirror.h"
#include "time.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
TCheckBox *o_Boxes[4];
TEdit	*att_boxes[19];
TButton *att_5k_buttons[19];
int _mode=NULL;
TForm *get_dwarfedit_pointer(void){
return Form5;
}

void change_mode(int mode){
_mode=mode;
Form5->SpeedButton1->Enabled=true;
Form5->Dwarf_list->Enabled=true;
Form5->Dwarf_list->Clear();
Form5->GroupBox1->Enabled=true;
Form5->GroupBox1->Visible=true;
}
void change_mode(int mode, int dwarfnum){
_mode=mode;
Form5->SpeedButton1->Enabled=false;
Form5->Dwarf_list->Clear();
for(int i=0;i<dwarfnum+1;i++){
	Form5->Dwarf_list->Items->Add(" ");
}
Form5->Dwarf_list->ItemIndex=dwarfnum;
Form5->Dwarf_listChange(Form5);
Form5->Dwarf_list->Enabled=false;
Form5->GroupBox1->Enabled=false;
Form5->GroupBox1->Visible=false;
}
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
o_Boxes[0]=CheckBox1;
o_Boxes[1]=CheckBox2;
o_Boxes[2]=CheckBox3;
o_Boxes[3]=CheckBox4;

att_boxes[0]=Edit7;
att_boxes[1]=Edit8;
att_boxes[2]=Edit9;
att_boxes[3]=Edit11;
att_boxes[4]=Edit10;
att_boxes[5]=Edit16;
att_boxes[6]=Edit15;
att_boxes[7]=Edit14;
att_boxes[8]=Edit13;
att_boxes[9]=Edit12;
att_boxes[10]=Edit26;
att_boxes[11]=Edit25;
att_boxes[12]=Edit24;
att_boxes[13]=Edit23;
att_boxes[14]=Edit22;
att_boxes[15]=Edit21;
att_boxes[16]=Edit20;
att_boxes[17]=Edit19;
att_boxes[18]=Edit18;

att_5k_buttons[0]=Button7;
att_5k_buttons[1]=Button8;
att_5k_buttons[2]=Button9;
att_5k_buttons[3]=Button10;
att_5k_buttons[4]=Button11;
att_5k_buttons[5]=Button12;
att_5k_buttons[6]=Button13;
att_5k_buttons[7]=Button14;
att_5k_buttons[8]=Button15;
att_5k_buttons[9]=Button16;
att_5k_buttons[10]=Button17;
att_5k_buttons[11]=Button18;
att_5k_buttons[12]=Button24;
att_5k_buttons[13]=Button19;
att_5k_buttons[14]=Button23;
att_5k_buttons[15]=Button22;
att_5k_buttons[16]=Button21;
att_5k_buttons[17]=Button20;
att_5k_buttons[18]=Button25;
}
//---------------------------------------------------------------------------
void __fastcall TForm5::SpeedButton1Click(TObject *Sender)
{

int dwarfs=get_dwarfcount();
Dwarf_list->Items->Clear();
HANDLE hProcess=get_process();
for(int i=0;i<dwarfs;i++)
{
		char buf[120];
		strcpy(buf,"");
		if(dwarfs<10) sprintf(buf,"%d. ",i+1);
		else if(dwarfs<100) sprintf(buf,"%2d. ",i+1);
		else if(dwarfs<1000) sprintf(buf,"%3d. ",i+1);

		get_full_name(buf,i,get_dfstartaddr()+get_addr_by_name("creature_vect"));

		strcat(buf," id:");

		__int64 addr=get_dfstartaddr()+get_addr_by_name("creature_vect");
		ReadProcessMemory(hProcess,(void*)addr,&addr,8,NULL);
		addr=addr+i*8;
		ReadProcessMemory(hProcess,(void*)addr,&addr,8,NULL);
		addr+=0x128;
		ReadProcessMemory(hProcess,(void*)addr,&addr,4,NULL);
		char temp[20];
		sprintf(temp,"%d",addr);
		strcat(buf,temp);
		Dwarf_list->Items->Add(buf);

}

}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button1Click(TObject *Sender)
{
HANDLE hProcess=get_process();
short count=StrToInt(Edit1->Text);
if((count>=0)&&(count<32766)){
__int64 tempAddr;
__int64 addr=get_dfstartaddr()+get_addr_by_name("main");
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x120;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
int SelectedDwarf=Dwarf_list->ItemIndex;
addr=tempAddr+SelectedDwarf*8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x2B4;
WriteProcessMemory(hProcess,(void*)addr,&count,2,NULL);
}
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button2Click(TObject *Sender)
{
HANDLE hProcess=get_process();
int mas[135];
for(int i=0;i<135;i++) mas[i]=20;

__int64 tempAddr;
__int64 addr=get_dfstartaddr()+get_addr_by_name("main");
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x120;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
int SelectedDwarf=Dwarf_list->ItemIndex;
addr=tempAddr+SelectedDwarf*8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x7C;
WriteProcessMemory(hProcess,(void*)addr,mas,135*sizeof(int),NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button3Click(TObject *Sender)
{
HANDLE hProcess=get_process();
int mas[135];
for(int i=0;i<135;i++) mas[i]=-1;

__int64 tempAddr;
__int64 addr=get_dfstartaddr()+get_addr_by_name("main");
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x120;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
int SelectedDwarf=Dwarf_list->ItemIndex;
addr=tempAddr+SelectedDwarf*8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x7C;
ReadProcessMemory(hProcess,(void*)addr,mas,135*sizeof(int),NULL);

for(int i=0;i<135;i++) if(mas[i]>0) mas[i]=20;

WriteProcessMemory(hProcess,(void*)addr,mas,135*sizeof(int),NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button5Click(TObject *Sender)
{
HANDLE hProcess=get_process();
int mas[135];
for(int i=0;i<135;i++) mas[i]=-1;

__int64 tempAddr;
__int64 dwarfsOffset;
__int64 addr=get_dfstartaddr()+get_addr_by_name("main");
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x120;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
dwarfsOffset=tempAddr;
int SelectedDwarf=Dwarf_list->ItemIndex;
addr=tempAddr+SelectedDwarf*8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x7C;
ReadProcessMemory(hProcess,(void*)addr,mas,135*sizeof(int),NULL);

int dwarfs=get_dwarfcount();
for(int i=0;i<dwarfs;i++){
		addr=dwarfsOffset+i*8;
		ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
		addr=tempAddr+0x7C;
        WriteProcessMemory(hProcess,(void*)addr,mas,135*sizeof(int),NULL);
}
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button4Click(TObject *Sender)
{
HANDLE hProcess=get_process();
int mas[135];
for(int i=0;i<135;i++) mas[i]=0;

__int64 tempAddr;
__int64 addr=get_dfstartaddr()+get_addr_by_name("main");
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x120;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
int SelectedDwarf=Dwarf_list->ItemIndex;
addr=tempAddr+SelectedDwarf*8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x7C;
WriteProcessMemory(hProcess,(void*)addr,mas,135*sizeof(int),NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Dwarf_listChange(TObject *Sender)
{

int SelectedDwarf=Dwarf_list->ItemIndex;
HANDLE hProcess=get_process();
//read dwarf SP
__int64 tempAddr;
__int64 addr=get_dfstartaddr()+get_addr_by_name("main");
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x120;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+SelectedDwarf*8;
ReadProcessMemory(hProcess,(void*)addr,&tempAddr,8,NULL);
addr=tempAddr+0x2B4;
short count=0;
ReadProcessMemory(hProcess,(void*)addr,&count,2,NULL);
Edit1->Text=IntToStr(count);

//name
		__int64 NameOffset=(_mode==EMBARK)?get_dfstartaddr()+get_addr_by_name("creature_vect"):get_dfstartaddr()+get_addr_by_name("active_creature_vect");
		__int64 ColNameOffset=get_dfstartaddr()+get_addr_by_name("names");
		//char buf[100];
		//strcpy(buf,"");

		__int64 fnameaddr;
		char firstname[28];
		ReadProcessMemory(hProcess,(void*)NameOffset,&fnameaddr,8,NULL);
		fnameaddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)fnameaddr,&fnameaddr,8,NULL);

		UCHAR name_mode=0;
		ReadProcessMemory(hProcess,(void*)(fnameaddr+0x14),&name_mode,1,NULL);
		if(name_mode==0x1F){
			ReadProcessMemory(hProcess,(void*)fnameaddr,&fnameaddr,8,NULL);
			ReadProcessMemory(hProcess,(void*)fnameaddr,firstname,28,NULL);
			firstname[0]=toupper(firstname[0]);
			//strcat(buf,firstname);
			Edit2->Text=firstname;
		}else{
			ReadProcessMemory(hProcess,(void*)fnameaddr,firstname,28,NULL);
			firstname[0]=toupper(firstname[0]);
			//strcat(buf,firstname);
			Edit2->Text=firstname;
		}
		//
		//strcat(buf," ");
		//
		__int64 l1nameaddr;
		int l1nameind,l2nameind;
		char l1name[10],l2name[10];
		//получение индексов имен, первой части
		ReadProcessMemory(hProcess,(void*)NameOffset,&l1nameaddr,8,NULL);
		l1nameaddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		l1nameaddr+=0x40;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameind,4,NULL);
		Edit5->Text=IntToStr(l1nameind);
		//второй
		ReadProcessMemory(hProcess,(void*)NameOffset,&l1nameaddr,8,NULL);
		l1nameaddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		l1nameaddr+=0x44;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l2nameind,4,NULL);
		Edit6->Text=IntToStr(l2nameind);
		//
		ReadProcessMemory(hProcess,(void*)ColNameOffset,&l1nameaddr,8,NULL);
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		l1nameaddr+=0x50;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		l1nameaddr+=(l1nameind+1)*8-8;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
        ReadProcessMemory(hProcess,(void*)l1nameaddr,l1name,10,NULL);

		//l1name[0]=toupper(l1name[0]);

		//strcat(buf,l1name);
		Edit3->Text=l1name;
		Edit5->Text=IntToStr(l1nameind);

		ReadProcessMemory(hProcess,(void*)ColNameOffset,&l1nameaddr,8,NULL);
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		l1nameaddr+=0x50;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		l1nameaddr+=(l2nameind+1)*8-8;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		ReadProcessMemory(hProcess,(void*)l1nameaddr,l2name,10,NULL);

		//strcat(buf,l2name);
		Edit4->Text=l2name;
		Edit6->Text=IntToStr(l2nameind);
		//fix_name(buf);
//gender and orientation

		//DWORD NameOffset=get_dfstartaddr()+get_addr_by_name("creature_vect");
		//char buf[100];
		//strcpy(buf,"");

		__int64 stat_addr;
		ReadProcessMemory(hProcess,(void*)NameOffset,&stat_addr,8,NULL);
		stat_addr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)stat_addr,&stat_addr,8,NULL);
		stat_addr+=0xA70;    //current soul
		//ReadProcessMemory(hProcess,(void*)stat_addr,&stat_addr,8,NULL); //soul 0
		ReadProcessMemory(hProcess,(void*)stat_addr,&stat_addr,8,NULL);

		char gender=2;
		ReadProcessMemory(hProcess,(void*)(stat_addr+0x84),&gender,1,NULL);
		RadioGroup1->ItemIndex=gender;
		int orientation=0;
		ReadProcessMemory(hProcess,(void*)(stat_addr+0x88),&orientation,4,NULL);
		orientation>>=1;
		for(int i=0;i<4;i++){
			o_Boxes[i]->Checked=(orientation&0x1)?1:0;
			orientation>>=1;
		}
//attributes
__int64 AttrOffset=(_mode==EMBARK)?get_dfstartaddr()+get_addr_by_name("creature_vect"):get_dfstartaddr()+get_addr_by_name("active_creature_vect");
//dwarf offset1 soul offset2
//0     470                     +1C  phys
//0     80C     0    9C         +1C  soul
		//int tempAddr;
		ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,8,NULL);
		tempAddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);
		tempAddr+=0x5DC;     //body
        for(int j=0;j<6;j++){
				int temp;
                ReadProcessMemory(hProcess,(void*)(tempAddr+j*0x1C),&temp,4,NULL);
				att_boxes[j]->Text=IntToStr(temp);
		}
		ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,8,NULL);
		tempAddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);
		tempAddr+=0xA70;    //current soul
		//ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);
		//tempAddr+=0x0;        //soul 0
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);
		tempAddr+=0xAC;
		for(int j=0;j<13;j++){
				int temp;
				ReadProcessMemory(hProcess,(void*)(tempAddr+j*0x1C),&temp,4,NULL);
				att_boxes[j+6]->Text=IntToStr(temp);
		}
//age

		ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,8,NULL);
		tempAddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);

		int b_year,b_time,o_year,o_time,spouse,mother,father,lover;
		ReadProcessMemory(hProcess,(void*)(tempAddr+0x36c),&b_year,4,NULL);
		ReadProcessMemory(hProcess,(void*)(tempAddr+0x370),&b_time,4,NULL);
		ReadProcessMemory(hProcess,(void*)(tempAddr+0x384),&o_year,4,NULL);
		ReadProcessMemory(hProcess,(void*)(tempAddr+0x388),&o_time,4,NULL);
		ReadProcessMemory(hProcess,(void*)(tempAddr+0x3a0),&spouse,4,NULL);
		ReadProcessMemory(hProcess,(void*)(tempAddr+0x3a4),&mother,4,NULL);
		ReadProcessMemory(hProcess,(void*)(tempAddr+0x3a8),&father,4,NULL);
		ReadProcessMemory(hProcess,(void*)(tempAddr+0x3c0),&lover,4,NULL);

		Edit28->Text=IntToStr(mother);
		Edit29->Text=IntToStr(father);
		Edit30->Text=IntToStr(lover);
		Edit31->Text=IntToStr(spouse);

		Edit17->Text=IntToStr(b_year);
		Edit35->Text=IntToStr(o_year);
		b_time++;
		o_time++;
		Edit32->Text=IntToStr((int)((double)b_time/(28*1200))+1);
		Edit34->Text=IntToStr((int)((double)o_time/(28*1200))+1);

		Edit33->Text=IntToStr((int)(((double)b_time-((StrToInt(Edit32->Text)-1)*28*1200))/1200)+1);
		Edit27->Text=IntToStr((int)(((double)o_time-((StrToInt(Edit34->Text)-1)*28*1200))/1200)+1);

}
//---------------------------------------------------------------------------

void __fastcall TForm5::NameEditor_ApplyClick(TObject *Sender)
{
		int SelectedDwarf=Dwarf_list->ItemIndex;
		HANDLE hProcess=get_process();
		__int64 NameOffset=(_mode==EMBARK)?get_dfstartaddr()+get_addr_by_name("creature_vect"):get_dfstartaddr()+get_addr_by_name("active_creature_vect");
		__int64 ColNameOffset=get_dfstartaddr()+get_addr_by_name("names");
		//char buf[100];
		//strcpy(buf,"");

		__int64 fnameaddr;
		char firstname[28];
		wchar_t *temp=Edit2->Text.c_str();
		for(unsigned int i=0;i<strlen(firstname)+1;i++) firstname[i]=temp[i];
		ReadProcessMemory(hProcess,(void*)NameOffset,&fnameaddr,8,NULL);
		fnameaddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)fnameaddr,&fnameaddr,8,NULL);


		//WriteProcessMemory(hProcess,(void*)fnameaddr,firstname,strlen(firstname)+1,NULL);
		//(void*)fnameaddr+0x10;
		UCHAR len=strlen(firstname);
		UCHAR mode=0x0F;
		if(len<16&&len>0){
			WriteProcessMemory(hProcess,(void*)fnameaddr,firstname,strlen(firstname)+1,NULL);
			WriteProcessMemory(hProcess,(void*)(fnameaddr+0x10),&len,1,NULL);
			WriteProcessMemory(hProcess,(void*)(fnameaddr+0x18),&mode,1,NULL);
		}
		else {
			__int64 new_addr_name=(__int64)VirtualAllocEx(hProcess,NULL,strlen(firstname)+2,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
			WriteProcessMemory(hProcess,(void*)new_addr_name,firstname,strlen(firstname)+1,NULL);
			WriteProcessMemory(hProcess,(void*)fnameaddr,&new_addr_name,8,NULL);
			mode=0x1F;
			WriteProcessMemory(hProcess,(void*)(fnameaddr+0x10),&len,1,NULL);
			WriteProcessMemory(hProcess,(void*)(fnameaddr+0x18),&mode,1,NULL);
		}
		//firstname[0]=toupper(firstname[0]);
		//strcat(buf,firstname);
		//Edit2->Text=firstname;
		//
		//strcat(buf," ");
		//
		__int64 l1nameaddr=0;
		int l1nameind=StrToInt(Edit5->Text),l2nameind=StrToInt(Edit6->Text);
		//char l1name[10],l2name[10];
		//получение индексов имен, первой части
		ReadProcessMemory(hProcess,(void*)NameOffset,&l1nameaddr,8,NULL);
		l1nameaddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		l1nameaddr+=0x40;
		WriteProcessMemory(hProcess,(void*)l1nameaddr,&l1nameind,4,NULL);
		//Edit5->Text=IntToStr(l1nameind);
		//второй
		ReadProcessMemory(hProcess,(void*)NameOffset,&l1nameaddr,8,NULL);
		l1nameaddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
		l1nameaddr+=0x44;
		WriteProcessMemory(hProcess,(void*)l1nameaddr,&l2nameind,4,NULL);
		//Edit6->Text=IntToStr(l2nameind);

}
//---------------------------------------------------------------------------

void __fastcall TForm5::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
	HANDLE hProcess=get_process();
	__int64 ColNameOffset=get_dfstartaddr()+get_addr_by_name("names");
	__int64 l1nameaddr;
	int l1nameind=StrToInt(Edit5->Text);
	char l1name[10];

	ReadProcessMemory(hProcess,(void*)ColNameOffset,&l1nameaddr,8,NULL);
	ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
	l1nameaddr+=0x50;
	ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
	l1nameaddr+=(l1nameind+1)*8-8;
	ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
	ReadProcessMemory(hProcess,(void*)l1nameaddr,l1name,10,NULL);

	Edit3->Text=l1name;

}
//---------------------------------------------------------------------------

void __fastcall TForm5::UpDown2Click(TObject *Sender, TUDBtnType Button)
{
	HANDLE hProcess=get_process();
	__int64 ColNameOffset=get_dfstartaddr()+get_addr_by_name("names");
	__int64 l1nameaddr;
	int l2nameind=StrToInt(Edit6->Text);
	char l2name[10];

	ReadProcessMemory(hProcess,(void*)ColNameOffset,&l1nameaddr,8,NULL);
	ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
	l1nameaddr+=0x50;
	ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
	l1nameaddr+=(l2nameind+1)*8-8;
	ReadProcessMemory(hProcess,(void*)l1nameaddr,&l1nameaddr,8,NULL);
	ReadProcessMemory(hProcess,(void*)l1nameaddr,l2name,10,NULL);

	Edit4->Text=l2name;
}
//---------------------------------------------------------------------------




void __fastcall TForm5::Set_5k(TObject *Sender)
{
for(int i=0;i<19;i++)
	if(Sender==att_5k_buttons[i])
		att_boxes[i]->Text=IntToStr(5000);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Save_bttnClick(TObject *Sender)
{
int SelectedDwarf=Dwarf_list->ItemIndex;
HANDLE hProcess=get_process();
__int64 tempAddr;
__int64 NameOffset=(_mode==EMBARK)?get_dfstartaddr()+get_addr_by_name("creature_vect"):get_dfstartaddr()+get_addr_by_name("active_creature_vect");
//gender and orientation
	//TODO: gender
		__int64 stat_addr,addrasd;
		char gender=RadioGroup1->ItemIndex;
		ReadProcessMemory(hProcess,(void*)NameOffset,&stat_addr,8,NULL);
		stat_addr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)stat_addr,&stat_addr,8,NULL);

		addrasd=stat_addr+0x126;
		WriteProcessMemory(hProcess,(void*)addrasd,&gender,1,NULL);

		stat_addr+=0xA70;
		ReadProcessMemory(hProcess,(void*)stat_addr,&stat_addr,8,NULL);
		ReadProcessMemory(hProcess,(void*)stat_addr,&stat_addr,8,NULL);
		//0xFE

		WriteProcessMemory(hProcess,(void*)(stat_addr+0x84),&gender,1,NULL);

		int orientation=0;
		for(int i=0;i<4;i++)
			orientation+=(o_Boxes[i]->Checked)?1*pow((double)2,i):0;
		orientation<<=1;
		WriteProcessMemory(hProcess,(void*)(stat_addr+0x88),&orientation,4,NULL);

//attributes
__int64 AttrOffset=(_mode==EMBARK)?get_dfstartaddr()+get_addr_by_name("creature_vect"):get_dfstartaddr()+get_addr_by_name("active_creature_vect");
//dwarf offset1 soul offset2
//0     470                     +1C  phys
//0     80C     0    9C         +1C  soul
		//int tempAddr;
		ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,8,NULL);
		tempAddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);
		tempAddr+=0x5DC;
        for(int j=0;j<6;j++){
				int temp=StrToInt(att_boxes[j]->Text);
				WriteProcessMemory(hProcess,(void*)(tempAddr+j*0x1C),&temp,4,NULL);
		}
		ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,8,NULL);
		tempAddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);
		tempAddr+=0xA70;
		//ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,4,NULL);
		//tempAddr+=0x0;
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);
		tempAddr+=0xAC;
		for(int j=0;j<13;j++){
				int temp=StrToInt(att_boxes[j+6]->Text);
				WriteProcessMemory(hProcess,(void*)(tempAddr+j*0x1C),&temp,4,NULL);
		}
//age

		ReadProcessMemory(hProcess,(void*)AttrOffset,&tempAddr,8,NULL);
		tempAddr+=SelectedDwarf*8;
		ReadProcessMemory(hProcess,(void*)tempAddr,&tempAddr,8,NULL);

		int b_year=StrToInt(Edit17->Text),b_time
		,o_year=StrToInt(Edit35->Text),o_time
		,spouse=StrToInt(Edit31->Text),mother=StrToInt(Edit28->Text),father=StrToInt(Edit29->Text),lover=StrToInt(Edit30->Text);
		/*
		b_time++;
		o_time++;
		Edit32->Text=IntToStr((int)((double)b_time/(28*1200))+1);
		Edit34->Text=IntToStr((int)((double)o_time/(28*1200))+1);
		*/
		//Edit33->Text=IntToStr((int)(((double)b_time-((StrToInt(Edit32->Text)-1)*28*1200))/1200)+1);
		//Edit27->Text=IntToStr((int)(((double)o_time-((StrToInt(Edit34->Text)-1)*28*1200))/1200)+1);
		srand( (unsigned)time( NULL ) );
		b_time=(StrToInt(Edit32->Text)-1)*(28*1200)+(StrToInt(Edit33->Text)-1)*1200
		+range_rand(0,1199);
		o_time=(StrToInt(Edit34->Text)-1)*(28*1200)+(StrToInt(Edit27->Text)-1)*1200
		+range_rand(0,1199);

		WriteProcessMemory(hProcess,(void*)(tempAddr+0x36c),&b_year,4,NULL);
		WriteProcessMemory(hProcess,(void*)(tempAddr+0x370),&b_time,4,NULL);
		WriteProcessMemory(hProcess,(void*)(tempAddr+0x384),&o_year,4,NULL);
		WriteProcessMemory(hProcess,(void*)(tempAddr+0x388),&o_time,4,NULL);
		WriteProcessMemory(hProcess,(void*)(tempAddr+0x3a0),&spouse,4,NULL);
		WriteProcessMemory(hProcess,(void*)(tempAddr+0x3a4),&mother,4,NULL);
		WriteProcessMemory(hProcess,(void*)(tempAddr+0x3a8),&father,4,NULL);
		WriteProcessMemory(hProcess,(void*)(tempAddr+0x3c0),&lover,4,NULL);
}
//---------------------------------------------------------------------------

