#include "stdafx.h"
BOOL pfShow = (BOOL)0xDEADBEEF; BOOL pfShowMovie;
BOOL pfPlaySound; BOOL pfShowIPTV;
/*Mount Path*/
PCHAR PATH_KV = "";
PCHAR PATH_CPU_BIN = "";
PCHAR PATH_XEX = "";
PCHAR Path_SysCache0 = "";
PCHAR Path_SysCache1 = "";
BYTE CurrentMACAddress[0x6] = { 0 };
BYTE SpoofedMACAddress[6] = { 0, 0x22, 0x48 };
BOOL DashLoaded = FALSE;
BYTE CPUKey[0x10] = { 0 };
BYTE KVCPUKey[0x10] = { 0 };
BYTE CPUKeyDigest[0x14] = { 0 };
BYTE KVDigest[0x14] = { 0 };
KEY_VAULT KV = { 0 };
BOOL Crl = FALSE, Fcrt = FALSE, kvtype = FALSE;
DWORD UpdateSequence = 0x00000008;
DWORD dwUpdateSequence;
DWORD kvCbFlag;
DWORD kvHardwareFlag;
QWORD kvPcieFlag;
BYTE kvFuseKey[0xC];
BYTE spoofSMCKey[0x5];
BYTE coronaKey[0xC] = { 0x9B, 0x48, 0x47, 0xE3, 0x9F, 0xE5, 0x46, 0x46, 0xF0, 0xA9, 0x9E, 0xB1 };
BYTE falconKey[0xC] = { 0x8B, 0x0C, 0xEA, 0xD4, 0x71, 0x54, 0xFB, 0x7B, 0xB8, 0xBD, 0xEC, 0x18 };
BYTE jasperKey[0xC] = { 0xED, 0x61, 0xD1, 0x54, 0xB2, 0x31, 0x35, 0x99, 0x0D, 0x90, 0xBD, 0xBC };
BYTE trinityKey[0xC] = { 0x78, 0xCB, 0xFC, 0x2F, 0x52, 0xA3, 0xBA, 0xF8, 0x92, 0x45, 0x8D, 0x65 };
BYTE zephyrKey[0xC] = { 0x1E, 0x89, 0x8B, 0xA1, 0x55, 0xB5, 0xAF, 0x74, 0xAA, 0x78, 0xAD, 0x0B };
BYTE xenonKey[0xC] = { 0xD7, 0x3E, 0xED, 0x7E, 0x5A, 0xF8, 0xB1, 0xBB, 0xB2, 0xE0, 0x26, 0x95 };
BYTE coronaSMC[5] = { 0x12, 0x62, 0x02, 0x05, 0x00 };
BYTE trinitySMC[5] = { 0x12, 0x51, 0x03, 0x01, 0x00 };
BYTE jasperSMC[5] = { 0x12, 0x41, 0x02, 0x03, 0x00 };
BYTE falconSMC[5] = { 0x12, 0x31, 0x01, 0x06, 0x00 };
BYTE zephyrSMC[5] = { 0x12, 0x21, 0x01, 0x09, 0x00 };
BYTE xenonSMC[5] = { 0x12, 0x12, 0x01, 0x33, 0x00 };
pDmSetMemory DevSetMemory = NULL;
CONST BYTE HvxPeekPokeExp[0x2F0] = {
	0x48, 0x58, 0x50, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x34, 0x1F, 0xD6, 0xDA,
	0x2F, 0xCA, 0xA8, 0x17, 0xF0, 0x30, 0xCC, 0x44, 0x0A, 0x41, 0xFA, 0x7C, 0xA0, 0xC1, 0xFD, 0x33,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x7A, 0x02, 0x59, 0x43, 0x9E, 0xE6, 0x93, 0xD5, 0x01, 0xC9, 0x48, 0x4D, 0xB2, 0xBF, 0x9D, 0x18,
	0xA9, 0x16, 0x5E, 0xFF, 0x1E, 0xD5, 0xB6, 0xA8, 0x79, 0x60, 0xA8, 0x2F, 0xC1, 0x8D, 0x20, 0x8A,
	0xEB, 0x46, 0xC3, 0x01, 0xEC, 0xC4, 0xDB, 0xDF, 0xA1, 0x04, 0xD1, 0xDF, 0x23, 0x69, 0x5E, 0xCC,
	0x50, 0xC3, 0xF4, 0xDD, 0xA4, 0x80, 0x7D, 0x05, 0x2D, 0x57, 0xFF, 0x60, 0xA5, 0x58, 0x69, 0x27,
	0x9A, 0x33, 0x70, 0xE8, 0xC2, 0x82, 0xDC, 0xDA, 0xE2, 0x4D, 0xE1, 0xF8, 0xA1, 0xD2, 0xCC, 0x8D,
	0x98, 0x05, 0xD1, 0xA3, 0x2E, 0x37, 0x06, 0x0F, 0xF7, 0xEF, 0x70, 0xEF, 0x28, 0xD7, 0xAE, 0xD5,
	0x5B, 0x19, 0x1B, 0x13, 0x50, 0x0D, 0x15, 0x00, 0x92, 0x01, 0xEE, 0x38, 0xA7, 0x61, 0xB1, 0xA1,
	0x27, 0xBF, 0xB0, 0x42, 0x0F, 0x07, 0xC3, 0x8F, 0x78, 0xAD, 0xAF, 0x87, 0x8F, 0x34, 0x8A, 0xA6,
	0x69, 0x7D, 0x40, 0xB6, 0x5C, 0x9E, 0x01, 0xEC, 0x9F, 0x5E, 0x78, 0x30, 0x09, 0x5A, 0x21, 0xFF,
	0x35, 0x8C, 0x13, 0xBE, 0xBC, 0x92, 0x67, 0xE3, 0x17, 0x0B, 0x09, 0x1C, 0xE2, 0x9D, 0xEC, 0xFD,
	0xFB, 0x6C, 0x49, 0x3A, 0xCC, 0xE7, 0x99, 0xB6, 0xB3, 0x8A, 0x8F, 0xEF, 0xF7, 0xA0, 0x28, 0x4F,
	0x72, 0xC7, 0x3D, 0xD7, 0xCC, 0xEB, 0xB2, 0x1B, 0x74, 0x93, 0xD7, 0x02, 0x05, 0xD5, 0xE1, 0x25,
	0x35, 0xD7, 0xE0, 0x50, 0xEA, 0xCF, 0x82, 0x69, 0xE3, 0x3B, 0x6F, 0xFA, 0x13, 0xF0, 0x5B, 0xD9,
	0x1A, 0xB0, 0xD3, 0x0B, 0x85, 0x4D, 0x6A, 0xFC, 0x31, 0x45, 0xC3, 0xA3, 0xFA, 0x7E, 0xDA, 0x93,
	0x84, 0xD4, 0xE7, 0xFA, 0xAB, 0x7C, 0x22, 0x96, 0x54, 0x69, 0x7F, 0xC9, 0xF8, 0xC4, 0x5A, 0xC2,
	0x82, 0x99, 0x34, 0x46, 0x81, 0x6F, 0x06, 0x33, 0x19, 0x94, 0x74, 0xA4, 0x76, 0x02, 0x4F, 0xB9,
	0x48, 0x56, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x01, 0x90,
	0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x7D, 0x88, 0x02, 0xA6, 0xFB, 0xE1, 0xFF, 0xF0, 0xF9, 0x81, 0xFF, 0xF8, 0x94, 0x21, 0xFF, 0x00,
	0x7C, 0x9F, 0x23, 0x78, 0x2C, 0x1F, 0x00, 0x00, 0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x01,
	0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x02, 0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x03,
	0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x0A, 0x41, 0x82, 0x00, 0x64, 0x2C, 0x1F, 0x00, 0x05,
	0x41, 0x82, 0x00, 0xD4, 0x2C, 0x1F, 0x00, 0x06, 0x41, 0x82, 0x00, 0xD4, 0x2C, 0x1F, 0x00, 0x07,
	0x41, 0x82, 0x00, 0xD4, 0x2C, 0x1F, 0x00, 0x08, 0x41, 0x82, 0x00, 0xD4, 0x2C, 0x1F, 0x00, 0x0B,
	0x40, 0x80, 0x00, 0x00, 0x80, 0x60, 0x00, 0x4C, 0x7C, 0x62, 0x1A, 0x14, 0x80, 0x63, 0x00, 0x08,
	0x7C, 0x69, 0x03, 0xA6, 0x7C, 0xC3, 0x33, 0x78, 0x38, 0x80, 0x00, 0x01, 0x4E, 0x80, 0x04, 0x21,
	0x7C, 0x66, 0x1B, 0x78, 0x7C, 0xE9, 0x03, 0xA6, 0x2C, 0x1F, 0x00, 0x04, 0x41, 0x82, 0x00, 0x6C,
	0x2C, 0x1F, 0x00, 0x09, 0x41, 0x82, 0x00, 0xA0, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x05,
	0x7C, 0xA6, 0x2B, 0x78, 0x3C, 0x80, 0x7C, 0x60, 0x50, 0xA6, 0x54, 0x6A, 0x60, 0x84, 0x02, 0xA6,
	0x50, 0xC4, 0x32, 0xE8, 0x7C, 0x68, 0x02, 0xA6, 0x38, 0x63, 0x00, 0x30, 0x90, 0x83, 0x00, 0x00,
	0x7C, 0x00, 0x18, 0x6C, 0x7C, 0x00, 0x1F, 0xAC, 0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C,
	0x7C, 0x79, 0x4A, 0xA6, 0x48, 0x00, 0x00, 0x98, 0x88, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0x90,
	0xA0, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0x88, 0x80, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0x80,
	0xE8, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0x78, 0x8B, 0xE5, 0x00, 0x00, 0x9B, 0xE6, 0x00, 0x00,
	0x38, 0xA5, 0x00, 0x01, 0x38, 0xC6, 0x00, 0x01, 0x42, 0x00, 0xFF, 0xF0, 0x38, 0x60, 0x00, 0x00,
	0x48, 0x00, 0x00, 0x5C, 0x98, 0xC5, 0x00, 0x00, 0x48, 0x00, 0x00, 0x40, 0xB0, 0xC5, 0x00, 0x00,
	0x48, 0x00, 0x00, 0x38, 0x90, 0xC5, 0x00, 0x00, 0x48, 0x00, 0x00, 0x30, 0xF8, 0xC5, 0x00, 0x00,
	0x48, 0x00, 0x00, 0x28, 0x8B, 0xE6, 0x00, 0x00, 0x9B, 0xE5, 0x00, 0x00, 0x7C, 0x00, 0x28, 0x6C,
	0x7C, 0x00, 0x2F, 0xAC, 0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C, 0x38, 0xA5, 0x00, 0x01,
	0x38, 0xC6, 0x00, 0x01, 0x42, 0x00, 0xFF, 0xE0, 0x38, 0x60, 0x00, 0x00, 0x7C, 0x00, 0x28, 0x6C,
	0x7C, 0x00, 0x2F, 0xAC, 0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C, 0x38, 0x21, 0x01, 0x00,
	0xEB, 0xE1, 0xFF, 0xF0, 0xE9, 0x81, 0xFF, 0xF8, 0x7D, 0x88, 0x03, 0xA6, 0x4E, 0x80, 0x00, 0x20
};


