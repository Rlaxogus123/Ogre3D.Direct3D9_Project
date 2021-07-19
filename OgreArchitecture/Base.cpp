#include "DXUT.h"
#include "Base.h"

USING(Tipp7)

int Base::AddReference(void)
{
	return refCount++;
}

int Base::Release(void)
{
	// 나를 참조하는 카운트가 0개이면
	if (refCount == 0)
	{
		Free(); // 메모리 해제
		delete this; // 자기자신 지우기
		return 0;
	}
	return refCount--; // 그게아니면 카운트 감소
}
