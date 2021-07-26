#pragma once

NAMESPACE(Tipp7)

class Plane
{
public:
	explicit Plane() {};
	explicit Plane(const Plane& copy);
	virtual ~Plane(void) {};

	ID3DXMesh* Mesh = nullptr;
	string planeName = "";

	Plane* Clone(void);
	void Exit();
};

END