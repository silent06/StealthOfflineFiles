class CXIniRW {
public:
	bool ROpenINI(const char* fileName);
	bool RCloseINI();
	bool WOpenINI(const char* fileName);
	bool WCloseINI();

	bool GetValue(const char* Key, const char* Member, string& szLine);

	int ReadInt(const char* Group, const char* Member);
	float ReadFloat(const char* Group, const char* Member);
	string ReadString(const char* Group, const char* Member);
	bool ReadBool(const char* Group, const char* Member);

	void WriteInt(const char* Group, const char* Member, int Value);
	void WriteFloat(const char* Group, const char* Member, float Value);
	void WriteString(const char* Group, const char* Member, string Value);
	void WriteBool(const char* Group, const char* Member, bool Value);

} extern XIniRW;