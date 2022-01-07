#include "DXUT.h"
#include "AseLexer.h"

USING(Tipp7)

bool AseLexer::LoadAseFile(const wstring _fileName)
{
	std::ifstream file(L"res/" + _fileName);

	if (file.good())
	{
		// File Reading
		strData.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
		file.close();
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}

void AseLexer::MakeToken(void)
{
	wstring separators = L" \t\r\n";
	unsigned int nLength = strData.length();
	unsigned int nStart, nStop;

	nStart = strData.find_first_of(separators);
	vecTokens.reserve(nLength);

	while (nStart >= 0 && nStart < nLength)
	{
		if (strData[nStart] == '\"') // 큰 따옴표가 발견되면 따옴표 끝까지 하나의 토큰이 된다.
		{
			nStart++;
			nStop = strData.find_first_of('\"', nStart);
		}
		else
			nStop = strData.find_first_of(separators, nStart);

		if (nStop < 0 || nStop > nLength)
			nStop = nLength;

		vecTokens.push_back(strData.substr(nStart, nStop - nStart));
		nStart = strData.find_first_not_of(separators, nStop + 1);
	}
}

bool AseLexer::GetToken(wstring& _tokenOut)
{
	if (curTokenNum < vecTokens.size())
	{
		_tokenOut = vecTokens[curTokenNum];
		++curTokenNum;
		return true;
	}
	else
	{
		return false;
	}
}

bool AseLexer::FindToken(const wstring& _tokenOut)
{
	while (curTokenNum < vecTokens.size())
	{
		++curTokenNum;
		wstring strTemp = vecTokens[curTokenNum - 1];
		if (strTemp == _tokenOut)
			return true;
	}
	return false;
}

bool AseLexer::FindTokenInThisBlock(const wstring& _tokenOut)
{
	while (curTokenNum < vecTokens.size())
	{
		++curTokenNum;
		wstring strTemp = vecTokens[curTokenNum - 1];
		if (strTemp == _tokenOut)
			return true;
		else if (strTemp == L"}")
			return false;
	}
	return false;
}

bool AseLexer::ShowToken(wstring& _tokenOut)
{
	if (curTokenNum < vecTokens.size())
	{
		_tokenOut = vecTokens[curTokenNum];
		return true;
	}
	else
	{
		return false;
	}
}
