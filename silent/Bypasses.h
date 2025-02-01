#include "stdafx.h"
extern DWORD Title, Version; extern PWCHAR Module;
VOID InitializeBypass(PLDR_DATA_TABLE_ENTRY Handle);
typedef enum {
	DASHBOARD = 0xFFFE07D1,
	FREESTYLEDASH = 0xF5D20000,
	DASHLAUNCH = 0xFFFF011D,
	COD_Black_Ops_3 = 0x4156091D,
	COD_Advanced_Warfare = 0x41560914,
	COD_Ghosts = 0x415608FC,
	COD_Black_Ops_2 = 0x415608C3,
	COD_Modern_Warfare_3 = 0x415608CB,
	COD_Black_Ops = 0x41560855,
	COD_Modern_Warfare_2 = 0x41560817,
	COD_World_at_War = 0x4156081C,
	COD_Modern_Warfare = 0x415607E6,
	GTA_V = 0x545408A7,
	DESTINY = 0x415608F8
} XBOX_GAMES;
