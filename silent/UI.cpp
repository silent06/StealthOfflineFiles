#include "stdafx.h"
#include <xui.h>
DWORD Color = 0xFF7d2886;//7d2886
DWORD Color2 = 0xFF47d131;//47d131
HXUIOBJ hGuideMain;
HXUIOBJ newScene;
namespace Dash_UI {
	__declspec(naked) void XuiElementBeginRenderStub(HXUIOBJ hObj, XUIMessageRender* pRenderData, XUIRenderStruct* pRenderStruct) {
		__asm {
			li r3, 0x1E
			nop
			nop
			nop
			nop
			nop
			nop
			blr
		}
	}
	HRESULT SetFill(HXUIOBJ hObj, DWORD Color1, DWORD Color2, BOOL Gradient) {
		XUI_FILL_TYPE fillType = XUI_FILL_TYPE::XUI_FILL_LINEAR_GRADIENT;
		fillType = (Gradient) ? XUI_FILL_TYPE::XUI_FILL_RADIAL_GRADIENT : XUI_FILL_TYPE::XUI_FILL_LINEAR_GRADIENT;
		D3DXVECTOR2 pvScalingFactor(1.0f, 1.0f), pTrnas(0.0f, 0.0f);

		XUIGradientStop gs[2];
		gs[0].dwColor = Color1;
		gs[0].fPos = 0.0f;

		gs[1].dwColor = Color2;
		gs[1].fPos = 1.0f;

		return ((HRESULT(*)(...))0x921E3458)(hObj, fillType, Color, gs, 2, RotateSrc, &pvScalingFactor, &pTrnas);
	}
	HRESULT XuiElementBeginRenderHook(HXUIOBJ hObj, XUIMessageRender* pRenderData, XUIRenderStruct* pRenderStruct) {
		HXUIOBJ hParentObj; LPCWSTR ObjID, ParentText;
		//Dashboard_Calls::XuiElementGetId(hObj, &ObjID);
		//Dashboard_Calls::XuiElementGetParent(hObj, &hParentObj);
		//Dashboard_Calls::XuiElementGetId(hParentObj, &ParentText);
		XuiElementBeginRenderStub(hObj, pRenderData, pRenderStruct);
		((HRESULT(*)(...))0x921DF700)(hObj, &ObjID);
		if (lstrcmpW(ObjID, L"Front") == 0 || lstrcmpW(ObjID, L"GreenHighlight") == 0 || lstrcmpW(ObjID, L"Background") == 0 || lstrcmpW(ObjID, L"figSearchBox") == 0 || lstrcmpW(ObjID, L"DescriptionGrid") == 0
			|| lstrcmpW(ObjID, L"DescriptionGrid") == 0 || lstrcmpW(ObjID, L"HubSlotXzpScene") == 0 || lstrcmpW(ObjID, L"Back") == 0 || lstrcmpW(ObjID, L"Color") == 0 || lstrcmpW(ObjID, L"_SceneHost") == 0)  {

			SetFill(hObj, Color, Color2, TRUE);
			
			//D3DXVECTOR2 pvScalingFactor(1.0f, 1.0f), pTrnas(0.0f, 0.0f);
			//XUIGradientStop gs[2];
			//gs[0].dwColor = Color;
			//gs[0].fPos = 0.0f;
			//gs[1].dwColor = Color2;
			//gs[1].fPos = 1.0f;
			//((HRESULT(*)(...))0x921E3458)(hObj, XUI_FILL_TYPE::XUI_FILL_RADIAL_GRADIENT, Color, gs, 2, 0, &pvScalingFactor, &pTrnas);
		}
		
		
		/*if (lstrcmpW(ObjID, L"Front") == 0)
			SetFill(hObj, Color, Color2, TRUE);
		else if (lstrcmpW(ObjID, L"Background") == 0 || lstrcmpW(ObjID, L"GreenHighlight") == 0 || lstrcmpW(ObjID, L"XuiFigure3") == 0)
			SetFill(hObj, Color, Color2, TRUE);
		else if (lstrcmpW(ObjID, L"figSearchBox") == 0 || lstrcmpW(ParentText, L"DescriptionGrid") == 0 || lstrcmpW(ParentText, L"HubSlotXzpScene") == 0 ||
			lstrcmpW(ParentText, L"Back") == 0 || lstrcmpW(ParentText, L"Color") == 0 || lstrcmpW(ParentText, L"_SceneHost") == 0)
			SetFill(hObj, Color, Color2, TRUE);//background
		*/
		return 0;
	}

