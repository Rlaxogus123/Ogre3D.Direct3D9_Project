#include "DXUT.h"
#include "Root.h"

USING(Tipp7)

SceneManager* Root::createSceneManager(const string _sceneName)
{
	SceneManager* scnMgr = new SceneManager();
	scnMgr->sceneName = _sceneName;

	for (auto& it : sceneList)
	{
		if (it->sceneName == _sceneName)
		{
			cout << _sceneName << " is Already added!";
			return scnMgr;
		}
	}
	sceneList.push_back(scnMgr);
	if (curScene == nullptr)
	{
		cout << "[ Scene Selected : " << scnMgr->sceneName << " ]" << endl;
		curScene = scnMgr;
		curScene->Init();
	}
	return scnMgr;
}

SceneManager* Root::getSceneManager(const string _sceneName)
{
	if (curScene != nullptr) curScene->Exit();
	for (auto& it : sceneList)
	{
		if (it->sceneName._Equal(_sceneName))
		{
			cout << "[ Scene Selected : " << it->sceneName << " ]" << endl;
			curScene = it;
			curScene->Init();
			return it;
		}
	}
	cout << "Could not Find Scene!" << endl;
	return nullptr;
}

void Root::RootInit(void)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	cout << "Root Initialized" << endl;
}

void Root::RootUpdate(void)
{
	if (curScene != nullptr) curScene->Update();
}

void Root::RootRender(void)
{
	if (curScene != nullptr) curScene->Render();
}

void Root::RootExit(void)
{
	curScene = nullptr;
	for (auto& it : sceneList)
	{
		it->Exit();
		delete it;
	}
	sceneList.clear();
	exit(0);
}
