#pragma once

#include "MovableObject.h"
#include "AseLexer.h"
#include "AseParser.h"

NAMESPACE(Tipp7)

class AseHandler
	: public MovableObject
{
public:
	explicit AseHandler(void) {};
	virtual ~AseHandler(void) {};

	// AseLexer & Parser
	AseLexer* m_lexer = nullptr;
	AseParser* m_parser = nullptr;

	bool ParsingMaterialList();
	bool ParsingGeomObject();

	bool Setup();
	void SetAseFile(const wstring _path);
	// AseLexer & Parser
	
	// D3DMember
	LPDIRECT3DTEXTURE9 m_texture = NULL;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	DWORD vertexCount = 0;

	bool SetTexture(wstring path);
	// D3DMember

	void Init(void) override;
	void Update(void) override;
	void Render(void) override;
	void Exit(void) override;
};

END