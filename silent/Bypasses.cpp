#include "stdafx.h"
BOOL bInitialized = FALSE; detour<VOID> LiveStats_Probation_GiveProbation;
VOID LiveStats_Probation_GiveProbationHook(int controllerIndex, int gameMode, float time)
{
	time = 0.0f;
	LiveStats_Probation_GiveProbation.callOriginal(controllerIndex, gameMode, time);
}
BYTE PATCH_COD[148] = {
	0x82, 0x49, 0x7E, 0xB0, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00,
	0x82, 0x59, 0xA6, 0x5C, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00,
	0x82, 0x5B, 0xEA, 0x7C, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00,
	0x82, 0x5C, 0x60, 0x70, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0x82, 0x60, 0xB1, 0x78, 0x00, 0x00, 0x00, 0x01,
	0x60, 0x00, 0x00, 0x00, 0x84, 0x14, 0xA1, 0xD4, 0x00, 0x00, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x82, 0x2E, 0x4D, 0xF0,
	0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00, 0x84, 0xDC, 0x5F, 0xE4,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0x82, 0x66, 0x52, 0x68, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00,
	0x82, 0x58, 0x89, 0xDC, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x00,
	0x82, 0x58, 0x89, 0xE4, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF
};
VOID InitializeBypass(PLDR_DATA_TABLE_ENTRY Handle) {
	switch (Title) {
	case DASHBOARD: {
		if (!bInitialized) {
			bInitialized = TRUE;
			//KVGuardSetup();
		}
	}
					break;
	case GTA_V: {
		if (wcscmp(Module, L"default.xex") != 0) return;
		if (!bInitialized) {
			*(DWORD*)0x82C8B3B0 = 0x60000000;
			*(DWORD*)0x838BFFF8 = 0x60000000;
			bInitialized = TRUE;
		}
	}
				break;
	case COD_Modern_Warfare: {
		if (wcscmp(Module, L"default_mp.xex") != 0) return;
		if (!(Version & 0x00000100)) return;
		if (!bInitialized) {
			bInitialized = TRUE;
		}
	}
							 break;
	case COD_World_at_War: {
		if (wcscmp(Module, L"default_mp.xex") != 0) return;
		if (!(Version & 0x00000100)) return;
		if (!bInitialized) {
			bInitialized = TRUE;
		}
	}
						   break;
	case COD_Modern_Warfare_2: {
		if (wcscmp(Module, L"default_mp.xex") != 0) return;
		if (!(Version & 0x00000900)) return;
		if (!bInitialized) {
			bInitialized = TRUE;
		}
	}
							   break;
	case COD_Black_Ops: {
		if (wcscmp(Module, L"default_mp.xex") != 0) return;
		if (!(Version & 0x00000600)) return;
		if (!bInitialized) {
			bInitialized = TRUE;
		}
	}
						break;
	case COD_Modern_Warfare_3: {
		if (wcscmp(Module, L"default_mp.xex") != 0) return;
		if (!(Version & 0x00001800)) return;
		if (!bInitialized) {
			bInitialized = TRUE;
		}
	}
							   break;
	case COD_Black_Ops_2: {
		if (wcscmp(Module, L"default_mp.xex") != 0) return;
		if (!(Version & 0x00001200)) return;
		if (!bInitialized)
		{
			applyPatches(PATCH_COD);
			LiveStats_Probation_GiveProbation.setupDetour(0x825C5330, LiveStats_Probation_GiveProbationHook);
			bInitialized = TRUE;
		}
	}
						  break;
	case COD_Ghosts:
	{
		if (wcscmp(Module, L"default_mp.xex") != 0) return;
		if (!(Version & 0x00001100)) return;
		if (!bInitialized)
		{
			while (XamGetCurrentTitleId() == COD_Ghosts)
			{
				applyPatches(PATCH_COD + 0x34);
				Sleep(600000);
			}
			bInitialized = TRUE;
		}
	}
	break;
	case COD_Advanced_Warfare:
	{
		if (wcscmp(Module, L"default_mp.xex") != 0) return;
		if (!(Version & 0x00001100)) return;
		if (!bInitialized)
		{
			while (XamGetCurrentTitleId() == COD_Advanced_Warfare)
			{
				applyPatches(PATCH_COD + 0x50);
				Sleep(600000);
			}
			bInitialized = TRUE;
		}
	}
	break;
	case COD_Black_Ops_3:
	{
		if (wcscmp(Module, L"default.xex") != 0) return;
		if (!(Version & 0x00000800)) return;
		if (!bInitialized)
		{
			applyPatches(PATCH_COD + 0x6C);
			bInitialized = TRUE;
		}
	}
	break;
	case 0x454109BA:
	{
		//if (wcscmp(Module, L"BF.Main.xex") != 0) return;

		if (!bInitialized)
		{

			bInitialized = TRUE;
		}
	}
	break;
	default: bInitialized = FALSE; break;
	}
}