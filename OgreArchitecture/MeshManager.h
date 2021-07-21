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

	HRESULT createPlane(const string _planeName, Plane& plane,
		const int _width, const int _height, const int Xsegments, const int Zsegments);

	LPD3DXMESH Mesh = NULL;

	int xseg;
	int zseg;

	void Render();

	LPD3DXMESH GetMesh(string _planeName);
};

END