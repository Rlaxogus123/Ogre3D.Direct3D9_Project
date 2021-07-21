#pragma once

#include "MovableObject.h"

NAMESPACE(Tipp7)

class Entity :
	public MovableObject
{
public:
	explicit Entity(void) {};
	virtual ~Entity(void) {};

	LPD3DXMESH Mesh = NULL; // 메쉬 객체
	D3DMATERIAL9* MeshMaterials = NULL; // 메쉬 재질
	LPDIRECT3DTEXTURE9* MeshTextures = NULL; // 메쉬 텍스쳐
	DWORD numMaterials = NULL; // 재질의 수

	HRESULT SetXFile(wstring _xfilePath);

	void Init(void) override;
	void Update(void) override;
	void Render(void) override;
	void Exit(void) override;
};

END