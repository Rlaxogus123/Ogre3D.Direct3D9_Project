#pragma once

NAMESPACE(Tipp7)

class Plane
{
public:
	explicit Plane() { ZeroMemory(&Mesh, sizeof(LPD3DXMESH)); };
	virtual ~Plane(void) {};

	LPD3DXMESH Mesh = NULL;
	string planeName = "";
};

END