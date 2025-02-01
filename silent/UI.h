#include "stdafx.h"
#ifndef __Silent_H
#define __Silent_H

typedef INT(*tSendNotifyPress)(HXUIOBJ r3, WORD r4, WORD r5);
extern tSendNotifyPress SendNotifyPressStub;

namespace Dash_UI {
	extern void XuiElementBeginRenderStub(HXUIOBJ hObj, XUIMessageRender* pRenderData, XUIRenderStruct* pRenderStruct);
	extern HRESULT XuiElementBeginRenderHook(HXUIOBJ hObj, XUIMessageRender* pRenderData, XUIRenderStruct* pRenderStruct);
	extern HRESULT SetFill(HXUIOBJ hObj, DWORD Color1, DWORD Color2, BOOL Gradient);
	VOID patchlabels();
	VOID dashtext();
	VOID SetHUDUI();
	VOID SetDashUI();
	typedef enum _Colors : DWORD {
		/*Dash and setting Background*/ // 17559
		Dash1 = 0x92B19236,
		Dash2 = 0x92B4FDA7,
		Dash3 = 0x92F58323,
		Dash4 = 0x92B4FDAF,
		Dash5 = 0x92B4FDB3,
		/*Settingsbackground*/
		SettingsbackgroundDash6 = 0x92B4FD9B,
		SettingsbackgroundDash7 = 0x92106CE7,
		SettingsbackgroundDash8 = 0x92B4FDA7,
		SettingsbackgroundDash9 = 0x92F58323,
		SettingsbackgroundDash10 = 0x92B4FDAB,
		SettingsbackgroundDash11 = 0x92B4FD9F,
		SettingsbackgroundDash12 = 0x92B53D33,
		SettingsbackgroundDash13 = 0x92B55FA9,
		SettingsbackgroundDash14 = 0x92B9524B,
		SettingsbackgroundDash15 = 0x92B95A6D,
		SettingsbackgroundDash16 = 0x92C58F84,
		SettingsbackgroundDash17 = 0x92C6C662,
		SettingsbackgroundDash18 = 0x92CBE9D8,
		SettingsbackgroundDash19 = 0x92CC7138,
		SettingsbackgroundDash20 = 0x92CE54F8,
		SettingsbackgroundDash21 = 0x92D1DB13,
		SettingsbackgroundDash22 = 0x92D1E13C,
		SettingsbackgroundDash23 = 0x92D566BB,
		SettingsbackgroundDash24 = 0x92D56926,
		SettingsbackgroundDash25 = 0x92D56B48,
		SettingsbackgroundDash26 = 0x92D56FAA,
		SettingsbackgroundDash27 = 0x92D56D79,
		SettingsbackgroundDash28 = 0x92D57213,
		SettingsbackgroundDash29 = 0x92D5749E,
		SettingsbackgroundDash30 = 0x92F0E053,
		SettingsbackgroundDash31 = 0x92F54632,
		SettingsbackgroundDash32 = 0x92B4FD9F,
		SettingsbackgroundDash33 = 0x92B4FDA3,
		SettingsbackgroundDash34 = 0x92B4FD93,
		SettingsbackgroundDash35 = 0x92B4FD97,
		SettingsbackgroundDash36 = 0x92B4FD9F,
		SettingsbackgroundDash37 = 0x92B4FD9F,
		SettingsbackgroundDash38 = 0x92B4FDAF,
		SettingsbackgroundDash39 = 0x92B4FDB3,
		SettingsbackgroundDash40 = 0x92B4FE03,
		//* PNG's*/
		PNGDash41 = 0x92D2ACDC,
		PNGDash42 = 0x92D2AF9D,
		PNGDash43 = 0x92D2B12B,
		PNGDash44 = 0x92D2B2EC,
		PNGDash45 = 0x92DB07DF,

		/* txt_Tabs */
		txt_TabsDash46 = 0x9140A936,
		txt_TabsDash47 = 0x9140BF26,
		/* SignUp */
		SignUpDash48 = 0x92291ED6,
		SignUpDash49 = 0x9239AA6A,
		SignUpDash50 = 0x923F3862,
		SignUpDash51 = 0x92291EFE,
		SignUpDash52 = 0x9239AA96,
		/*Dashtitles*/ //17599
		Dashtitles53 = 0x92ACAA30,
		Dashtitles54 = 0x92C58F24,
		Dashtitles55 = 0x92F5F852,
		Dashtitles56 = 0x92F54622,
		Dashtitles57 = 0x92F0E15B,
		Dashtitles58 = 0x92DB07E5,
		Dashtitles59 = 0x92C72B73,
		Dashtitles60 = 0x92C58F28,
		Dashtitles61 = 0x92B570E2,
		/*HUD Press & GamerCard*/
		Dashtitles62 = 0x92BACFC0, // button press FF76B900
		Dashtitles63 = 0x92C58F24, // button press FF1CB61C
		Dashtitles64 = 0x92F0E16F, // button press FF1CB61C
		Dashtitles65 = 0x81B9D432, // Gamercard Gold
		Dashtitles66 = 0x81B9D436, // Gamercard Gold
		Dashtitles67 = 0xC025D43A, // Gamercard Silver
		Dashtitles68 = 0xC2317DE7, // Gamercard Silver 

		/*More Hud Stuff*/
		// Idle
		MISC69 = 0xC098E638,
		MISC70 = 0xC09BAEDE,
		MISC71 = 0xC10712EC,
		MISC72 = 0xC1073E94,
		MISC73 = 0xC1074394,
		MISC74 = 0xC10754F4,
		MISC75 = 0xC1075F54,
		MISC76 = 0xC108A9DC,
		MISC77 = 0xC108B910,
		MISC78 = 0xC108CB7C,
		MISC79 = 0xC108D110,
		MISC80 = 0xC10D0AF4,
		MISC81 = 0xC1117AE4,
		MISC82 = 0xC1197248,
		MISC83 = 0xC24D80E2,
		// Press
		MISC84 = 0xC09B9F0E,
		MISC85 = 0xC0F99000,
		MISC86 = 0xC0FA97D8,
		MISC87 = 0xC1075F48,
		MISC88 = 0xC111ECC0,
		MISC89 = 0xC1197278,
		MISC90 = 0xC212F16F,
		//Txts
		SignTxt = 0x92BAE010,
		SignTxt2 = 0x92BADFFC,
		OpenTray = 0x92D2CA2E,
		CloseTray = 0x92D2C9DC,
		OfflineDashTxt = 0x92D2BD71,
		/*Hud Txt*/
		TurnOffGamesApps = 0x9140A095,
		AccountManagement = 0x91411A16,
		HomeTab = 0x9140A086,
		TurnOffConsole1 = 0x91411A9B,
		TurnOffConsole2 = 0x91411FAF,
		SettingsTab = 0x9140A05C,
		SystemSettings = 0x914119F7,
		/*Pictures*/
		Avatar = 0x92D84DC8,
		/*Offline_Home_Slot*/
		OfflineDashHome = 0x92BD0869,
		HudRender = 0x817CA3A0,
		/* Social Online */
		SocialOnline = 0x9AFC4876,
		SocialOffonline = 0x9B06B948,
		/*KeyBoard Outline*/
		KeyBoard = 0x81BDB0D0,
		KeyBoard2 = 0x81BDB0F9,
		DashBuildHook = 0x92200360,
		DashPressHook = 0x92324B88,
		/*Purchase Games Buttons*/
		PurchaseGames1 = 0x9B111169,
		PurchaseGames2 = 0x9B11CBB8,
		PurchaseGames3 = 0x9B11DFCF,
		PurchaseGames4 = 0x9B11F133,
		PurchaseGames5 = 0x9B11F31A,
		PurchaseGames6 = 0x9B120CF0,
		PurchaseGames7 = 0x9B120F1C,
		PurchaseGames8 = 0x9B124609,
		PurchaseGames9 = 0x9B121556,
		PurchaseGames10 = 0x9B1224FA,
		PurchaseGames11 = 0x9B12271F,
		PurchaseGames12 = 0x9B1243C7
	} _Colors;
}

namespace HUD_UI {
	extern void XuiElementBeginRenderStub(HXUIOBJ hObj, XUIMessageRender* pRenderData, XUIRenderStruct* pRenderStruct);
	extern HRESULT XuiElementBeginRenderHook(HXUIOBJ hObj, XUIMessageRender* pRenderData, XUIRenderStruct* pRenderStruct);
	extern void OpenCustomScene();
}
#endif