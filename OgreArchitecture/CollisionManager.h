#pragma once
#include "Singleton.h"

NAMESPACE(Tipp7)

class CollisionManager : public Singleton<CollisionManager>
{
public:
	bool Sphere_VS_Sphere(const Vector3 position1, const FLOAT radius1,
		const Vector3 position2, const FLOAT radius2);
	bool Sphere_VS_Plane(const Vector3* spherePosition, const FLOAT radius, 
		const Vector3* Plane, const Vector3* up);
};

END