DWORD ResolveFunction2(PCHAR Module, DWORD Ordinal)
{
	HANDLE Handle = 0;
	if (NT_SUCCESS(XexGetModuleHandle(Module, &Handle)))
	{
		DWORD Address = 0;
		if (NT_SUCCESS(XexGetProcedureAddress(Handle, Ordinal, &Address))) return (Address != 0) ? Address : 0;
	}
	return 0;
}
VOID PatchInJump(PDWORD Address, DWORD Destination, BOOL Linked)
{
	if (Destination & 0x8000) Address[0] = (0x3D600000 + (((Destination >> 16) & 0xFFFF) + 1));
	else Address[0] = (0x3D600000 + ((Destination >> 16) & 0xFFFF));
	Address[1] = (0x396B0000 + (Destination & 0xFFFF));
	Address[2] = 0x7D6903A6;
	Address[3] = (0x4E800420 | Linked);
	doSync(Address);
}
DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, PCHAR Import, DWORD Ordinal, DWORD Destination) {
	DWORD OrdinalAddress = ResolveFunction2(Import, Ordinal);
	if (OrdinalAddress == 0) return S_FALSE;
	PXEX_IMPORT_DESCRIPTOR ImportDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(Module->XexHeaderBase, XEX_HEADER_IMPORTS);
	if (ImportDesc == 0) return S_FALSE;
	PXEX_IMPORT_TABLE ImportTable = (PXEX_IMPORT_TABLE)((PBYTE)ImportDesc + sizeof(*ImportDesc) + ImportDesc->NameTableSize);
	for (DWORD i = 0; i < ImportDesc->ModuleCount; i++) {
		for (WORD j = 0; j < ImportTable->ImportCount; j++) {
			DWORD StubAddress = *((PDWORD)ImportTable->ImportStubAddr[j]);
			if (OrdinalAddress != StubAddress) continue;
			StubAddress = (DWORD)ImportTable->ImportStubAddr[j + 1];
			PatchInJump((PDWORD)StubAddress, Destination, FALSE);
			j = ImportTable->ImportCount;
		}
		ImportTable = (PXEX_IMPORT_TABLE)((PBYTE)ImportTable + ImportTable->TableSize);
	}
	return S_OK;
}
DWORD PatchModuleImport(PCHAR Module, PCHAR Import, DWORD Ordinal, DWORD Destination)
{
	PLDR_DATA_TABLE_ENTRY Handle = (PLDR_DATA_TABLE_ENTRY)GetModuleHandle(Module);
	return (Handle != 0) ? PatchModuleImport(Handle, Import, Ordinal, Destination) : S_FALSE;
}
BOOL FileExists(LPCSTR lpFileName) {
	if (GetFileAttributes(lpFileName) == -1) {
		DWORD lastError = GetLastError();
		if (lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
			return FALSE;
	}return TRUE;
}
BOOL SReadFile(CONST PCHAR FilePath, MemoryBuffer &Buffer)
{
	HANDLE Handle = CreateFile(FilePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (Handle == INVALID_HANDLE_VALUE) return FALSE;
	DWORD FileSize = GetFileSize(Handle, 0);
	PBYTE FileBuffer = (PBYTE)malloc(FileSize);
	if (FileBuffer == 0)
	{
		CloseHandle(Handle);
		return FALSE;
	}
	DWORD ReadSize = 0;
	if (!ReadFile(Handle, FileBuffer, FileSize, &ReadSize, 0))
	{
		free(FileBuffer);
		CloseHandle(Handle);
		return FALSE;
	}
	else if (ReadSize != FileSize)
	{
		free(FileBuffer);
		CloseHandle(Handle);
		return FALSE;
	}
	Buffer.Add(FileBuffer, FileSize);
	free(FileBuffer);
	CloseHandle(Handle);
	return TRUE;
}
BOOL SWriteFile(CONST PCHAR FilePath, CONST PVOID Buffer, DWORD Size)
{
	DWORD WriteSize = Size;
	HANDLE Handle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (Handle == INVALID_HANDLE_VALUE) return FALSE;
	if (!WriteFile(Handle, Buffer, WriteSize, &WriteSize, 0))
	{
		CloseHandle(Handle);
		return FALSE;
	}
	CloseHandle(Handle);
	return (WriteSize == Size);
}
BYTE char2byte(char input)
{
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	return 0;
}
DWORD SetConsoleType() {
	BYTE moboSerialByte = 0;
	moboSerialByte = (((char2byte(KV.ConsoleCertificate.ConsolePartNumber[2]) << 4) & 0xF0) | ((char2byte(KV.ConsoleCertificate.ConsolePartNumber[3]) & 0x0F)));
	kvCbFlag = 0x0304000E;
	dwUpdateSequence = 0x0000000A; 
	kvHardwareFlag = 0x50000207;
	kvPcieFlag = 0x4158019002000380;
	memcpy(kvFuseKey, coronaKey, 0xC);
	memcpy(spoofSMCKey, coronaSMC, 0x5);

	if (moboSerialByte < 0x10) {
		kvCbFlag = 0x010C0FFB;
		dwUpdateSequence = 0x0000000F; 
		kvHardwareFlag = 0x00000207;
		kvPcieFlag = 0x2158023102000380;
		memcpy(kvFuseKey,xenonKey, 0xC);
		memcpy(spoofSMCKey, xenonSMC, 0x5);
		return 0;
	}
	else if (moboSerialByte < 0x14) {
		kvCbFlag = 0x010B0524;
		dwUpdateSequence = 0x0000000E; 
		kvHardwareFlag = 0x10000207;
		kvPcieFlag = 0x2158023102000380;
		memcpy(kvFuseKey, zephyrKey, 0xC);
		memcpy(spoofSMCKey, zephyrSMC, 0x5);
		return 0;
	}
	else if (moboSerialByte < 0x18) {
		kvCbFlag = 0x010C0AD8;
		dwUpdateSequence = 0x0000000D; 
		kvHardwareFlag = 0x20000207;
		kvPcieFlag = 0x2158023102000380;
		memcpy(kvFuseKey, falconKey, 0xC);
		memcpy(spoofSMCKey, falconSMC, 0x5);
		return 0;
	}
	else if (moboSerialByte < 0x52) {
		kvCbFlag = 0x010C0AD0;
		dwUpdateSequence = 0x0000000C; 
		kvHardwareFlag = 0x30000207;
		kvPcieFlag = 0x3158116002000380;
		memcpy(kvFuseKey, jasperKey, 0xC);
		memcpy(spoofSMCKey, jasperSMC, 0x5);
		return 0;
	}
	else if (moboSerialByte < 0x58) {
		kvCbFlag = 0x0304000D;
		dwUpdateSequence = 0x0000000B; 
		kvHardwareFlag = 0x40000207;
		kvPcieFlag = 0x4158016002000380;
		memcpy(kvFuseKey, trinityKey, 0xC);
		memcpy(spoofSMCKey, trinitySMC, 0x5);
		return 0;
	}
	return 0;
}
BYTE RetailRoamableObfuscationKey[0x10] = { 0xE1, 0xBC, 0x15, 0x9C, 0x73, 0xB1, 0xEA, 0xE9, 0xAB, 0x31, 0x70, 0xF3, 0xAD, 0x47, 0xEB, 0xF3 };
BOOL CheckKVType()
{
	for (DWORD x = 0; x < 0x100; x++)
	{
		if (KV.KeyVaultSignature[x] != 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}
PBYTE GetKeyVault()
{
	QWORD KVAddress = HvxPeekQWORD(0x00000002000163C0);
	if (HvxPeekBytes(KVAddress, &KV, sizeof(KEY_VAULT)) != S_OK) return 0;
	return (PBYTE)&KV;
}
BOOL SetKeyVault()
{
	MemoryBuffer mbCPUKey, mbKV;
	if (FileExists(PATH_CPU_BIN))
	{
		if (!SReadFile(PATH_CPU_BIN, mbCPUKey)) return FALSE;
		memcpy(KVCPUKey, mbCPUKey.GetBuffer(), 0x10);
	}
	else
	{
		XeCryptRandom(KVCPUKey, 0x10);
		if (!SWriteFile(PATH_CPU_BIN, KVCPUKey, 0x10)) return FALSE;
	}

	XeCryptSha(KVCPUKey, 0x10, NULL, NULL, NULL, NULL, CPUKeyDigest, 0x14);

	if (FileExists(PATH_KV))
	{
		if (!SReadFile(PATH_KV, mbKV)) return FALSE;
		memcpy(&KV, mbKV.GetBuffer(), 0x4000);
	}
	else
	{
		memcpy(&KV, GetKeyVault(), 0x4000);
	}

	if (SetConsoleType() != ERROR_SUCCESS) {
		return E_FAIL;
	}

	if (kvCbFlag == 0 || dwUpdateSequence == 0 || kvHardwareFlag == 0 || kvPcieFlag == 0 || kvFuseKey == 0 || spoofSMCKey == 0) {
		return E_FAIL;
	}
	
	memcpy((PVOID)0x8E03AA54, kvFuseKey, 0xC);

	kvtype = CheckKVType();

	QWORD KV_ADDR = 0x7601EE0000;
	HvxPeekBytes((KV_ADDR + 0xD0), &KV.ConsoleObfuscationKey, 0x40);
	memcpy(KV.RoamableObfuscationKey, RetailRoamableObfuscationKey, 0x10);
	HvxPokeBytes(KV_ADDR, &KV, 0x4000);

	memcpy((PVOID)0x8E03A000, &KV.ConsoleCertificate, 0x1A8);
	memcpy((PVOID)0x8E038020, &KV.ConsoleCertificate.ConsoleId.abData, 5);
	XeCryptSha((PBYTE)0x8E038014, 0x3EC, NULL, NULL, NULL, NULL, (PBYTE)0x8E038000, 0x14);

	XECRYPT_HMACSHA_STATE HMACSHA = { 0 };
	XeCryptHmacShaInit(&HMACSHA, KVCPUKey, 0x10);
	XeCryptHmacShaUpdate(&HMACSHA, (PBYTE)&KV.OddFeatures, 0xD4);
	XeCryptHmacShaUpdate(&HMACSHA, (PBYTE)&KV.DvdKey, 0x1CF8);
	XeCryptHmacShaUpdate(&HMACSHA, (PBYTE)&KV.CardeaCertificate, 0x2108);
	XeCryptHmacShaFinal(&HMACSHA, KVDigest, 0x14);

	Fcrt = ((KV.OddFeatures & ODD_POLICY_FLAG_CHECK_FIRMWARE) != 0);

	SpoofedMACAddress[0] = 0x00;
	SpoofedMACAddress[1] = 0x22;
	SpoofedMACAddress[2] = 0x48;
	SpoofedMACAddress[3] = KV.ConsoleCertificate.ConsoleId.asBits.MacIndex3;
	SpoofedMACAddress[4] = KV.ConsoleCertificate.ConsoleId.asBits.MacIndex4;
	SpoofedMACAddress[5] = KV.ConsoleCertificate.ConsoleId.asBits.MacIndex5;

		if (NT_SUCCESS(ExGetXConfigSetting(XCONFIG_SECURED_CATEGORY, XCONFIG_SECURED_MAC_ADDRESS, CurrentMACAddress, 6, 0) >= 0))
			if (memcmp(CurrentMACAddress, SpoofedMACAddress, 6) != 0)
				if (NT_SUCCESS(ExSetXConfigSetting(XCONFIG_SECURED_CATEGORY, XCONFIG_SECURED_MAC_ADDRESS, SpoofedMACAddress, 6) >= 0))
					HalReturnToFirmware(HalFatalErrorRebootRoutine);

		DWORD Temp = 0;
		XeCryptSha(SpoofedMACAddress, 6, 0, 0, 0, 0, (PBYTE)&Temp, 4);
		UpdateSequence |= (Temp & ~0xFF);
	

	XamCacheReset(XAM_CACHE_TICKETS);
	return TRUE;
}

BOOL InitializeHvxPeekPoke()
{
	PVOID pBuffer = XPhysicalAlloc(0x1000, MAXULONG_PTR, 0, PAGE_READWRITE);
	DWORD Address = (DWORD)MmGetPhysicalAddress(pBuffer);
	memset(pBuffer, 0, 0x1000);
	memcpy(pBuffer, HvxPeekPokeExp, sizeof(HvxPeekPokeExp));
	DWORD Result = (DWORD)HvxExpansionInstall(Address, 0x1000);
	XPhysicalFree(pBuffer);
	return (Result == S_OK);
}
BYTE HvxPeekBYTE(QWORD Address) { return (BYTE)HvxExpansionCall(HvxPeekPokeExpID, PEEK_BYTE, Address); }
WORD HvxPeekWORD(QWORD Address) { return (WORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_WORD, Address); }
DWORD HvxPeekDWORD(QWORD Address) { return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_DWORD, Address); }
QWORD HvxPeekQWORD(QWORD Address) { return HvxExpansionCall(HvxPeekPokeExpID, PEEK_QWORD, Address); }
DWORD HvxPeekBytes(QWORD Address, PVOID Buffer, DWORD Size)
{
	PVOID pBuffer = XPhysicalAlloc(Size, MAXULONG_PTR, 0, PAGE_READWRITE);
	memset(pBuffer, 0, Size);
	DWORD Result = (DWORD)HvxExpansionCall(HvxPeekPokeExpID, PEEK_BYTES, Address, (QWORD)MmGetPhysicalAddress(pBuffer), Size);
	if (Result == S_OK) memcpy(Buffer, pBuffer, Size);
	XPhysicalFree(pBuffer);
	return Result;
}
DWORD HvxPokeBYTE(QWORD Address, BYTE Value) { return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_BYTE, Address, Value); }
DWORD HvxPokeWORD(QWORD Address, WORD Value) { return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_WORD, Address, Value); }
DWORD HvxPokeDWORD(QWORD Address, DWORD Value) { return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_DWORD, Address, Value); }
DWORD HvxPokeQWORD(QWORD Address, QWORD Value) { return (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_QWORD, Address, Value); }
DWORD HvxPokeBytes(QWORD Address, CONST PVOID Buffer, DWORD Size)
{
	PVOID pBuffer = XPhysicalAlloc(Size, MAXULONG_PTR, 0, PAGE_READWRITE);
	memcpy(pBuffer, Buffer, Size);
	DWORD Result = (DWORD)HvxExpansionCall(HvxPeekPokeExpID, POKE_BYTES, Address, (QWORD)MmGetPhysicalAddress(pBuffer), Size);
	XPhysicalFree(pBuffer);
	return Result;
}
char vaBuffer[0x1000];
char* va(const char* fmt, ...) {
	memset(vaBuffer, 0, 0x1000);
	va_list ap;
	va_start(ap, fmt);
	RtlVsprintf(vaBuffer, fmt, ap); // RtlVsprintf
	va_end(ap);
	return vaBuffer;
}
char* vaBuff(char* vaBuffer, int size, const char* fmt, ...) {
	memset(vaBuffer, 0, size);
	va_list ap;
	va_start(ap, fmt);
	RtlVsprintf(vaBuffer, fmt, ap);
	va_end(ap);
	return vaBuffer;
}
FARPROC ResolveFunction(CHAR* ModuleName, DWORD Ordinal)
{
	HMODULE mHandle = GetModuleHandle(ModuleName);
	return (mHandle == NULL) ? NULL : GetProcAddress(mHandle, (LPCSTR)Ordinal);
}
VOID toggleNotify(BOOL on) {
	if ((int)pfShow == 0xDEADBEEF)
		XNotifyUIGetOptions(&pfShow, &pfShowMovie, &pfPlaySound, &pfShowIPTV);
	if (!on) {
		XNotifyUISetOptions(pfShow, pfShowMovie, pfPlaySound, pfShowIPTV);
	}
	else {
		XNotifyUISetOptions(true, true, true, true);
	} Sleep(500);
}
VOID XNotifyDoQueueUI(PWCHAR pwszStringParam) {
	toggleNotify(true);
	XNotifyQueueUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, XUSER_INDEX_ANY, XNOTIFYUI_PRIORITY_HIGH, pwszStringParam, NULL);
	toggleNotify(false);
}
VOID NotifyPopup(PWCHAR myPWCHAR) {
	if (KeGetCurrentProcessType() != PROC_USER) {
		HANDLE th = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)XNotifyDoQueueUI, (LPVOID)myPWCHAR, CREATE_SUSPENDED, NULL);
		if (th == NULL) return; ResumeThread(th);
	}
	else XNotifyDoQueueUI(myPWCHAR);
}
HRESULT CreateSymbolicLink(CHAR* szDrive, CHAR* szDeviceName, BOOL System) {

	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, System ? "\\System??\\%s" : "\\??\\%s", szDrive);

	ANSI_STRING linkname, devicename;
	RtlInitAnsiString(&linkname, szDestinationDrive);
	RtlInitAnsiString(&devicename, szDeviceName);

	if (FileExists(szDrive))
		return S_OK;

	NTSTATUS status = ObCreateSymbolicLink(&linkname, &devicename);

	return (status >= 0) ? S_OK : S_FALSE;
}
HRESULT SetMemory(VOID* Destination, VOID* Source, DWORD Length) {
	if (DevSetMemory == NULL)
		DevSetMemory = (pDmSetMemory)ResolveFunction("xbdm.xex", 40);
	if (DevSetMemory == NULL) {
		memcpy(Destination, Source, Length);
		return ERROR_SUCCESS;
	}
	else {
		if (DevSetMemory(Destination, Length, Source, NULL) == MAKE_HRESULT(0, 0x2DA, 0))
			return ERROR_SUCCESS;
	}return E_FAIL;
}

