#include "DXUT.h"
#include "MeshManager.h"

USING(Tipp7)

HRESULT MeshManager::createPlane(const string _planeName, const int _width, const int _height, const int Xsegments, const int Zsegments, const float uTile, const float vTile)
{
	Plane* plane = new Plane();

	if (FAILED(D3DXCreateMeshFVF((((Xsegments-1) * (Zsegments-1)) * 2), (Xsegments * Zsegments), D3DXMESH_MANAGED, D3DFVF_PLANEVERTEX, DEVICE, &plane->Mesh)))
		return E_FAIL;

	//Lock() 함수를 통해 정점버퍼에 정점을 저장할수 있는 주소값을 직접 얻어온다.
	VOID* pVBbuffer = NULL;
	if (FAILED(plane->Mesh->LockVertexBuffer(NULL, (void**)&pVBbuffer)))
		return E_FAIL;
	
	// 정점의 좌표값을 할당하는 간단한 알고리즘
	// 0,0,0의 위치 : 지형의 무게중심
	PLANEVERTEX v;
	PLANEVERTEX* pV = (PLANEVERTEX*)pVBbuffer; // 버텍스 정보를 저장할 배열을 만듬 

	for (int z = 0; z < Zsegments; ++z)
	{
		for (int x = 0; x < Xsegments; ++x)
		{
			// 정점 위치 잡아주기
			v.x = (((float)x - Xsegments / 2) / Xsegments) * _width;
			v.y = 0.0f;
			v.z = (((float)z - Zsegments / 2) / Zsegments) * _height;
			
			// 정점 수직벡터 잡아주기 ( 빛 효과 관련 처리 )
			v.nx =  0;
			v.ny =  1;
			v.nz =  0;

			//텍스쳐 맵핑을 위한 uv좌표 설정
			v.u1 = (float)x / (Xsegments - 1) * uTile;
			v.v1 = (float)z / (Zsegments - 1) * vTile;

			// 이렇게 만들어진 하나의 정점 정보를 정점 버퍼에 저장한다.
			// ( 이미 Lock을 통해서 실제로 저장되야할 주소는 받아온 상태 )
			// 저장 후 다음 정점버퍼의 위치를 가리킬 수 있도록 포인터 연산을 통해 처리한다
			*pV++ = v;
			// pV는 Lock을 통해 받은 주소 위치.
			// 해당위치에 내가 넣어둔 v를 넣고 후위 연산을 통해
			// 포인터를 다음 정점 위치로 가리킨다.
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
			// 정점 인덱스를 CW방향으로 생성한다.
			// 컬링 모드를 CW방향으로 설정해놓을 시 아무것도 보이지 않을 것이다.
			// DEVICE->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ); 이 아니게 조심하자.

			// 사각형중.. 왼쪽 위 삼각형
			i._0 = (z * Xsegments + x);
			i._1 = ((z + 1) * Xsegments + x);
			i._2 = (z * Xsegments + x + 1);

			*pI++ = i;

			// 사각형중.. 오른쪽 아래 삼각형
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
