#include "DXUT.h"
#include "AseHandler.h"

USING(Tipp7)

bool AseHandler::ParsingMaterialList()
{
	if (!Setup()) return false;

	wstring strToken;
	wstring strTexturePath;
	DWORD materialCount = 0;

	if (m_lexer->FindToken(L"*MATERIAL_LIST"))
	{
		if (m_lexer->FindToken(L"*MATERIAL_COUNT"))
		{
			if (m_lexer->GetToken(strToken))
				materialCount = wcstoul(strToken.c_str(), NULL, 10);
		}

		for (DWORD i = 0; i < materialCount; i++)
		{
			if (m_lexer->FindToken(L"*MAP_DIFFUSE"))
			{
				if (m_lexer->FindToken(L"*BITMAP"))
				{
					m_lexer->GetToken(strTexturePath);
					SetTexture(strTexturePath);
				}
			}
		}
	}

	return true;
}

bool AseHandler::ParsingGeomObject()
{
	wstring strToken;

	DWORD numVertexData = 0;	// ���ؽ� ��ġ ������ ����
	DWORD numFaceData = 0;		// �������� �����ϴ� ���ؽ� ��ġ �������� �ε��� ����
	DWORD numTVertexData = 0;	// ���ؽ� �ؽ��� ��ǥ �������� ����
	DWORD numTFaceData = 0;		// �������� �����ϴ� ���ؽ� �ؽ��� ��ǥ �������� �ε��� ����

	Vector3* pVertexData = nullptr;		// ���ؽ� ��ġ ������
	MYINDEX* pFaceData = nullptr;		// �������� �����ϴ� ���ؽ� ��ġ �������� �ε���

	Vector2* pTVertexData = nullptr;	// ���ؽ� �ؽ��� ��ǥ ������
	MYINDEX* pTFaceData = nullptr;		// �������� �����ϴ� ���ؽ� �ؽ��� ��ǥ �������� �ε���

	if (m_lexer->FindToken(L"*GEOMOBJECT"))
	{
		if (m_lexer->FindToken(L"*MESH"))
		{
			if (m_lexer->FindToken(L"*MESH_NUMVERTEX"))
			{
				numVertexData = m_parser->ParseDWORD();
				pVertexData = new Vector3[numVertexData];
				ZeroMemory(pVertexData, sizeof(Vector3) * numVertexData);
			}

			if (m_lexer->FindToken(L"*MESH_NUMFACES"))
			{
				numFaceData = m_parser->ParseDWORD();
				pFaceData = new MYINDEX[numFaceData];
				ZeroMemory(pVertexData, sizeof(Vector3) * numVertexData);
			}

			if (m_lexer->FindToken(L"*MESH_VERTEX_LIST"))
			{
				for (DWORD i = 0; i < numVertexData; ++i)
				{
					if (m_lexer->FindToken(L"*MESH_VERTEX"))
					{
						DWORD vertexIndex = m_parser->ParseDWORD();
						// 3ds Max�� ��ǥ�踦 DX ��ǥ��� �����ֱ� ���� y�� z�� ����
						pVertexData[vertexIndex].x = m_parser->ParseFLOAT();
						pVertexData[vertexIndex].z = m_parser->ParseFLOAT();
						pVertexData[vertexIndex].y = m_parser->ParseFLOAT();
					}
				}
			}
			
			if (m_lexer->FindToken(L"*MESH_FACE_LIST"))
			{
				for (DWORD i = 0; i < numFaceData; ++i)
				{
					if (m_lexer->FindToken(L"*MESH_FACE"))
					{
						m_lexer->GetToken(strToken); // ������ ��Ÿ���� ���� 0: ~ n: �� ������ ��������ʰ� ����.

						// 3ds Max�� ��ǥ�踦 DX ��ǥ��� �����ֱ� ���� y�� z�� ����
						m_lexer->GetToken(strToken);
						pFaceData[i]._0 = m_parser->ParseDWORD();

						m_lexer->GetToken(strToken);
						pFaceData[i]._2 = m_parser->ParseDWORD();

						m_lexer->GetToken(strToken);
						pFaceData[i]._1 = m_parser->ParseDWORD();
					}
				}
			}

			if (m_lexer->FindToken(L"*MESH_NUMTVERTEX"))
			{
				numTVertexData = m_parser->ParseDWORD();
				pTVertexData = new Vector2[numTVertexData];
				ZeroMemory(pTVertexData, sizeof(Vector2) * numTVertexData);
			}

			if (m_lexer->FindToken(L"*MESH_TVERTLIST"))
			{
				for (DWORD i = 0; i < numTVertexData; ++i)
				{
					if (m_lexer->FindToken(L"*MESH_TVERT"))
					{
						DWORD index = m_parser->ParseDWORD();

						// 3ds Max ������ ������ ���ϴܿ� ��ġ �� �����Ƿ�, �»���� ������ DirectX���� ������
						// v��ǥ�� 1.0f - v�� �����ؾ��Ѵ�.
						pTVertexData[index].x = m_parser->ParseFLOAT();
						pTVertexData[index].y = m_parser->ParseFLOAT();
						pTVertexData[index].y = 1.0f - pTVertexData[index].y;
					}
				}
			}

			if (m_lexer->FindToken(L"*MESH_NUMTVFACES"))
			{
				numTFaceData = m_parser->ParseDWORD();
				pTFaceData = new MYINDEX[numTFaceData];
			}

			if (m_lexer->FindToken(L"*MESH_TFACELIST"))
			{
				for (DWORD i = 0; i < numTFaceData; i++)
				{
					if (m_lexer->FindToken(L"*MESH_TFACE"))
					{
						DWORD index = m_parser->ParseDWORD();

						// 3ds Max�� ��ǥ�踦 DX ��ǥ��� �����ֱ� ���� y�� z�� ����
						pTFaceData[index]._0 = m_parser->ParseDWORD();
						pTFaceData[index]._2 = m_parser->ParseDWORD();
						pTFaceData[index]._1 = m_parser->ParseDWORD();
					}
				}
			}
		}
	}

	// Push D3D Informations

	vertexCount = numFaceData * 3; // ������ ���ؽ��� ���� : �������� ���� * 3
	if (FAILED(DEVICE->CreateVertexBuffer(vertexCount * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		return false;
	}

	CUSTOMVERTEX* pDstVertices;

	if (FAILED(m_pVB->Lock(0, vertexCount * sizeof(CUSTOMVERTEX), (VOID**)&pDstVertices, 0)))
		return false;

	for (DWORD i = 0; i < numFaceData; ++i)
	{
		// position
		pDstVertices[i * 3].position.x = pVertexData[pFaceData[i]._0].x;
		pDstVertices[i * 3].position.y = pVertexData[pFaceData[i]._0].y;
		pDstVertices[i * 3].position.z = pVertexData[pFaceData[i]._0].z;

		pDstVertices[i * 3 + 1].position.x = pVertexData[pFaceData[i]._1].x;
		pDstVertices[i * 3 + 1].position.y = pVertexData[pFaceData[i]._1].y;
		pDstVertices[i * 3 + 1].position.z = pVertexData[pFaceData[i]._1].z;

		pDstVertices[i * 3 + 2].position.x = pVertexData[pFaceData[i]._2].x;
		pDstVertices[i * 3 + 2].position.y = pVertexData[pFaceData[i]._2].y;
		pDstVertices[i * 3 + 2].position.z = pVertexData[pFaceData[i]._2].z;

		// color
		pDstVertices[i * 3].color = 0xffffff;
		pDstVertices[i * 3 + 1].color = 0xffffff;
		pDstVertices[i * 3 + 2].color = 0xffffff;
	}

	if (pTVertexData != nullptr)
	{
		for (DWORD i = 0; i < numFaceData; ++i)
		{
			// uv
			pDstVertices[i * 3].tu = pTVertexData[pTFaceData[i]._0].x;
			pDstVertices[i * 3].tv = pTVertexData[pTFaceData[i]._0].y;

			pDstVertices[i * 3 + 1].tu = pTVertexData[pTFaceData[i]._1].x;
			pDstVertices[i * 3 + 1].tv = pTVertexData[pTFaceData[i]._1].y;

			pDstVertices[i * 3 + 2].tu = pTVertexData[pTFaceData[i]._2].x;
			pDstVertices[i * 3 + 2].tv = pTVertexData[pTFaceData[i]._2].y;
		}
	}

	m_pVB->Unlock();

	delete[] pVertexData;
	delete[] pFaceData;
	delete[] pTVertexData;
	delete[] pTFaceData;

	return true;
}

bool AseHandler::Setup()
{
	if (m_lexer == nullptr)
		m_lexer = new AseLexer();

	if (m_parser == nullptr)
		m_parser = new AseParser(m_lexer);

	return (m_lexer != nullptr) && (m_parser != nullptr);
}

void AseHandler::SetAseFile(const wstring _path)
{
	if (Setup())
	{
		if (!m_lexer->LoadAseFile(_path))
		{
			wcout << "AseFile Load FAILED!! :  " << _path << endl;
			return;
		}
		m_lexer->MakeToken();

		ParsingMaterialList();
		ParsingGeomObject();
	}
	else cout << "AseHandler Initialize Failed!" << endl;
}

bool AseHandler::SetTexture(wstring path)
{
	return !FAILED(D3DXCreateTextureFromFile(DEVICE, path.c_str(), &m_texture));
}

void AseHandler::Init(void)
{

}

void AseHandler::Update(void)
{
}

void AseHandler::Render(void)
{
	DEVICE->SetTransform(D3DTS_WORLD, &node->GetMatrix());

	if(m_texture != NULL) 
		DEVICE->SetTexture(0, m_texture);

	DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	DEVICE->SetFVF(D3DFVF_CUSTOMVERTEX);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, vertexCount / 3);
}

void AseHandler::Exit(void)
{
	if (m_pVB != nullptr)
	{
		m_pVB->Release();
		m_pVB = nullptr;
	}

	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
	cout << "!! Ase Released !! : " << movableName << endl;
}
