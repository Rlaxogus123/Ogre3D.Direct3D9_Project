#include "DXUT.h"
#include "CollisionManager.h"

USING(Tipp7)

bool CollisionManager::Sphere_VS_Sphere(const Vector3 position1, const FLOAT radius1, const Vector3 position2, const FLOAT radius2)
{
	Vector3 pos = position2 - position1;
	FLOAT distance = sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
	if (radius1 + radius2 >= distance) return true;
	else return false;
}

bool CollisionManager::Sphere_VS_Plane(const Vector3* spherePosition, const FLOAT radius, const Vector3* Plane, const Vector3* up)
{
	// d = ?? ax1 + by1 + cz1 + d ?? / sqrt(a^2 + b^2 + c^2)
	// d = ?? ax1 + by1 + cz1 - D ?? / ??n?桫 = 1
	// D = ax + by + cz
	float d = fabs((up->x * spherePosition->x + up->y * spherePosition->y + up->z * spherePosition->z) -
		(up->x * Plane->x + up->y * Plane->y + up->z * Plane->z));
	if (d < radius) return true;
	return false;
}