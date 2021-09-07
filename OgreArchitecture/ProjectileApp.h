#pragma once
#include "SceneManager.h"
#include "Root.h"
#include "Font2D.h"

NAMESPACE(Tipp7)

class ProjectileApp
	: public SceneManager
{
public:
	explicit ProjectileApp(void);
	~ProjectileApp(void) {};

	Font2D* font0;
	Font2D* font1;
	Font2D* font2;
	Font2D* font3;

	SceneNode* n_effect[50];
	Entity* effect[50];

	Vector3 firstPos = Vector3(0, 50, 50);

	bool pointlock;
	float aimAmount = 0.1f;

	float time = 0.0f;
	float timeAmount = 1.0f;
	float power = 20;
	int angle = 0;
	bool isFire;

	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

END