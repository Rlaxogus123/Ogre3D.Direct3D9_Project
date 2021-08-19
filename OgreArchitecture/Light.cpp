#include "DXUT.h"
#include "Light.h"

USING(Tipp7)

void Light::Init(void)
{
	light.Position = node->position;
}

void Light::Update(void)
{
}

void Light::Render(void)
{
	light.Position = node->position;
	vecDir = { 0,0,-1 };
	D3DXVec3TransformCoord(&vecDir, &vecDir, &node->GetEulerMatrix());
	D3DXVec3Normalize((Vector3*)&light.Direction, &vecDir);

	DXUTGetD3D9Device()->SetLight(lightNumber, &light);
	DXUTGetD3D9Device()->LightEnable(lightNumber, TRUE);
}

void Light::setType(const LightType _type)
{
	if (_type == LightType::DIRECTIONAL)
		light.Type = D3DLIGHT_DIRECTIONAL;
	if (_type == LightType::POINT)
		light.Type = D3DLIGHT_POINT;
	if (_type == LightType::SPOT)
		light.Type = D3DLIGHT_SPOT;
}

void Light::setPowerScale(const float _range)
{
	light.Range = _range;
}

void Light::setDiffuseColor(const float r, const float g, const float b, const float a)
{
	light.Diffuse.r = r;
	light.Diffuse.g = g;
	light.Diffuse.b = b;
	light.Diffuse.a = a;
}

void Light::setSpecularColor(const float r, const float g, const float b, const float a)
{
	light.Specular.r = r;
	light.Specular.g = g;
	light.Specular.b = b;
	light.Specular.a = a;
}

void Light::Exit(void)
{
	cout << "!! Light Released !! : " << movableName << endl;
	DXUTGetD3D9Device()->LightEnable(lightNumber, FALSE);
}

