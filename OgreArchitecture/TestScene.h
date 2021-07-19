#pragma once
#include "SceneManager.h"

NAMESPACE(Tipp7)

class TestApp
{
public:
	explicit TestApp(void) {};
	~TestApp(void) {};

	void Init();
	void Update();
	void Render();
	void Exit();
};

END