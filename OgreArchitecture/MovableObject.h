#pragma once
#include "Node.h"

NAMESPACE(Tipp7)

class MovableObject
{
private:

public:
	explicit MovableObject(void) {};
	virtual ~MovableObject(void) {};

	Node* node = nullptr;
	string movableName = "";

	bool isEnable = true;
	constexpr bool activeSelf() { return isEnable; };

	virtual void Init(void); // when you call attachObject();
	virtual void Update(void);
	virtual void Render(void);
	virtual void Exit(void);
};

END