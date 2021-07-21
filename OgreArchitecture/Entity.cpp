#include "DXUT.h"
#include "Entity.h"

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
	MeshTextures = new LPDIRECT3DTEXTURE9[numMaterials];
	for (DWORD i = 0; i < numMaterials; i++)
	{
		MeshMaterials[i] = d3dxMaterials[i].MatD3D;
		MeshMaterials[i].Ambient = MeshMaterials[i].Diffuse;
		MeshTextures[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL && strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			const CHAR* route = "res/Colors/";
			CHAR finalroute[MAX_PATH];
			sprintf(finalroute, "%s%s", route, d3dxMaterials[i].pTextureFilename);

			auto isFail = D3DXCreateTextureFromFileA(DXUTGetD3D9Device(), finalroute, &MeshTextures[i]);
			if (FAILED(isFail))
			{
				MeshTextures[i] = NULL;
				wcout << "TextureFail!! << " << finalroute << endl;
			}
			else
				wcout << "TextureLoad!! << " << finalroute << endl;
		}
	}
	pD3DXMtrlBuffer->Release();
	return 0;
}

void Entity::Render(void)
{
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &node->GetMatrix());
	for (DWORD i = 0; i < numMaterials; i++)
	{
		if(MeshMaterials != NULL) DXUTGetD3D9Device()->SetMaterial(&MeshMaterials[i]);
		if(MeshTextures != NULL) DXUTGetD3D9Device()->SetTexture(0, MeshTextures[i]);
		if(Mesh != NULL) Mesh->DrawSubset(i);
	}
	DXUTGetD3D9Device()->SetTexture(0, NULL);
}

void Entity::Exit(void)
{
	Safe_Release(Mesh);
	for (int i = 0; i < numMaterials; i++)
	{
		delete& MeshMaterials[i];
		Safe_Release(MeshTextures[i]);
	}
	SAFE_DELETE_ARRAY(MeshTextures);
}
