#pragma once
#include "psapi.h"
#include "windows.h"
#include "stdio.h"
#include "math.h"
#pragma link "psapi.a"

#define SINGLE 1
#define EMBARK 2

TForm *get_about_pointer(void);
//TForm *get_attedit_pointer(void);
TForm *get_invedit_pointer(void);
TForm *get_dwarfedit_pointer(void);
__int64 get_dfstartaddr(void);
int get_dwarfcount(void);
HANDLE get_process(void);
__int64 get_addr_by_name(char *name);
void change_mode(int mode);
void change_mode(int mode, int dwarfnum);
void get_full_name(char *buf,int i,__int64 vect);
int range_rand( int range_min, int range_max);
char *fix_name(char *name);
