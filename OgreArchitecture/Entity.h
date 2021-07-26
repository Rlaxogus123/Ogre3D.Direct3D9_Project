#pragma once

#include "MovableObject.h"
#include "Texture2D.h"
#include "Shader.h"

NAMESPACE(Tipp7)

class Entity :
	public MovableObject
{
public:
	explicit Entity(void) {};
	virtual ~Entity(void) {};

	Shader* shader = nullptr;
	ID3DXMesh* Mesh = NULL; // 메쉬 객체
	D3DMATERIAL9* MeshMaterials = NULL; // 메쉬 재질
	Texture2D* MeshTextures = NULL; // 메쉬 텍스쳐
	DWORD numMaterials = NULL; // 재질의 수

	HRESULT SetXFile(wstring _xfilePath);
	void SetTexture(Texture2D* texture, const int _number = 0);
	void SetEffect(Shader* _shader);

	void Init(void) override;
	void Update(void) override;
	void Render(void) override;
	void Exit(void) override;
};

END