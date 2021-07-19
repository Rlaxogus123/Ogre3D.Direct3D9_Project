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
	movable->Init();
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
	movable->Init();
	return movable;
}

Camera* SceneManager::getCamera(const string _movableName)
{
	for (auto& it : camList)
		if (it->movableName._Equal(_movableName))
			return it;
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
	for (auto& it : nodelist)
	{
		if (it->activeSelf())
			it->Render();
	}
}

void SceneManager::Exit(void)
{
}
