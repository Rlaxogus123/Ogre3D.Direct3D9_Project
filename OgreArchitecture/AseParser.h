#pragma once

#include "AseLexer.h"

NAMESPACE(Tipp7)

class AseParser
{
public:
	AseParser(AseLexer* _lexer) { lexer = _lexer; };
	~AseParser(void) {};

	AseLexer* lexer;

	D3DXQUATERNION	ParseQueternion();
	Vector3			ParseVector3();
	LONG			ParseLong();
	DWORD			ParseDWORD();
	WORD			ParseWORD();
	FLOAT			ParseFLOAT();
};

END