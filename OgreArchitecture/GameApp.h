#pragma once
#include "SceneManager.h"
#include "Root.h"

NAMESPACE(Tipp7)

class GameApp
	: public SceneManager
{
public:
	explicit GameApp(void);
	~GameApp(void) {};

	bool pointlock;
	float aimAmount = 0.1f;

	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

END