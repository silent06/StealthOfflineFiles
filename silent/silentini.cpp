#include "stdafx.h"
#define INI_Path "Hdd:\\silent Cache\\silent.ini"
#define XML_Path "Hdd:\\silent Cache\\CustomXML.ini"
CSimpleIniA ini;
bool INI::CustomUI;
bool INI::Bypass;
bool INI::Cheats;
bool INI::Rainbow;
bool INI::MSPspoof;
bool INI::CustomXml;

void INI::Create() {

	BYTE INIData[98] = {
0x5B, 0x53, 0x65, 0x74, 0x74, 0x69, 0x6E, 0x67, 0x73, 0x5D, 0x0D, 0x0A, 0x43, 0x75, 0x73, 0x74,
0x6F, 0x6D, 0x5F, 0x55, 0x49, 0x20, 0x3D, 0x20, 0x54, 0x72, 0x75, 0x65, 0x0D, 0x0A, 0x58, 0x5F,
0x43, 0x68, 0x65, 0x61, 0x74, 0x73, 0x20, 0x3D, 0x20, 0x54, 0x72, 0x75, 0x65, 0x0D, 0x0A, 0x58,
0x5F, 0x42, 0x79, 0x70, 0x61, 0x73, 0x73, 0x20, 0x3D, 0x20, 0x54, 0x72, 0x75, 0x65, 0x0D, 0x0A,
0x58, 0x5F, 0x52, 0x61, 0x69, 0x6E, 0x62, 0x6F, 0x77, 0x3D, 0x20, 0x46, 0x41, 0x4C, 0x53, 0x45,
0x0D, 0x0A, 0x58, 0x5F, 0x4D, 0x53, 0x50, 0x53, 0x70, 0x6F, 0x6F, 0x66, 0x3D, 0x20, 0x54, 0x72,
0x75, 0x65
	};

	SWriteFile(INI_Path, INIData, sizeof(INIData));
	Read();
}
void INI::CreateIP() {

	BYTE INIData[141] = {
0x5B, 0x58, 0x4D, 0x4C, 0x5D, 0x0D, 0x0A, 0x43, 0x75, 0x73, 0x74, 0x6F, 0x6D, 0x49, 0x50, 0x41,
0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x20, 0x3D, 0x20, 0x31, 0x39, 0x32, 0x2E, 0x39, 0x39, 0x2E,
0x35, 0x38, 0x2E, 0x31, 0x38, 0x34, 0x0D, 0x0A, 0x57, 0x65, 0x6C, 0x63, 0x6F, 0x6D, 0x65, 0x54,
0x6F, 0x20, 0x3D, 0x20, 0x57, 0x65, 0x4C, 0x63, 0x4F, 0x4D, 0x45, 0x20, 0x54, 0x6F, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x47, 0x72, 0x65, 0x65, 0x74, 0x69, 0x6E, 0x67, 0x20, 0x3D,
0x20, 0x53, 0x69, 0x6C, 0x65, 0x6E, 0x74, 0x20, 0x4C, 0x69, 0x56, 0x65, 0x20, 0x20, 0x20, 0x20,
0x20, 0x20, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x4F, 0x70, 0x65, 0x6E, 0x20, 0x3D, 0x20, 0x48, 0x6F,
0x6F, 0x6B, 0x61, 0x68, 0x20, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x43, 0x6C, 0x6F, 0x73, 0x65, 0x20,
0x3D, 0x20, 0x43, 0x6C, 0x6F, 0x73, 0x65, 0x47, 0x75, 0x59, 0x20, 0x20, 0x20
	};

	SWriteFile(INI_Path, INIData, sizeof(INIData));
	//ReadIP();
}
void INI::Init() {
	ini.SetUnicode();
	FileExists(INI_Path) ? Read() : Create();
	FileExists(XML_Path) ? ReadIP() : CreateIP();
}
void INI::ReadIP() {
	ini.LoadFile(XML_Path);

}
void INI::UpdateSettings() {

	ini.SetboolValue("Settings", "Custom_UI", CustomUI);
	ini.SetboolValue("Settings", "X_Cheats", Cheats);
	ini.SetboolValue("Settings", "X_Bypass", Bypass);
	ini.SetboolValue("Settings", "X_Rainbow", Rainbow);
	ini.SetboolValue("Settings", "X_MSPSpoof", MSPspoof);
	ini.SetboolValue("Settings", "X_CustomXml", CustomXml);

	ini.SaveFile(INI_Path);
}
void INI::Read() {
	ini.LoadFile(INI_Path);

	CustomUI = ini.GetboolValue("Settings", "Custom_UI");
	Cheats = ini.GetboolValue("Settings", "X_Cheats");
	Bypass = ini.GetboolValue("Settings", "X_Bypass");
	Rainbow = ini.GetboolValue("Settings", "X_Rainbow");
	MSPspoof = ini.GetboolValue("Settings", "X_MSPSpoof");
	CustomXml = ini.GetboolValue("Settings", "X_CustomXml");
}