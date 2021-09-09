#pragma once
#include "SceneManager.h"
#include "Root.h"

NAMESPACE(Tipp7)

class Test2App
	: public SceneManager
{
public:
	explicit Test2App(void);
	~Test2App(void) {};

	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

END