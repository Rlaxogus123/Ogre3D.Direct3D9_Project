#pragma once

#include "Singleton.h"
#include "Plane.h"

NAMESPACE(Tipp7)

class MeshManager
	: public Singleton<MeshManager>
{
public:
	explicit MeshManager() {};
	virtual ~MeshManager() {};

	list<Plane*> planeList;

	HRESULT createPlane(const string _planeName,
		const int _width, const int _height, const int Xsegments, const int Zsegments,
		const float uTile = 1, const float vTile = 1);

	void Render();
	void Exit();

	LPD3DXMESH GetMesh(string _planeName);
};

END