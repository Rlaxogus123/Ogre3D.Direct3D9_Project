#pragma once
#include "SceneManager.h"
#include "Singleton.h"
#include "MeshManager.h"
#include "RM.h"

NAMESPACE(Tipp7)

class Root : public Singleton<Root>
{
private:
	list<SceneManager*> sceneList;
public:
	explicit Root(void) {};
	~Root(void) {};

	SceneManager* createSceneManager(const string _sceneName = "Default Scene");
	SceneManager* createSceneManager(const string _sceneName, SceneManager* app);
	SceneManager* getSceneManager(const string _sceneName);
	SceneManager* curScene = nullptr;

	void ReloadSceneManager(const string _sceneName = "Default Scene");

	void RootInit(void);
	void RootUpdate(void);
	void RootRender(void);
	void RootExit(void);
};

END