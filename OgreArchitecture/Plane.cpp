#include "DXUT.h"
#include "Plane.h"

USING(Tipp7)

Plane::Plane(const Plane& copy) :
	Mesh(copy.Mesh),
	planeName(copy.planeName)
{

}

Plane* Plane::Clone(void)
{
	return new Plane(*this);
}

void Plane::Exit()
{
	SAFE_RELEASE(Mesh);
}
