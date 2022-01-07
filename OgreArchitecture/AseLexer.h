#pragma once

#include <fstream>

NAMESPACE(Tipp7)

class AseLexer
{
public:
	AseLexer(void) : curTokenNum(0) {};
	~AseLexer(void) { strData.clear(); vecTokens.clear(); };

	wstring strData;
	vector<wstring> vecTokens;

	DWORD curTokenNum = 0;

public:
	bool LoadAseFile(const wstring _fileName);
	void MakeToken(void);

	bool GetToken(wstring& _tokenOut);
	bool FindToken(const wstring& _tokenOut);
	bool FindTokenInThisBlock(const wstring& _tokenOut);
	bool ShowToken(wstring& _tokenOut);
};

END