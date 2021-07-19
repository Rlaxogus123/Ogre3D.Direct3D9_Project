#pragma once
#include "SceneNode.h"
#include "Camera.h"

NAMESPACE(Tipp7)

class SceneManager
{
private:
	list<SceneNode*> nodelist;
	list<MovableObject*> movableList;
	list<Camera*> camList;
public:
	explicit SceneManager(void) {};
	virtual ~SceneManager(void) {}; 

	string sceneName = "";
	bool isActive = false;

	SceneNode* createChildSceneNode(const string _childName);
	SceneNode* getSceneNode(const string _childName);
	MovableObject* createMovableObject(const string _movableName);
	MovableObject* getMovableObject(const string _movableName);
	Camera* createCamera(const string _movableName);
	Camera* getCamera(const string _movableName);

	virtual void Init(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void Exit(void);
};

END