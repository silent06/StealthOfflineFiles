#include "Title.h"
#include "stdafx.h"
BOOL dashLoaded = FALSE; PVOID SectionData = 0; DWORD SectionSize = 0;
const int LOW = 0;
const int HIGH = 255;
RGB color = { 0, 255, 0 };
RGB color2 = { 0, 0, 255 };
DWORD RotateSrc;
BOOL FadeToggle;
int speed = 2.0;
DWORD Title = 0, Version = 0; PWCHAR Module = 0;
BOOL GradientRotation = FALSE;
BOOL Hookah = TRUE;
VOID DoRotate() {

	GradientRotation = TRUE;
	float P = 1.0f;
	while (true) {
		if (P < 360) {
			P += speed;
		}
		else {
			P = 0;
		}

		RotateSrc = P;
		if (!GradientRotation) break;
		Sleep(15);
	}
}
DWORD randomizergb()
{
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);
	color.R = rand() % (HIGH - LOW + 1) + LOW;
	color.G = rand() % (HIGH - LOW + 1) + LOW;
	color.B = rand() % (HIGH - LOW + 1) + LOW;
	color2.R = rand() % (HIGH - LOW + 1) + LOW;
	color2.G = rand() % (HIGH - LOW + 1) + LOW;
	color2.B = rand() % (HIGH - LOW + 1) + LOW;
	Color = D3DCOLOR_ARGB(0xFF, color.R, color.G, color.B);
	Color2 = D3DCOLOR_ARGB(0xFF, color2.R, color2.G, color2.B);
	return 0;
}
VOID DoRGB() {
	int Speed = 1.4;
	FadeToggle = TRUE;
	while (true) {
		if (color.R > 0 && color.B <= 0) {
			color.R -= Speed;
			color.G += Speed;
		}
		if (color.G > 0 && color.R <= 0) {
			color.G -= Speed;
			color.B += Speed;
		}
		if (color.B > 0 && color.G <= 0) {
			color.R += Speed;
			color.B -= Speed;
		}
		if (color2.R > 0 && color2.B <= 0) {
			color2.R -= Speed;
			color2.G += Speed;
		}
		if (color2.G > 0 && color2.R <= 0) {
			color2.G -= Speed;
			color2.B += Speed;
		}
		if (color2.B > 0 && color2.G <= 0) {
			color2.R += Speed;
			color2.B -= Speed;
		}
		if (!FadeToggle) break;
		Color = D3DCOLOR_ARGB(0xFF, color.R, color.G, color.B);
		Color2 = D3DCOLOR_ARGB(0xFF, color2.R, color2.G, color2.B);
		Sleep(15);
	}

}
DWORD R3 = 255, G3, B3;
void RainbowColor() {
	while (true) {
		Sleep(1);
		if (R3 > 0 && B3 <= 0)
		{
			R3 -= 1;
			G3 += 1;
		}
		if (G3 > 0 && R3 <= 0)
		{
			G3 -= 1;
			B3 += 1;
		}
		if (B3 > 0 && G3 <= 0)
		{
			R3 += 1;
			B3 -= 1;
		}

		Color = D3DCOLOR_ARGB(0xFF, R3, G3, B3);
	}
}
HANDLE XHTTPConnectHook(XNCALLER_TYPE Type, void* Handle, char* ServerName, WORD ServerPort, DWORD Flags) {
	if (strcmp(ServerName, "manifest.xboxlive.com") == 0) {
		DashLoaded = false; strcpy(ServerName, CurrentIpAddress);
			if (strcmp(ServerName + 0x215, "dashhome.xml") == 0) { strcpy(ServerName + 0x200, "/assets/silent1.php"); DashLoaded = TRUE; }
			if (strcmp(ServerName + 0x215, "exl-HELP-on-360.xml") == 0) { strcpy(ServerName + 0x200, "/assets/silent2.php"); DashLoaded = TRUE; }
			if (strcmp(ServerName + 0x215, "exl-GamesMarketplace.xml") == 0) { strcpy(ServerName + 0x200, "/assets/silent3.php"); DashLoaded = TRUE; }
			if (strcmp(ServerName + 0x215, "DashVideoMP-London.xml") == 0) { strcpy(ServerName + 0x200, "/assets/silent4.php"); DashLoaded = TRUE; }
		ServerPort = 80; Flags = 0;
	}
	return ((HANDLE(*)(...))ResolveFunction(MODULE_XAM, 0xCD))(Type, Handle, ServerName, ServerPort, Flags);
}
bool XHTTPOpenRequestHook(XNCALLER_TYPE Type, HANDLE Handle, char* Headers, DWORD HeadersLength, void* Optional, DWORD OptionalLength, DWORD TotalLength, PDWORD Context) {
	if (DashLoaded) Headers = 0; return ((bool(*)(...))ResolveFunction(MODULE_XAM, 0xD1))(Type, Handle, Headers, HeadersLength, Optional, OptionalLength, TotalLength, Context);
}
VOID Noify() {
	WCHAR FilePath[MAX_PATH] = { 0 };
	XuiFreeVisuals(L"scr_Notification");
	swprintf(FilePath, L"section://%08X,XZP#Notify.xur", GetModuleHandle("silent.xex"));
	XuiLoadVisualFromBinary(FilePath, 0);
}
VOID InitializeTitleHooks(PLDR_DATA_TABLE_ENTRY Handle) {
	PatchModuleImport(Handle, MODULE_KERNEL, 407, (DWORD)XexGetProcedureAddressHook);
	PatchModuleImport(Handle, MODULE_KERNEL, 0x198, (DWORD)XexLoadExecutableHook);
	PatchModuleImport(Handle, MODULE_KERNEL, 0x199, (DWORD)XexLoadImageHook);
	PatchModuleImport(Handle, MODULE_KERNEL, 404, (DWORD)XenonPrivilegeHook);
	XEX_EXECUTION_ID* pExecutionId = (XEX_EXECUTION_ID*)RtlImageXexHeaderField(Handle->XexHeaderBase, 0x00040006);
	if (pExecutionId == 0) return;
	BOOL AnimLoaded = FALSE;
	if (wcscmp(Handle->BaseDllName.Buffer, L"bootanim.xex") == 0 || wcscmp(Handle->BaseDllName.Buffer, L"fakeanim.xex") == 0) AnimLoaded = TRUE;
	if (wcscmp(Handle->BaseDllName.Buffer, L"dash.xex") == 0) {
		ReadConfig();

		if (INI::Cheats) {
			if (!NT_SUCCESS(XexLoadImage("Hdd:\\silent Cache\\engine.xex", 8, 0, 0)));
			if (!NT_SUCCESS(XexLoadImage("Hdd:\\silent Cache\\GTAV.xex", 8, 0, 0)));
		}

		if (INI::CustomUI) {
			//Noify();
			if (!NT_SUCCESS(XexLoadImage("Hdd:\\silent Cache\\notify.xex", 8, 0, 0))); 
			Color = D3DCOLOR_ARGB(0xFF, R, G, B);
			Color2 = D3DCOLOR_ARGB(0xFF, R2, G2, B2);
			Dash_UI::dashtext();
			Dash_UI::SetDashUI();
			BYTE Data[0x13];
			memcpy((PDWORD)Dash_UI::Dash1, Data, 0x13);
			Hooking::OfflineHooks(Handle);
			cTools::HookFunctionStart((DWORD*)0x921E0518, (DWORD*)Dash_UI::XuiElementBeginRenderStub, (DWORD)Dash_UI::XuiElementBeginRenderHook);
			if (INI::CustomXml) {
				PatchModuleImport(Handle, MODULE_XAM, 0xCD, (DWORD)XHTTPConnectHook);
				PatchModuleImport(Handle, MODULE_XAM, 0xD1, (DWORD)XHTTPOpenRequestHook);
			}
			//tools.MakeThread((LPTHREAD_START_ROUTINE)RainbowColor);
			if (INI::Rainbow) {
				
				if(Hookah) {
					tools.MakeThread((LPTHREAD_START_ROUTINE)DoRotate);
					tools.MakeThread((LPTHREAD_START_ROUTINE)DoRGB);
					Hookah = FALSE;
				}
			}

			if (XGetModuleSection(Handle, "signinpr", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x1C40) = Color; // Sign in text
			}
			if (XGetModuleSection(Handle, "dashuisk", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x7828) = Color; // Highlighter
				*(PDWORD)((DWORD)SectionData + 0x7824) = Color; // Highlighter
				*(PDWORD)((DWORD)SectionData + 0x7880) = Color; // Descriptions 
			}
			if (XGetModuleSection(Handle, "socxzp", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x83B0) = Color; // Offline tiles
			}
			if (XGetModuleSection(Handle, "network", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0xEC73) = Color; // Bubbles
			}
		}
		dashLoaded = TRUE;
	}
	if (INI::CustomUI) 
	{
		if (wcscmp(Handle->BaseDllName.Buffer, L"dash.search.lex") == 0)
		{
			if (XGetModuleSection(Handle, "dashsear", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x948) = Color; // bing bar
			}
		}

		if (wcscmp(Handle->BaseDllName.Buffer, L"Dash.Search.xex") == 0)
		{
			if (XGetModuleSection(Handle, "dashsear", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x70D4) = Color; // bing
				*(PDWORD)((DWORD)SectionData + 0x710C) = Color; // bing
			}
		}

		if (wcscmp(Handle->BaseDllName.Buffer, L"dash.social.lex") == 0)
		{
			if (XGetModuleSection(Handle, "xzp", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x167F6) = Color; // Tiles
			}
		}

		if (wcscmp(Handle->BaseDllName.Buffer, L"Dash.OnlineCommon.lex") == 0)
		{
			if (XGetModuleSection(Handle, "ekmedia", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x386A) = Color; // Highlighter
				*(PDWORD)((DWORD)SectionData + 0x3896) = Color; // Highlighter
			}
		}

		if (wcscmp(Handle->BaseDllName.Buffer, L"dash.mp.contentexplorer.lex") == 0)
		{
			if (XGetModuleSection(Handle, "DashUI", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x14B38) = Color; // Extra
				*(PDWORD)((DWORD)SectionData + 0x170B3) = Color; // Pin to home and rate
				*(PDWORD)((DWORD)SectionData + 0x1729A) = Color; // Pick rating
				*(PDWORD)((DWORD)SectionData + 0x18C70) = Color; // Overview buttons
				*(PDWORD)((DWORD)SectionData + 0x1A69F) = Color; // Title selection
			}
		}

		if (wcscmp(Handle->BaseDllName.Buffer, L"Guide.Beacons.xex") == 0)
		{
			if (XGetModuleSection(Handle, "media", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x269D) = Color; // Highlighter
				*(PDWORD)((DWORD)SectionData + 0x26B5) = Color; // Highlighter
			}
		}

		if (wcscmp(Handle->BaseDllName.Buffer, L"guide.beacons.xex") == 0)
		{
			if (XGetModuleSection(Handle, "media", &SectionData, &SectionSize))
			{
				*(PDWORD)((DWORD)SectionData + 0x269D) = Color; // Highlighter
				*(PDWORD)((DWORD)SectionData + 0x26B5) = Color; // Highlighter
			}
		}

		if (wcscmp(Handle->BaseDllName.Buffer, L"Title.NewLiveSignup.xex") == 0)
		{
			if (XGetModuleSection(Handle, "embedded", &SectionData, &SectionSize))
			{
				*(DWORD*)((DWORD)SectionData + 0x386A) = Color; // Highlighter
				*(DWORD*)((DWORD)SectionData + 0x3896) = Color; // Highlighter
			}
			if (XGetModuleSection(Handle, "media", &SectionData, &SectionSize))
			{
				*(DWORD*)((DWORD)SectionData + 0x3056) = Color; // Highlighter
				*(DWORD*)((DWORD)SectionData + 0x307E) = Color; // Highlighter
			}
			if (XGetModuleSection(Handle, "controlp", &SectionData, &SectionSize))
			{
				*(DWORD*)((DWORD)SectionData + 0x3DEE2) = Color; // Highlighter
			}
		}
	}
	
	if (wcscmp(Handle->BaseDllName.Buffer, L"Guide.MP.Purchase.xex") == 0) {
		
		if (INI::MSPspoof) {
			BYTE xampatch1[0x1C] = {
				0x38, 0x80, 0x00, 0x05, 0x80, 0x63, 0x00, 0x1C, 0x90, 0x83, 0x00, 0x04,
				0x38, 0x80, 0x09, 0xC4, 0x90, 0x83, 0x00, 0x08, 0x38, 0x60, 0x00, 0x00,
				0x4E, 0x80, 0x00, 0x20
			};

			memcpy((PVOID)0x8168A6F8, xampatch1, 0x1C); // xam.xex 17559
			*(DWORD*)(0x818E9BE4) = 0x60000000; // xam.xex 17559
			*(DWORD*)(0x818EE414) = 0x480000C8; // xam.xex 17559
			*(DWORD*)(0x9015D860) = 0x60000000; // Guide.MP.Purchase.xex 17559
			*(DWORD*)(0x9015D924) = 0x60000000; // Guide.MP.Purchase.xex 17559

			XNotifyQueueUI(XNOTIFYUI_TYPE_COMPLAINT, 0, 2, L"[Silent] MSP Spoof!", 0);
		}
	}

	int titleVersion = (pExecutionId->Version >> 8) & 0xFF;
	switch (pExecutionId->TitleID) {
	
		/*case 0x454109BA: 
		if (wcscmp(Handle->BaseDllName.Buffer, L"default.xex") == 0) {

			XNotifyQueueUI(XNOTIFYUI_TYPE_COMPLAINT, 0, 2, L"[Silent] BF4 Loaded!", 0);
			if (!NT_SUCCESS(XexLoadImage("Hdd:\\silent Cache\\BF4.Engine.xex", 8, 0, 0)));
			printf("Installing hooks for 0x%08X", pExecutionId->TitleID);
		}
		break;*/

	//default:
		//printf("Unsupported title to install hooks for 0x%08X", pExecutionId->TitleID);
		//break;
	}


	if (INI::Bypass) {
		Title = pExecutionId->TitleID;
		Version = pExecutionId->Version;
		Module = Handle->BaseDllName.Buffer;
		tools.MakeThread((LPTHREAD_START_ROUTINE)InitializeBypass);
	}
}