HRESULT setMemory(VOID* Destination, DWORD Value)
{
	return SetMemory(Destination, &Value, 4);
}
VOID ComparePointerWrite(DWORD Address, DWORD Value)
{
	if (!MmIsAddressValid((PVOID)Address))
	{
		return;
	}

	if (*(DWORD*)Address == NULL)
	{
		return;
	}

	setMemory((PVOID)Address, Value);
}


DWORD applyPatches(VOID* patches)
{
	DWORD patchCount = 0;
	MemoryBuffer mbPatches;
	DWORD* patchData = (DWORD*)patches;

	if (patchData == NULL)
		return 0;

	while (*patchData != 0xFFFFFFFF) {
		BOOL inHvMode = (patchData[0] < 0x40000);
		QWORD patchAddr = inHvMode ? (0x200000000 * (patchData[0] / 0x10000)) + patchData[0] : (QWORD)patchData[0];

		SetMemory((VOID*)patchData[0], &patchData[2], patchData[1] * sizeof(DWORD));
		patchData += (patchData[1] + 2);
		patchCount++;
	}

	return patchCount;
}
BOOL TrayOpen()
{
	BYTE Input[0x10] = { 0 }, Output[0x10] = { 0 };
	Input[0] = 0xA;
	HalSendSMCMessage(Input, Output);
	return (Output[1] == 0x60);
}
PWCHAR vaS(const char* Text, ...) {
	CHAR Buffer[0x1000];
	CHAR MessageBuffer[0x100];
	static WCHAR Message[0x100];
	va_list pArgList;
	va_start(pArgList, Text);
	RtlVsprintf(Buffer, Text, pArgList);
	va_end(pArgList);
	RtlSprintf(MessageBuffer, Buffer);
	mbstowcs(Message, MessageBuffer, strlen(MessageBuffer) + 1);
	ZeroMemory(Buffer, sizeof(Buffer));
	ZeroMemory(MessageBuffer, sizeof(MessageBuffer));
	return Message;
}
PWCHAR toWCHAR(PCHAR Text, ...) {
	CHAR Buffer[0x1000];
	CHAR MessageBuffer[0x100];
	WCHAR Message[0x100];

	va_list pArgList;
	va_start(pArgList, Text);
	vsprintf(Buffer, Text, pArgList);
	va_end(pArgList);

	sprintf(MessageBuffer, Buffer);
	mbstowcs(Message, MessageBuffer, strlen(MessageBuffer) + 1);

	ZeroMemory(Buffer, sizeof(Buffer));
	ZeroMemory(MessageBuffer, sizeof(MessageBuffer));

	return Message;
}
PWCHAR LinkWChar(PWCHAR Text, ...) {
	WCHAR Buffer[0x1000], MessageBuffer[0x100];
	va_list pArgList;
	va_start(pArgList, Text);
	vswprintf(Buffer, Text, pArgList);
	va_end(pArgList);
	swprintf(MessageBuffer, Buffer);
	return MessageBuffer;
}
void __declspec(naked) GLPR(void) {
	__asm {
		std     r14, -0x98(sp)
		std     r15, -0x90(sp)
		std     r16, -0x88(sp)
		std     r17, -0x80(sp)
		std     r18, -0x78(sp)
		std     r19, -0x70(sp)
		std     r20, -0x68(sp)
		std     r21, -0x60(sp)
		std     r22, -0x58(sp)
		std     r23, -0x50(sp)
		std     r24, -0x48(sp)
		std     r25, -0x40(sp)
		std     r26, -0x38(sp)
		std     r27, -0x30(sp)
		std     r28, -0x28(sp)
		std     r29, -0x20(sp)
		std     r30, -0x18(sp)
		std     r31, -0x10(sp)
		stw     r12, -0x8(sp)
		blr
	}
}
VOID cTools::MakeThread(LPTHREAD_START_ROUTINE Address)
{
	HANDLE Handle = 0;
	ExCreateThread(&Handle, 0, 0, XapiThreadStartup, Address, 0, (EX_CREATE_FLAG_SUSPENDED | EX_CREATE_FLAG_SYSTEM | 0x18000424));
	XSetThreadProcessor(Handle, 4);
	SetThreadPriority(Handle, THREAD_PRIORITY_ABOVE_NORMAL);
	ResumeThread(Handle);
	CloseHandle(Handle);
}
DWORD cTools::RelinkGPLR(DWORD SFSOffset, DWORD* SaveStubAddress, DWORD* OriginalAddress)
{
	DWORD Instruction = NULL, Replacing;
	DWORD* Saver = (DWORD*)GLPR;
	if (SFSOffset & 0x2000000)
		SFSOffset |= 0xFC000000;
	Replacing = OriginalAddress[SFSOffset / 0x04];
	for (DWORD i = NULL; i < 0x14; i++)
	{
		if (Replacing == Saver[i])
		{
			DWORD NewAddress = (DWORD)&Saver[i] - (DWORD)SaveStubAddress;
			Instruction = (0x48000001 | (NewAddress & 0x03FFFFFC));
		}
	}
	return Instruction;
}
VOID cTools::HookFunctionStart(DWORD* Address, DWORD* SaveStub, DWORD Destination)
{
	if ((Address != NULL) && (SaveStub != NULL))
	{
		DWORD Relocation = (DWORD)(&Address[0x04]);
		SaveStub[0x00] = (0x3D600000 + ((Relocation >> 0x10) & 0xFFFF));
		SaveStub[0x01] = (0x616B0000 + (Relocation & 0xFFFF));
		SaveStub[0x02] = 0x7D6903A6;
		for (DWORD i = 0; i < 0x04; i++)
		{
			if ((Address[i] & 0x48000003) == 0x48000001)
				SaveStub[i + 0x03] = RelinkGPLR((Address[i] & ~0x48000003), &SaveStub[i + 0x03], &Address[i]);
			else SaveStub[i + 0x03] = Address[i];
		}
		SaveStub[0x07] = 0x4E800420;
		__dcbst(NULL, SaveStub);
		__sync();
		__isync();
		PatchInJump(Address, Destination, false);
	}
}
DWORD RelinkGPLR(DWORD SFSOffset, DWORD* SaveStubAddress, DWORD* OriginalAddress)
{
	DWORD Instruction = NULL, Replacing;
	DWORD* Saver = (DWORD*)GLPR;

	if (SFSOffset & 0x2000000)
		SFSOffset |= 0xFC000000;

	Replacing = OriginalAddress[SFSOffset / 0x04];
	for (DWORD i = NULL; i < 0x14; i++) {
		if (Replacing == Saver[i]) {
			DWORD NewAddress = (DWORD)&Saver[i] - (DWORD)SaveStubAddress;
			Instruction = (0x48000001 | (NewAddress & 0x03FFFFFC));
		}
	}
	return Instruction;
}
BOOL XenonPrivilegeHook(XEXPRIVS Privilege)
{
	if (Privilege == XEX_PRIVILEGE_INSECURE_SOCKETS)//turn on for Halo3 Sunrise
		return TRUE;

	if (Privilege == XEX_PRIVILEGE_TITLE_INSECURE_UTILITYDRIVE)
		return TRUE;

	if (Privilege == XEX_PRIVILEGE_ALLOW_BACKGROUND_DOWNLOAD)
		return TRUE;

	if (Privilege == XEX_PRIVILEGE_GAMEVOICE_REQUIRED_UI)
		return TRUE;

	return XexCheckExecutablePrivilege(Privilege);
}