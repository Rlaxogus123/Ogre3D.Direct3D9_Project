#include "DXUT.h"
#include "SceneManager.h"

USING(Tipp7)

SceneNode* SceneManager::createChildSceneNode(const string _childName)
{
	SceneNode* scnNode = new SceneNode();
	scnNode->nodeName = _childName;
	for(auto& it : nodelist)
	{
		if (it->nodeName._Equal(_childName))
		{
			cout << "This SceneNode name is Already added : " << _childName << endl;
			scnNode->nodeName = _childName + "_copy";
			break;
		}
	}
	nodelist.push_back(scnNode);
	scnNode->Init();
	return scnNode;
}

SceneNode* SceneManager::getSceneNode(const string _childName)
{
	for (auto& it : nodelist)
		if (it->nodeName._Equal(_childName))
			return it;
}

MovableObject* SceneManager::createMovableObject(const string _movableName)
{
	MovableObject* movable = new MovableObject();
	movable->movableName = _movableName;
	for (auto& it : movableList)
	{
		if (it->movableName._Equal(_movableName))
		{
			cout << "This MovableObject name is Already added : " << _movableName << endl;
			movable->movableName = _movableName + "_copy";
			break;
		}
	}
	movableList.push_back(movable);
	return movable;
}

MovableObject* SceneManager::getMovableObject(const string _movableName)
{
	for (auto& it : movableList)
		if (it->movableName._Equal(_movableName))
			return it;
}

Camera* SceneManager::createCamera(const string _movableName)
{
	Camera* movable = new Camera();
	movable->movableName = _movableName;
	for (auto& it : movableList)
	{
		if (it->movableName._Equal(_movableName))
		{
			cout << "This Camera name is Already added : " << _movableName << endl;
			movable->movableName = _movableName + "_copy";
			break;
		}
	}
	movableList.push_back(movable);
	return movable;
}

Camera* SceneManager::getCamera(const string _movableName)
{
	for (auto& it : camList)
		if (it->movableName._Equal(_movableName))
			return it;
}

Entity* SceneManager::createEntity(const string _movableName, const wstring _xfilePath)
{
	Entity* movable = new Entity();
	movable->movableName = _movableName;
	for (auto& it : movableList)
	{
		if (it->movableName._Equal(_movableName))
		{
			cout << "This Entity name is Already added : " << _movableName << endl;
			movable->movableName = _movableName + "_copy";
			break;
		}
	}
	movableList.push_back(movable);
	movable->SetXFile(_xfilePath);
	return movable;
}

Entity* SceneManager::getEntity(const string _movableName)
{
	for (auto& it : movableList)
		if (it->movableName._Equal(_movableName))
			return (Entity*)it;
	return nullptr;
}

Light* SceneManager::createLight(const string _movableName)
{
	Light* movable = new Light();
	movable->movableName = _movableName;
	for (auto& it : lightList)
	{
		if (it->movableName._Equal(_movableName))
		{
			cout << "This Light name is Already added : " << _movableName << endl;
			movable->movableName = _movableName + "_copy";
			break;
		}
	}
	movableList.push_back(movable);
	return movable;
}

Light* SceneManager::getLight(const string _movableName)
{
	for (auto& it : lightList)
		if (it->movableName._Equal(_movableName))
			return it;
	return nullptr;
}

void SceneManager::setAmbientLight(const float _r, const float _g, const float _b)
{
	//wtf code
	int nr = _r * 255;
	int ng = _g * 255;
	int nb = _b * 255;
	char cr[3];
	char cg[3];
	char cb[3];
	sprintf(cr, "%02x", nr);
	sprintf(cg, "%02x", ng);
	sprintf(cb, "%02x", nb);
	string str_r(cr);
	string str_g(cg);
	string str_b(cb);
	string str = "00" + str_r + str_g + str_b;
	char fin[9];
	strcpy(fin, str.c_str());
	ambient = (int)strtol(fin, NULL, 16);
}

void SceneManager::Init(void)
{
	cout << sceneName << " is Initialized" << endl;
}

void SceneManager::Update(void)
{
	for (auto& it : nodelist)
	{
		if (it->activeSelf())
			it->Update();
	}
}

void SceneManager::Render(void)
{
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_AMBIENT, ambient);

	for (auto& it : nodelist)
	{
		if (it->activeSelf())
			it->Render();
	}
}

void SceneManager::Exit(void)
{
}
