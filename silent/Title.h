#include "stdafx.h"
VOID InitializeTitleHooks(PLDR_DATA_TABLE_ENTRY Handle);
extern CHAR CurrentIpAddress[38];
extern CHAR WelcomeTo[19];
extern CHAR Greeting[20];
extern CHAR Open[10];
extern CHAR Close[11];
extern DWORD Color;
extern DWORD Color2;
extern DWORD RotateSrc;
struct RGB {
	int R, G, B;
};