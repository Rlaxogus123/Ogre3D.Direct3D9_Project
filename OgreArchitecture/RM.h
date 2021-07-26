#pragma once

#include "Singleton.h"
#include "Texture2D.h"
#include "Resources.h"
#include "Shader.h"

NAMESPACE(Tipp7)

class RM
	: public Singleton<RM>
{
public:
	RM(void) {};
	~RM(void) {}

	void preLoadTextures();
	list<Resources*> resourceList;
	
	HRESULT CreateTexture(wstring _path, string _resName);
	HRESULT CreateShader(wstring _path, string _resName);

	Resources* GetResources(string name);

	void Exit();
};

END