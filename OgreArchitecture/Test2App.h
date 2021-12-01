#pragma once
#include "SceneManager.h"
#include "Font2D.h"
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

	int points = 0;
	int circle = 0;
	float time = 0.0f;

	float float_t = 0;
	float float_b = 0;
	float float_c = 0;

	Font2D* font_t;
	Font2D* font_b;
	Font2D* font_c;

	vector<Vector3> catmull_list;
	void CreatePoint();
};

END