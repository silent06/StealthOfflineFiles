#include "stdafx.h"
#include "offlinehooks.h"
typedef DWORD(*tFunctionFromDashThatLoadsImages)(PWCHAR r3, CONST PWCHAR r4, DWORD Size);
tFunctionFromDashThatLoadsImages OriginalFunctionFromDashThatLoadsImages;
BYTE szHookSection[0x500];
DWORD dwHookCount;
vector<HookContext> vHookContext;
detour<VOID> DashbuildConnectOur;
VOID __declspec(naked) GPLR()
{
	__asm
	{
		std r14, -0x98(r1)
		std r15, -0x90(r1)
		std r16, -0x88(r1)
		std r17, -0x80(r1)
		std r18, -0x78(r1)
		std r19, -0x70(r1)
		std r20, -0x68(r1)
		std r21, -0x60(r1)
		std r22, -0x58(r1)
		std r23, -0x50(r1)
		std r24, -0x48(r1)
		std r25, -0x40(r1)
		std r26, -0x38(r1)
		std r27, -0x30(r1)
		std r28, -0x28(r1)
		std r29, -0x20(r1)
		std r30, -0x18(r1)
		std r31, -0x10(r1)
		stw r12, -0x8(r1)
		blr
	}
}
DWORD Hooking::RelinkGPLR(DWORD Offset, PDWORD SaveStub, PDWORD Original)
{
	DWORD Instruction = 0, Replacing = 0;
	PDWORD Saver = (PDWORD)GPLR;
	if (Offset & 0x2000000) Offset |= 0xFC000000;
	Replacing = Original[Offset / 4];
	for (DWORD i = 0; i < 0x14; i++)
	{
		if (Replacing == Saver[i])
		{
			DWORD NewOffset = ((DWORD)&Saver[i] - (DWORD)SaveStub);
			Instruction = (0x48000001 | (NewOffset & 0x03FFFFFC));
		}
	}
	return Instruction;
}
void Hooking::PatchInJump(DWORD* dwAddress, DWORD dwDestination, bool bLinked) {
	if (dwDestination & 0x8000)
		dwAddress[0] = 0x3D600000 + (((dwDestination >> 16) & 0xFFFF) + 1);
	else
		dwAddress[0] = 0x3D600000 + ((dwDestination >> 16) & 0xFFFF);

	dwAddress[1] = 0x396B0000 + (dwDestination & 0xFFFF);
	dwAddress[2] = 0x7D6903A6;
	dwAddress[3] = 0x4E800420 | (bLinked ? 1 : 0);
}
void Hooking::HookFunctionStart(DWORD* dwAddress, DWORD* dwSaveStub, DWORD dwDestination) {
	if ((dwSaveStub != NULL) && (dwAddress != NULL)) {
		DWORD AddressRelocation = (DWORD)(&dwAddress[4]);

		if (AddressRelocation & 0x8000) {
			dwSaveStub[0] = 0x3D600000 + (((AddressRelocation >> 16) & 0xFFFF) + 1);
		}
		else {
			dwSaveStub[0] = 0x3D600000 + ((AddressRelocation >> 16) & 0xFFFF);
		}

		dwSaveStub[1] = 0x396B0000 + (AddressRelocation & 0xFFFF);
		dwSaveStub[2] = 0x7D6903A6;

		for (int i = 0; i < 4; i++) {
			if ((dwAddress[i] & 0x48000003) == 0x48000001) {
				dwSaveStub[i + 3] = Hooking::RelinkGPLR((dwAddress[i] & ~0x48000003), &dwSaveStub[i + 3], &dwAddress[i]);
			}
			else {
				dwSaveStub[i + 3] = dwAddress[i];
			}
		}

		dwSaveStub[7] = 0x4E800420;
		__dcbst(0, dwSaveStub);
		__sync();
		__isync();

		PatchInJump(dwAddress, dwDestination);
	}
}
DWORD DashBuildResourceLocatorHook(PWCHAR Resource, DWORD r4, DWORD ResourceSize)
{
	if (wcscmp(Resource + 0x1C, L"silent_Rainbow") == 0) {
		XNotifyQueueUI(XNOTIFYUI_TYPE_COMPLAINT, 0, 2, L"[Silent] Disabled", 0);
		//MakeThread(reinterpret_cast<LPTHREAD_START_ROUTINE>(rainbow));
		//MakeThread(reinterpret_cast<LPTHREAD_START_ROUTINE>(Hudrainbow));
		return 0;
	}

	if (wcscmp(Resource + 0x1C, L"silent_CheckTime") == 0) {
		XNotifyQueueUI(XNOTIFYUI_TYPE_COMPLAINT, 0, 2, L"[Silent] Disabled", 0);
		return 0;
	}
	//if (wcscmp(Resource + 0x1C, L"silent_Rainbow") == 0) { XuiSceneCreate(nullptr, xbox::utilities::LinkWChar(L"memory://%X,%X#silentScene.xur", Xui::XuiData, sizeof(Xui::XuiData)), NULL, &HUD_UI::newScene) & XuiSceneNavigateForward(HUD_UI::hGuideMain, FALSE, HUD_UI::newScene, 0xFF); return 0; }
	//if (wcscmp(Resource + 0x1C, L"silentScene") == 0) { XuiSceneCreate(nullptr, xbox::utilities::LinkWChar(L"memory://%X,%X#silentScene.xur", Xui::XuiData, sizeof(Xui::XuiData)), NULL, &HUD_UI::newScene);  xbox::utilities::XNotifyUI2(L"Success!"); return 0; }
	//if (lstrcmpW(Resource, L"section://30000EC8,silentScene#silentScene") == 0) { XuiSceneCreate(nullptr, xbox::utilities::LinkWChar(L"memory://%X,%X#silentScene.xur", Xui::XuiData, sizeof(Xui::XuiData)), NULL, &HUD_UI::newScene) & XuiSceneNavigateForward(HUD_UI::hGuideMain, FALSE, HUD_UI::newScene, 0xFF); xbox::utilities::XNotifyUI2(L"Success!"); }		
	DashbuildConnectOur.callOriginal(Resource, r4, ResourceSize);
}
DWORD FunctionFromDashThatLoadsImagesHook(PWCHAR r3, CONST PWCHAR r4, DWORD Size) {
	bool customSize = false;
	if (wcscmp(r3, L"epix://dashhome-offline.xml") == 0) {
		customSize = true;
		r3 = vaS(Str("memory://%X,%X#dashhome-offline.xml"), Xui::XuiData, sizeof(Xui::XuiData), dllHandle);
	}//"section://%X,silent#dashhome-offline.xml"
	if (wcscmp(r3, L"epix://Offline_Slot_Home.jpg") == 0) {
		customSize = true;
		r3 = vaS(Str("memory://%X,%X#Offline_Slot_Home.jpg"), Xui::XuiData, sizeof(Xui::XuiData), dllHandle);
	}
	//"section://%X,silent#Offline_Slot_Home.jpg"

	return OriginalFunctionFromDashThatLoadsImages(r3, r4, customSize ? lstrlenW(r3) : Size);
}
void Hooking::OfflineHooks(PLDR_DATA_TABLE_ENTRY Handle) {
	//Hooking::HookFunction(Dash_UI::DashBuildHook, FunctionFromDashThatLoadsImagesHook, &OriginalFunctionFromDashThatLoadsImages);
	DashbuildConnectOur.setupDetour(Dash_UI::DashBuildHook, DashBuildResourceLocatorHook);
}