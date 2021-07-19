#pragma once
#include "Node.h"
#include "MovableObject.h"

NAMESPACE(Tipp7)

class SceneNode
	: public Node
{
private:
	list<MovableObject*> movablegroup;
public:
	SceneNode(void) {};
	virtual ~SceneNode(void) {};

	void attachObject(MovableObject* _obj);
	void detachObject(MovableObject* _obj);
	MovableObject* getAttachObject(const string _movableName);

	SceneNode* createChildSceneNode(const string _nodeName);
	SceneNode* GetChild(const string _nodeName);
	
	void Init(void);
	void Update(void) override;
	void Render(void) override;
	void Exit(void);
};

END