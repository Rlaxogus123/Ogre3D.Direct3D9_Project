#pragma once
#include "SceneNode.h"
#include "Entity.h"
#include "Camera.h"
#include "Light.h"

NAMESPACE(Tipp7)

class SceneManager
{
private:
	list<SceneNode*> nodelist;
	list<MovableObject*> movableList;
	list<Camera*> camList;
	list<Light*> lightList;
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

	Entity* createEntity(const string _movableName, const wstring _xfilePath);
	Entity* getEntity(const string _movableName);

	Light* createLight(const string _movableName);
	Light* getLight(const string _movableName);
	void setAmbientLight(const float _r, const float _g, const float _b);
	DWORD ambient = 0;

	virtual void Init(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void Exit(void);
};

END