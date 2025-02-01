#include "stdafx.h"
int R = 113, G = 36, B = 129, R2 = 0, G2 = 0, B2 = 0;
#define INIPath "Hdd:\\silent Cache\\RGB.ini"
//CHAR manifest[14] = "192.99.58.184";
char Xui::XManifestIp[0x24];
char Xui::XColors[0xa];
unsigned char Xui::XuiData[510669];
BOOL Xui::Custom;
//PCHAR CurrentIpAddress = ""; // op1
CHAR CurrentIpAddress[38]; // op2
CHAR WelcomeTo[19];
CHAR Greeting[20];
CHAR Open[10];
CHAR Close[11];
VOID WriteINI()
{
	CreateDirectoryA("HDD:\\silent Cache\\", NULL);
	if (XIniRW.WOpenINI(INIPath))
	{
		XIniRW.WriteInt("UI", "R", R);
		XIniRW.WriteInt("UI", "G", G);
		XIniRW.WriteInt("UI", "B", B);
		XIniRW.WriteInt("UI", "R2", R2);
		XIniRW.WriteInt("UI", "G2", G2);
		XIniRW.WriteInt("UI", "B2", B2);
		if (!XIniRW.WCloseINI());
	}
}
VOID ReadINI()
{
	if (XIniRW.ROpenINI(INIPath))
	{
		R = XIniRW.ReadInt("UI", "R");
		G = XIniRW.ReadInt("UI", "G");
		B = XIniRW.ReadInt("UI", "B");
		R2 = XIniRW.ReadInt("UI", "R2");
		G2 = XIniRW.ReadInt("UI", "G2");
		B2 = XIniRW.ReadInt("UI", "B2");
		if (!XIniRW.RCloseINI());
	}
}
void ReadConfig() {
	IniParse parse("HDD:\\silent Cache\\CustomXML.ini");
	if (parse.IsGood()) {
		auto IpAddrs = parse.ReadString("XML", "CustomIPAddress", CurrentIpAddress);
		auto XWelcome = parse.ReadString("XML", "WelcomeTo", WelcomeTo);
		auto XGreeting = parse.ReadString("XML", "Greeting", Greeting);
		auto xOpen = parse.ReadString("XML", "Open", Open);
		auto xClose = parse.ReadString("XML", "Close", Close);

		strcpy(CurrentIpAddress, IpAddrs);
		strcpy(WelcomeTo, XWelcome);
		strcpy(Greeting, XGreeting);
		strcpy(Open, xOpen);
		strcpy(Close, xClose);
		SWriteFile("HDD:\\silent Cache\\customIP.bin", CurrentIpAddress, 38);
		/*if (strlen(IpAddrs) <= 15) {

		}*/	
	}
	else
	{
		XNotifyQueueUI(XNOTIFYUI_TYPE_COMPLAINT, 0, 2, L"[Silent] INI Failed to read!", 0);
	}
	parse.ItemMap.clear();
}
/*
void UpdateConfig() {
	IniParse parse("HDD:\\silent Cache\\silent.ini");
	if (parse.IsGood()) {
		FILE* file = fopen("HDD:\\silent Cache\\silent.ini", Str("w+"));
		if (file) {

			parse.SetString(Str("UI"), Str("Manifest"), Xui::XManifestIp);
			parse.SetString(Str("UI"), Str("Colors"), Xui::XColors);
			parse.SetBool(Str("UI"), Str("CustomUi"), Xui::Custom);
			auto sections = parse.GetSections();
			for (int i = 0; i < sections.size(); i++) {
				fprintf(file, Str("[%s]\n"), sections[i].c_str());

				auto data = parse.GetDataFromSection(sections[i].c_str());
				for (int j = 0; j < data.size(); j++) {
					fprintf(file, Str("%s = %s\n"), data[j].first.c_str(), data[j].second.c_str());
				}

				data.clear();

				if (i != sections.size() - 1) {
					fprintf(file, Str("\n"));
				}
			}

			sections.clear();
		}

		parse.ItemMap.clear();

		fclose(file);
	}
}
void InstallDefaultConfig() {
	IniParse parse;
	parse.SetString(Str("UI"), Str("Manifest"), Str("assets.silent.hosted.nfoservers.com"));
	parse.SetString(Str("UI"), Str("Colors"), Str("none"));
	parse.SetBool(Str("UI"), Str("CustomUi"), true);
	FILE* file = fopen("HDD:\\silent Cache\\silent.ini", Str("w+"));
	if (file) {
		auto sections = parse.GetSections();
		for (int i = 0; i < sections.size(); i++) {
			fprintf(file, Str("[%s]\n"), sections[i].c_str());

			auto data = parse.GetDataFromSection(sections[i].c_str());
			for (int j = 0; j < data.size(); j++) {
				fprintf(file, Str("%s = %s\n"), data[j].first.c_str(), data[j].second.c_str());
			}

			data.clear();

			if (i != sections.size() - 1) {
				fprintf(file, Str("\n"));
			}
		}

		sections.clear();

		fclose(file);
	}
	parse.ItemMap.clear();
}
HRESULT Xui::InitializeX() {
	CreateDirectoryA("HDD:\\silent Cache\\", NULL);
	IniParse parse("HDD:\\silent Cache\\silent.ini");
	if (parse.IsGood()) {
		auto ManifestIp = parse.ReadString(Str("UI"), Str("Manifest"), Str(Xui::XManifestIp));
		auto colors = parse.ReadString("UI", "Colors", "");
		parse.ReadBool("UI", "CustomUi", Xui::Custom);

		parse.ItemMap.clear();
		strcpy(Xui::XManifestIp, ManifestIp);
		strcpy(Xui::XColors, colors);
		SWriteFile("HDD:\\customIP.bin", Xui::XManifestIp, 0x24);
		// re-cache
		//UpdateConfig();
	}
	else {
		// create base file
		InstallDefaultConfig();
		strcpy(XColors, Str("Red"));
		strcpy(XManifestIp, Str("assets.silent.hosted.nfoservers.com"));
	}
	return S_OK;
}
*/
/*
VOID WriteINI()
{
	if (XIniRW.WOpenINI(INIPath))
	{
		XIniRW.WriteInt("UI", "R", R);
		XIniRW.WriteInt("UI", "G", G);
		XIniRW.WriteInt("UI", "B", B);
		XIniRW.WriteInt("UI", "R2", R2);
		XIniRW.WriteInt("UI", "G2", G2);
		XIniRW.WriteInt("UI", "B2", B2);
		XIniRW.WriteString("UI", "ManifestIp", manifest);

		if (!XIniRW.WCloseINI());
	}
}


char Xui::cstr[0x26];
VOID ReadINI()
{
	if (XIniRW.ROpenINI(INIPath))
	{
		R = XIniRW.ReadInt("UI", "R");
		G = XIniRW.ReadInt("UI", "G");
		B = XIniRW.ReadInt("UI", "B");
		R2 = XIniRW.ReadInt("UI", "R2");
		G2 = XIniRW.ReadInt("UI", "G2");
		B2 = XIniRW.ReadInt("UI", "B2");
		Xui::cstr = XIniRW.ReadString("UI", "ManifestIp");
		if (!XIniRW.RCloseINI());
	}
}
*/