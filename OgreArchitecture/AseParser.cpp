#include "DXUT.h"
#include "AseParser.h"

USING(Tipp7)

D3DXQUATERNION AseParser::ParseQueternion()
{
	D3DXQUATERNION temp;
	wstring strToken;

	if (lexer->GetToken(strToken))
		temp.x = (float)_wtof(strToken.c_str());

	if (lexer->GetToken(strToken))
		temp.y = (float)_wtof(strToken.c_str());

	if (lexer->GetToken(strToken))
		temp.z = (float)_wtof(strToken.c_str());

	if (lexer->GetToken(strToken))
		temp.w = (float)_wtof(strToken.c_str());

	return temp;
}

Vector3 AseParser::ParseVector3()
{
	Vector3 temp;
	wstring strToken;

	if (lexer->GetToken(strToken))
		temp.x = (float)_wtof(strToken.c_str());

	if (lexer->GetToken(strToken))
		temp.y = (float)_wtof(strToken.c_str());

	if (lexer->GetToken(strToken))
		temp.z = (float)_wtof(strToken.c_str());

	return temp;
}

LONG AseParser::ParseLong()
{
	LONG temp;
	wstring strToken;

	if (lexer->GetToken(strToken))
		temp = wcstoul(strToken.c_str(), NULL, 10);

	return temp;
}

DWORD AseParser::ParseDWORD()
{
	DWORD temp;
	wstring strToken;

	if (lexer->GetToken(strToken))
		temp = wcstoul(strToken.c_str(), NULL, 10);

	return temp;
}

WORD AseParser::ParseWORD()
{
	WORD temp;
	wstring strToken;

	if (lexer->GetToken(strToken))
		temp = (WORD)wcstoul(strToken.c_str(), NULL, 10);

	return temp;
}

FLOAT AseParser::ParseFLOAT()
{
	FLOAT temp;
	wstring strToken;

	if (lexer->GetToken(strToken))
		temp = (FLOAT)_wtof(strToken.c_str());

	return temp;
}
