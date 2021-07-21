#pragma once

#include "MovableObject.h"

NAMESPACE(Tipp7)

class Entity :
	public MovableObject
{
public:
	explicit Entity(void) {};
	virtual ~Entity(void) {};

	LPD3DXMESH Mesh = NULL; // �޽� ��ü
	D3DMATERIAL9* MeshMaterials = NULL; // �޽� ����
	LPDIRECT3DTEXTURE9* MeshTextures = NULL; // �޽� �ؽ���
	DWORD numMaterials = NULL; // ������ ��

	HRESULT SetXFile(wstring _xfilePath);

	void Init(void) override;
	void Update(void) override;
	void Render(void) override;
	void Exit(void) override;
};

END