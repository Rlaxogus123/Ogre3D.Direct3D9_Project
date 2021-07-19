#pragma once
#include "SceneManager.h"
#include "Singleton.h"

NAMESPACE(Tipp7)

class Root : public Singleton<Root>
{
private:
	list<SceneManager*> sceneList;
public:
	explicit Root(void) {};
	~Root(void) {};

	SceneManager* createSceneManager(const string _sceneName = "Default Scene");
	SceneManager* getSceneManager(const string _sceneName);
	SceneManager* curScene = nullptr;

	void RootInit(void);
	void RootUpdate(void);
	void RootRender(void);
	void RootExit(void);
};

END