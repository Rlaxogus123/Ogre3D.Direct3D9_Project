#include "DXUT.h"
#include "Base.h"

USING(Tipp7)

int Base::AddReference(void)
{
	return refCount++;
}

int Base::Release(void)
{
	// ���� �����ϴ� ī��Ʈ�� 0���̸�
	if (refCount == 0)
	{
		Free(); // �޸� ����
		delete this; // �ڱ��ڽ� �����
		return 0;
	}
	return refCount--; // �װԾƴϸ� ī��Ʈ ����
}
