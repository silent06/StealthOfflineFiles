#include "stdafx.h"

CXIniRW XIniRW;

#pragma region File Handling

fstream _RFile;
ofstream _WFile;

bool CXIniRW::ROpenINI(const char* fileName)
{
	if (_RFile.is_open()) {
		printf("Error: File %s is already open.\n");
		return false;
	}

	_RFile = fstream(fileName, std::ios::in);

	if (!_RFile.is_open()) {
		printf("Error: File %s was not able to be opened.\n");
		return false;
	}

	return true;
}

bool CXIniRW::RCloseINI()
{
	if (!_RFile.is_open()) {
		printf("Error: File is not opened.\n");
		return false;
	}

	_RFile.close();
	return true;
}

bool CXIniRW::WOpenINI(const char* fileName)
{
	if (_WFile.is_open()) {
		printf("Error: File %s is already open.\n");
		return false;
	}

	_WFile = ofstream(fileName, ofstream::out | ofstream::trunc);

	if (!_WFile.is_open()) {
		printf("Error: File %s was not able to be opened.\n");
		return false;
	}

	return true;
}

bool CXIniRW::WCloseINI()
{
	if (!_WFile.is_open()) {
		printf("Error: File is not opened.\n");
		return false;
	}

	_WFile.close();
	return true;
}

#pragma endregion

#pragma region Reading

bool CXIniRW::GetValue(const char* Key, const char* Member, string& szReturn) {
	string szLine;
	getline(_RFile, szLine);

	if ((szLine.substr(0, 1)) == ";" || szLine.empty())
		return false;

	string::size_type dwGroupOffset = szLine.find_first_of('.');
	string::size_type dwValueOffset = szLine.find_first_of('=');

	string szKey = szLine.substr(0, dwGroupOffset);

	if (strcmp(szKey.c_str(), Key))
		return false;

	string szMember = szLine.substr(dwGroupOffset + 1, (dwValueOffset - dwGroupOffset) - 1);

	if (strcmp(szMember.c_str(), Member))
		return false;

	szReturn = szLine.substr(dwValueOffset + 1, szLine.length() - (dwValueOffset + 1));
	return true;
}

int CXIniRW::ReadInt(const char* Key, const char* Member)
{
	if (!_RFile.is_open()) {
		printf("Error: Ini not opened.\n");
		return 0;
	}

	_RFile.clear();
	_RFile.seekg(0, ios::beg);

	while (_RFile.good()) {
		string szValue;
		if (!GetValue(Key, Member, szValue))
			continue;

		return atoi(szValue.c_str());
	}

	return 0;
}

float CXIniRW::ReadFloat(const char* Key, const char* Member)
{
	if (!_RFile.is_open()) {
		printf("Error: Ini not opened.\n");
		return 0;
	}

	_RFile.clear();
	_RFile.seekg(0, ios::beg);

	while (_RFile.good()) {
		string szValue;
		if (!GetValue(Key, Member, szValue))
			continue;

		return (float)atof(szValue.c_str());
	}

	return 0.0f;
}

string CXIniRW::ReadString(const char* Key, const char* Member)
{
	if (!_RFile.is_open()) {
		printf("Error: Ini not opened.\n");
		return 0;
	}

	_RFile.clear();
	_RFile.seekg(0, ios::beg);

	while (_RFile.good()) {
		string szValue;
		if (!GetValue(Key, Member, szValue))
			continue;

		return szValue;
	}

	return "";
}

bool CXIniRW::ReadBool(const char* Key, const char* Member)
{
	if (!_RFile.is_open()) {
		printf("Error: Ini not opened.\n");
		return 0;
	}

	_RFile.clear();
	_RFile.seekg(0, ios::beg);

	while (_RFile.good()) {
		string szValue;
		if (!GetValue(Key, Member, szValue))
			continue;

		return !strcmp(szValue.c_str(), "true");
	}

	return false;
}

#pragma endregion

#pragma region Writing

void CXIniRW::WriteInt(const char* Group, const char* Member, int Value)
{
	if (!_WFile.is_open()) {
		printf("Error: Ini not opened.\n");
		return;
	}

	char szWriteBuffer[256];
	_snprintf(szWriteBuffer, 256, "%s.%s=%i\n", Group, Member, Value);

	_WFile << szWriteBuffer;
}

void CXIniRW::WriteFloat(const char* Group, const char* Member, float Value)
{
	if (!_WFile.is_open()) {
		printf("Error: Ini not opened.\n");
		return;
	}

	char szWriteBuffer[256];
	_snprintf(szWriteBuffer, 256, "%s.%s=%f\n", Group, Member, Value);

	_WFile << szWriteBuffer;
}

void CXIniRW::WriteString(const char* Group, const char* Member, string Value)
{
	if (!_WFile.is_open()) {
		printf("Error: Ini not opened.\n");
		return;
	}

	char szWriteBuffer[256];
	_snprintf(szWriteBuffer, 256, "%s.%s=%s\n", Group, Member, Value.c_str());

	_WFile << szWriteBuffer;
}

void CXIniRW::WriteBool(const char* Group, const char* Member, bool Value)
{
	if (!_WFile.is_open()) {
		printf("Error: Ini not opened.\n");
		return;
	}

	char szWriteBuffer[256];
	_snprintf(szWriteBuffer, 256, "%s.%s=%s\n", Group, Member, Value ? "true" : "false");

	_WFile << szWriteBuffer;
}
#pragma endregion
#pragma endregion