	VOID SetDashUI() {
		memcpy((PVOID*)Dash1, (BYTE*)&Color, 4);
		memcpy((PVOID*)Dash2, (BYTE*)&Color, 4);
		memcpy((PVOID*)Dash3, (BYTE*)&Color, 4);
		memcpy((PVOID*)Dash4, (BYTE*)&Color, 4);
		memcpy((PVOID*)Dash5, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash6, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash7, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash8, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash9, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash10, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash11, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash12, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash13, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash14, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash15, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash16, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash17, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash18, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash19, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash20, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash21, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash22, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash23, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash24, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash25, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash26, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash27, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash28, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash29, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash30, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash31, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash32, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash33, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash34, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash35, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash36, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash37, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash38, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash39, (BYTE*)&Color, 4);
		memcpy((PVOID*)SettingsbackgroundDash40, (BYTE*)&Color, 4);
		/*memcpy((PVOID*)SignUpDash48, (BYTE*)&Color1, 4);
		memcpy((PVOID*)SignUpDash49, (BYTE*)&Color1, 4);
		memcpy((PVOID*)SignUpDash50, (BYTE*)&Color1, 4);
		memcpy((PVOID*)SignUpDash51, (BYTE*)&Color1, 4);
		memcpy((PVOID*)SignUpDash52, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles53, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles54, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles55, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles56, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles57, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles58, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles59, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles60, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles61, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles62, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles63, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles64, (BYTE*)&Color1, 4);
		memcpy((PVOID*)PNGDash41, (BYTE*)&Color1, 4);
		memcpy((PVOID*)PNGDash42, (BYTE*)&Color1, 4);
		memcpy((PVOID*)PNGDash43, (BYTE*)&Color1, 4);
		memcpy((PVOID*)PNGDash44, (BYTE*)&Color1, 4);
		memcpy((PVOID*)PNGDash45, (BYTE*)&Color1, 4);
		memcpy((PVOID*)txt_TabsDash46, (BYTE*)&Color1, 4);
		memcpy((PVOID*)txt_TabsDash47, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles65, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles66, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles67, (BYTE*)&Color1, 4);
		memcpy((PVOID*)Dashtitles68, (BYTE*)&Color1, 4);*/
	}
	VOID SetHUDUI() {
		// Idle
		memcpy((PVOID*)MISC69, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC70, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC71, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC72, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC73, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC74, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC75, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC76, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC77, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC78, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC79, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC80, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC81, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC82, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC83, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC84, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC85, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC86, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC87, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC88, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC89, (BYTE*)&Color2, 4);
		memcpy((PVOID*)MISC90, (BYTE*)&Color2, 4);
	}

	VOID dashtext() {
		memcpy((LPVOID)SignTxt, WelcomeTo, 19);// WeLcOME To    
		memcpy((LPVOID)SignTxt2, Greeting, 19);//Silent Live        
		memcpy((LPVOID)OpenTray, Open, 9);//HookaH   
		memcpy((LPVOID)CloseTray, Close, 10);//CloseGuY  
		memcpy((LPVOID)OfflineDashTxt, "Your Offline! Please visit silentlive.gq                                       ", 80);
	}
	VOID patchlabels() {
		/*Hud Txt*/
		char* XboxGaA = "Silent Menu ";
		memcpy((LPVOID)TurnOffGamesApps, XboxGaA, 13); // -- Turn Off Games & Apps
		char* XboxAM = "Account STUFF     ";
		memcpy((LPVOID)AccountManagement, XboxAM, 18); // -- Account Management
		char* XboxHME = "LIVE";
		memcpy((LPVOID)HomeTab, XboxHME, 4); // -- Home Tab
		char* XboxToC = "Exit SilenTLive  ";
		memcpy((LPVOID)TurnOffConsole1, XboxToC, 16); // -- Turn Off Console 
		memcpy((LPVOID)TurnOffConsole2, XboxToC, 16); // -- Turn Off Console 
		char* GuideBladeLblText = "SileNT  ";//[8] chars 
		memcpy((LPVOID)SettingsTab, GuideBladeLblText, 8); // -- Settings Tab 
		char* GuideButtonSS = "UR SeTtings!   "; // [15] Chars
		memcpy((LPVOID)SystemSettings, GuideButtonSS, 15); // -- System Settings 
	}
}
namespace HUD_UI {
	__declspec(naked) void XuiElementBeginRenderStub(HXUIOBJ hObj, XUIMessageRender* pRenderData, XUIRenderStruct* pRenderStruct) {
		__asm {
			li r3, 0x14
			nop
			nop
			nop
			nop
			nop
			nop
			blr
		}
	}

	HRESULT XuiElementBeginRenderHook(HXUIOBJ hObj, XUIMessageRender* pRenderData, XUIRenderStruct* pRenderStruct) {
		HXUIOBJ hParentObj; LPCWSTR ObjID, ParentText;

		XuiElementBeginRenderStub(hObj, pRenderData, pRenderStruct);

		XuiElementGetId(hObj, &ObjID);
		XuiElementGetParent(hObj, &hParentObj);
		XuiElementGetId(hParentObj, &ParentText);

		if (lstrcmpW(ObjID, L"GreenHighlight") == 0 || lstrcmpW(ObjID, L"GreenHighlight1") == 0) {

			D3DXVECTOR2 pvScalingFactor(1.0f, 1.0f), pTrnas(0.0f, 0.0f);

			XUIGradientStop gs[2];
			gs[0].dwColor = Color;
			gs[0].fPos = 0.0f;

			gs[1].dwColor = Color;
			gs[1].fPos = 1.0f;

			XuiFigureSetFill(hObj, XUI_FILL_TYPE::XUI_FILL_SOLID, Color, gs, 2, 0, &pvScalingFactor, &pTrnas);
		}

		if (lstrcmpW(ParentText, L"Tabscene") == 0) {
			XuiElementGetParent(hParentObj, &hGuideMain);
		}

		return 0;
	}

	void OpenCustomScene() {
		XuiSceneCreate(nullptr, toWCHAR("memory://%X,%X#ShieldMenu.xur", 0, sizeof(0)), NULL, &newScene);
		XuiSceneNavigateForward(hGuideMain, FALSE, newScene, 0xFF);
	}


}