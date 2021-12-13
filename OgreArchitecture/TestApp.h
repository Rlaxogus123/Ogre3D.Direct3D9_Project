#pragma once
#include "SceneManager.h"
#include "Root.h"

NAMESPACE(Tipp7)

class TestApp
	: public SceneManager
{
public:
	explicit TestApp(void);
	~TestApp(void) {};

	bool isMy = false;

	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

END