#include "DXUT.h"
#include "Entity.h"
#include "Root.h"

USING(Tipp7)

void Entity::Init(void)
{
}

void Entity::Update(void)
{
}

HRESULT Entity::SetXFile(wstring _xfilePath)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	auto route = L"res/" + _xfilePath;
	auto isFail = D3DXLoadMeshFromXW(route.c_str(), D3DXMESH_SYSTEMMEM, DXUTGetD3D9Device(), NULL,
		&pD3DXMtrlBuffer, NULL, &numMaterials, &Mesh);

	if (FAILED(isFail))
	{
		MessageBox(NULL, L"X파일 로드 실패", L"메쉬로드 실패", MB_OK);
		return E_FAIL;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	MeshMaterials = new D3DMATERIAL9[numMaterials];
	MeshTextures = new Texture2D[numMaterials];
	for (DWORD i = 0; i < numMaterials; i++)
	{
		MeshMaterials[i] = d3dxMaterials[i].MatD3D;
		MeshMaterials[i].Ambient = MeshMaterials[i].Diffuse;
		MeshTextures[i].texture = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL && strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			const CHAR* route = "res/Colors/";
			CHAR finalroute[MAX_PATH];
			sprintf(finalroute, "%s%s", route, d3dxMaterials[i].pTextureFilename);

			auto isFail = D3DXCreateTextureFromFileA(DXUTGetD3D9Device(), finalroute, &MeshTextures[i].texture);
			if (FAILED(isFail))
			{
				MeshTextures[i].texture = NULL;
				wcout << "TextureFail!! << " << finalroute << endl;
			}
			else
			{
				wcout << "TextureLoad!! << " << finalroute << endl;
			}
		}
	}
	pD3DXMtrlBuffer->Release();
	return 0;
}

void Entity::SetTexture(Texture2D* texture, const int _number)
{
	if (texture == nullptr) return;
	MeshTextures = nullptr;
	MeshTextures = new Texture2D[_number + 1];
	MeshTextures[_number].info = texture->info;
	MeshTextures[_number].texture = texture->texture;
}

void Entity::SetSpecularMap(Texture2D* texture)
{
	Specular_texture = texture->texture;
}

void Entity::SetNormalMap(Texture2D* texture)
{
	Normal_texture = texture->texture;
}

void Entity::SetDiffuseMap(Texture2D* texture)
{
	Diffuse_texture = texture->texture;
}

void Entity::SetEffect(Shader* _shader)
{
	shader = _shader;
}

void Entity::Render(void)
{
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &node->GetMatrix());

	if (shader != nullptr)
	{
		shader->Render(node->GetMatrix());

		// 쉐이더 전역변수들을 설정
		shader->effect->SetVector((D3DXHANDLE)"gWorldLightPosition", &Vector4(5, -1, 0, 0));

		shader->effect->SetVector((D3DXHANDLE)"gLightColor", &Vector4(1,1,1,1));
		shader->effect->SetVector((D3DXHANDLE)"gLightAmbient", &Vector4(0.5,0.5,0.5,1));

		shader->effect->SetTexture((D3DXHANDLE)"DiffuseMap_Tex", Diffuse_texture);
		shader->effect->SetTexture((D3DXHANDLE)"fieldstone_SM_Tex", Specular_texture);
		shader->effect->SetTexture((D3DXHANDLE)"NormalMap_Tex", Normal_texture);

		// 쉐이더를 시작한다.
		UINT numPasses = 0;
		shader->effect->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				shader->effect->BeginPass(i);
				{
					Mesh->DrawSubset(0);
				}
				shader->effect->EndPass();
			}
		}
		shader->effect->End();
	}
	else
	{
		for (DWORD i = 0; i < numMaterials; i++)
		{
			if (MeshMaterials != NULL)
				DXUTGetD3D9Device()->SetMaterial(&MeshMaterials[i]);
			DXUTGetD3D9Device()->SetTexture(0, MeshTextures[i].texture);
			Mesh->DrawSubset(i);
		}
		DXUTGetD3D9Device()->SetTexture(0, NULL);
	}
}

void Entity::Exit(void)
{
	cout << "!! Entity Released !! : " << movableName << endl;
	SAFE_RELEASE(Specular_texture);
	SAFE_RELEASE(Normal_texture);
	SAFE_RELEASE(Diffuse_texture);
	SAFE_DELETE_ARRAY(MeshMaterials);
	if (MeshTextures)
	{
		for (int i = 0; i < numMaterials; i++)
		{
			SAFE_RELEASE(MeshTextures[i].texture);
		}
		SAFE_DELETE_ARRAY(MeshTextures);
	}
}
