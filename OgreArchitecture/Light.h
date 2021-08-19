#pragma once

#include "MovableObject.h"

NAMESPACE(Tipp7)

enum class LightType
{
	POINT = 1,
	SPOT = 2,
	DIRECTIONAL = 3,
};

class Light 
	: public MovableObject
{
public:
	explicit Light(void) { ZeroMemory(&light, sizeof(D3DLIGHT9)); 
	light.Diffuse.a = light.Diffuse.r = light.Diffuse.g = light.Diffuse.b = 1; 
	light.Specular.a = light.Specular.r = light.Specular.g = light.Specular.b = 1;
	};
	virtual ~Light(void) {};

	D3DLIGHT9 light; // 조명
	Vector3 vecDir = { 0,0,0 }; // 조명의 방향
	UINT lightNumber = 0;

	void setPowerScale(const float _range);
	void setType(const LightType _type);
	void setDiffuseColor(const float r, const float g, const float b, const float a = 1.0f);
	void setSpecularColor(const float r, const float g, const float b, const float a = 1.0f);
	
	void Init(void) override;
	void Update(void) override;
	void Render(void) override;
	void Exit(void) override;
};

END