#pragma once
#include "stdafx.h"
#ifndef __INIPARSE_H__
#define __INIPARSE_H__

class IniParse {
public:
	IniParse() { bIsGood = false; }

	IniParse(const char* pFileName) {
		bIsGood = false;
		auto file = fopen(pFileName, "r");
		if (file) {
			bIsGood = true;
			string currentSection;
			int currentLine = 0;
			char currentDilem = '=';

			char line[300];
			while (fgets(line, 300, file) != 0) {
				string strLine(line);
				strLine.erase(std::remove(strLine.begin(), strLine.end(), '\n'), strLine.end());
				if (strLine.empty()) continue;

				if (line[0] == ';') continue;

				currentLine++;
				currentDilem = '=';
				bool checkedDilem = false;

				if (line[0] == '[') {
					// section line
					currentSection = strLine;
					currentSection.erase(std::remove(currentSection.begin(), currentSection.end(), '['), currentSection.end());
					currentSection.erase(std::remove(currentSection.begin(), currentSection.end(), ']'), currentSection.end());

					if (currentSection.length() > 0) {
						if (currentSection[currentSection.length() - 1] == ' ') {
							currentSection[currentSection.length() - 1] = 0x0;
						}
					}
				}
				else {
					if (line[0] == NULL) {
						continue;
					}

					if (currentSection.c_str()) {
						bool isSpacedLeft = false;
						bool isSpacedRight = false;

					jStart:
						int equals = strLine.find(currentDilem);
						if (equals > 0) {
							if (line[equals - 1] == ' ') {
								isSpacedLeft = true;
							}

							if (line[equals + 1] == ' ') {
								isSpacedRight = true;
							}

							string key = strLine.substr(0, equals - (isSpacedLeft ? 1 : 0));
							string value = strLine.substr(equals + (isSpacedRight ? 2 : 1));

							if (value.length() <= 0) {
								continue;
							}

							if (value[value.length() - 1] == ' ')
								value[value.length() - 1] = 0x0;

							ItemMap.insert(make_pair(make_pair(currentSection, key), value));
						}
						else {
							if (strLine.find(':') > 0) {
								if (checkedDilem) continue;
								checkedDilem = true;

								currentDilem = ':';
								goto jStart;
							}
						}
					}
				}
			}

			fclose(file);
		}
		else {
			DbgPrint("Can't open file!");
		}
	}

	vector<string> GetSections() {
		vector<string> mapped;

		for (auto outer = ItemMap.begin(); outer != ItemMap.end(); ++outer) {
			auto vit = Find(mapped, outer->first.first);
			if (!vit) {
				mapped.push_back(outer->first.first);
			}
		}

		return mapped;
	}

	vector<pair<string, string>> GetDataFromSection(const char* pSection) {
		vector<pair<string, string>> mapped;

		for (auto outer = ItemMap.begin(); outer != ItemMap.end(); ++outer) {
			if (!strcmp(outer->first.first.c_str(), pSection)) {
				mapped.push_back(make_pair(outer->first.second, outer->second));
			}
		}

		return mapped;
	}

	const char* ReadString(const char* pSection, const char* pWhat, const char* defaultVal) {
		if (!ItemMap[make_pair(pSection, pWhat)].empty()) {
			return ItemMap[make_pair(pSection, pWhat)].c_str();
		}

		return defaultVal;
	}

	void SetString(const char* pSection, const char* pWhat, const char* val) {
		ItemMap[make_pair(pSection, pWhat)] = val;
	}

	bool IsGood() {
		return bIsGood;
	}

	map<pair<string, string>, string> ItemMap;
private:
	bool bIsGood;
	bool Find(vector<string> mapped, string val) {
		for (int i = 0; i < mapped.size(); i++) {
			if (mapped[i] == val)
				return true;
		}
		return false;
	}
};

#endif