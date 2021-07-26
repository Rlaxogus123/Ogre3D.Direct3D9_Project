#include "DXUT.h"
#include "MeshManager.h"

USING(Tipp7)

HRESULT MeshManager::createPlane(const string _planeName, const int _width, const int _height, const int Xsegments, const int Zsegments, const float uTile, const float vTile)
{
	Plane* plane = new Plane();

	if (FAILED(D3DXCreateMeshFVF((((Xsegments-1) * (Zsegments-1)) * 2), (Xsegments * Zsegments), D3DXMESH_MANAGED, D3DFVF_PLANEVERTEX, DEVICE, &plane->Mesh)))
		return E_FAIL;

	//Lock() �Լ��� ���� �������ۿ� ������ �����Ҽ� �ִ� �ּҰ��� ���� ���´�.
	VOID* pVBbuffer = NULL;
	if (FAILED(plane->Mesh->LockVertexBuffer(NULL, (void**)&pVBbuffer)))
		return E_FAIL;
	
	// ������ ��ǥ���� �Ҵ��ϴ� ������ �˰���
	// 0,0,0�� ��ġ : ������ �����߽�
	PLANEVERTEX v;
	PLANEVERTEX* pV = (PLANEVERTEX*)pVBbuffer; // ���ؽ� ������ ������ �迭�� ���� 

	for (int z = 0; z < Zsegments; ++z)
	{
		for (int x = 0; x < Xsegments; ++x)
		{
			// ���� ��ġ ����ֱ�
			v.x = (((float)x - Xsegments / 2) / Xsegments) * _width;
			v.y = 0.0f;
			v.z = (((float)z - Zsegments / 2) / Zsegments) * _height;
			
			// ���� �������� ����ֱ� ( �� ȿ�� ���� ó�� )
			v.nx =  0;
			v.ny =  1;
			v.nz =  0;

			//�ؽ��� ������ ���� uv��ǥ ����
			v.u1 = (float)x / (Xsegments - 1) * uTile;
			v.v1 = (float)z / (Zsegments - 1) * vTile;

			// �̷��� ������� �ϳ��� ���� ������ ���� ���ۿ� �����Ѵ�.
			// ( �̹� Lock�� ���ؼ� ������ ����Ǿ��� �ּҴ� �޾ƿ� ���� )
			// ���� �� ���� ���������� ��ġ�� ����ų �� �ֵ��� ������ ������ ���� ó���Ѵ�
			*pV++ = v;
			// pV�� Lock�� ���� ���� �ּ� ��ġ.
			// �ش���ġ�� ���� �־�� v�� �ְ� ���� ������ ����
			// �����͸� ���� ���� ��ġ�� ����Ų��.
		}
	}
	plane->Mesh->UnlockVertexBuffer();

	VOID* pIBbuffer = NULL;
	if (FAILED(plane->Mesh->LockIndexBuffer(NULL, (void**)&pIBbuffer)))
		return E_FAIL;

	MYINDEX i;
	MYINDEX* pI = (MYINDEX*)pIBbuffer;

	for (int z = 0; z < Zsegments - 1; ++z)
	{
		for (int x = 0; x < Xsegments - 1; ++x)
		{
			// ���� �ε����� CW�������� �����Ѵ�.
			// �ø� ��带 CW�������� �����س��� �� �ƹ��͵� ������ ���� ���̴�.
			// DEVICE->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ); �� �ƴϰ� ��������.

			// �簢����.. ���� �� �ﰢ��
			i._0 = (z * Xsegments + x);
			i._1 = ((z + 1) * Xsegments + x);
			i._2 = (z * Xsegments + x + 1);

			*pI++ = i;

			// �簢����.. ������ �Ʒ� �ﰢ��
			i._0 = ((z + 1) * Xsegments + x);
			i._1 = ((z + 1) * Xsegments + x + 1);
			i._2 = (z * Xsegments + x + 1);

			*pI++ = i;
		}
	}

	plane->Mesh->UnlockIndexBuffer();
	plane->planeName = _planeName;
	planeList.push_back(plane);
}

void MeshManager::Render()
{
}

void MeshManager::Exit()
{
	cout << "!! MeshManager - Plane Released !!" << endl;
	for (auto& it : planeList)
	{
		it->Exit();
		SAFE_DELETE(it);
	}
	planeList.clear();
}

LPD3DXMESH MeshManager::GetMesh(string _planeName)
{
	for (auto& it : planeList)
	{
		if (it->planeName._Equal(_planeName))
			return it->Clone()->Mesh;
	}
	return nullptr;
}
