#pragma once
#include "SceneManager.h"
#include "Root.h"
#include "Font2D.h"

NAMESPACE(Tipp7)

enum class SHOWCASE {
	LERP,
	SLERP,
	CATMULL,
	SQUAD
};

class SquadApp
	: public SceneManager
{
public:
	explicit SquadApp(void);
	~SquadApp(void) {};

	int points = 0;
	int circle = 0;
	float time = 0.0f;

	SHOWCASE moveType = SHOWCASE::CATMULL;
	SHOWCASE rotateType = SHOWCASE::SQUAD;

	Font2D* font0;
	Font2D* font1;

	vector<D3DXQUATERNION> quaternion_list;
	vector<Vector3> catmull_list;
	D3DXQUATERNION s0;
	D3DXQUATERNION s1;

	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;

	void CreatePoint();
	void SettingSquad();
};

END