#include "stdafx.h"
#pragma once
struct ManifestData {
	const wchar_t* pCommand;
	char _0x0004[0x18];
	const wchar_t* pParam;
};
struct HookContext {
	DWORD dwAddress;
	BYTE szAsm[0x10];
	BYTE bWriteSize;

	HookContext() {
		bWriteSize = 0x10;
	}
};
class Hooking {
public:
	//static vector<HookContext> vHookContext;
	//static BYTE szHookSection[0x500];
	//static DWORD dwHookCount;
	static void PatchInJump(DWORD* dwAddress, DWORD dwDestination, bool bLinked = false);
	static void HookFunctionStart(DWORD* dwAddress, DWORD* dwSaveStub, DWORD dwDestination);
	static DWORD RelinkGPLR(DWORD Offset, PDWORD SaveStub, PDWORD Original);
	static void OfflineHooks(PLDR_DATA_TABLE_ENTRY Handle);
	//Need this
	template <typename T>
	static bool HookFunction(DWORD dwAddress, void* pHookFunction, T* pTrampoline, bool addToIntegrity = false) {
		if (dwAddress) {
			HookContext cxt;
			cxt.dwAddress = dwAddress;
			memcpy(cxt.szAsm, (void*)dwAddress, 0x10);

			vHookContext.push_back(cxt);

			DWORD* startStub = (DWORD*)&szHookSection[dwHookCount * 0x20];
			dwHookCount++;

			for (int i = 0; i < 7; i++)
				startStub[i] = 0x60000000;
			startStub[7] = 0x4E800020;

			Hooking::HookFunctionStart((DWORD*)dwAddress, startStub, (DWORD)pHookFunction);

			*pTrampoline = (T)startStub;

			return true;
		}

		return false;
	}
};
