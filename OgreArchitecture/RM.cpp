#include "DXUT.h"
#include "RM.h"

USING(Tipp7)

void RM::preLoadTextures()
{
	CreateShader(L"Shaders/PhongUV.fx", "PhongUV");
	CreateShader(L"Shaders/Light.fx", "Light");
	CreateShader(L"Shaders/MyLightShader.fx", "MLS");

	CreateTexture(L"Textures/terrain.png", "terrain");
	CreateTexture(L"Textures/brick0.jpg", "brick0");
	CreateTexture(L"Textures/brick1.jpg", "brick1");
	CreateTexture(L"Textures/checker.jpg", "checker");
	CreateTexture(L"Textures/red.png", "red");
	CreateTexture(L"Textures/orange.png", "orange");
	CreateTexture(L"Colors/FA59AMako_BaseColor.png", "Air");
}

HRESULT RM::CreateTexture(wstring _path, string _resName)
{
	for (auto& it : resourceList) {
		if (it->resName._Equal(_resName))
		{
			cout << "Texture Resources Name is already ADDED!! >> " << _resName << endl;
			return E_FAIL;
		}
	}

	Texture2D* tex = new Texture2D();
	tex->resName = _resName;
	auto route = L"res/" + _path;

	auto isFail = D3DXCreateTextureFromFileExW(DEVICE, route.c_str(), -2, -2, 1, 0, D3DFORMAT::D3DFMT_A8B8G8R8, 
		D3DPOOL::D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &tex->info, nullptr,
		&tex->texture);

	if (FAILED(isFail)) {
		MessageBox(DXUTGetHWND(), NULL, L"텍스쳐 로딩 실패!", MB_ICONERROR | MB_OK);
		delete tex;
		return E_FAIL;
	}
	else
	{
		wcout << "TEXTURE LOAD COMPLETE!! >> " << route.c_str() << endl;
		resourceList.push_back(tex);
		return S_OK;
	}
}

HRESULT RM::CreateShader(wstring _path, string _resName)
{
	for (auto& it : resourceList) {
		if (it->resName._Equal(_resName))
		{
			cout << "Texture Resources Name is already ADDED!! >> " << _resName << endl;
			return E_FAIL;
		}
	}

	Shader* shader = new Shader();
	shader->resName = _resName;
	auto route = L"res/" + _path;

	auto isFail = D3DXCreateEffectFromFileW(DEVICE, route.c_str(), NULL, NULL, NULL, NULL, &shader->effect, nullptr);

	if (FAILED(isFail))
	{
		MessageBox(DXUTGetHWND(), NULL, L"쉐이더 로딩 실패!", MB_ICONERROR | MB_OK);
		delete shader;
		return E_FAIL;
	}
	else
	{
		wcout << "SHADER LOAD COMPLETE!! >> " << route.c_str() << endl;
		resourceList.push_back(shader);
		return S_OK;
	}
}

Resources* RM::GetResources(string name)
{
	for (auto& it : resourceList)
	{
		if (it->resName._Equal(name))
			return it->Clone();
	}
	return nullptr;
}

void RM::Exit()
{
	cout << "!! ResourceManager Released !!" << endl;
	for (auto& it : resourceList)
	{
		it->Exit();
		delete it;
	}
	resourceList.clear();
}
