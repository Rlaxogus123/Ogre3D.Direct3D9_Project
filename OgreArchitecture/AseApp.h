#pragma once
#include "SceneManager.h"
#include "Root.h"

NAMESPACE(Tipp7)

class AseApp
	: public SceneManager
{
public:
	explicit AseApp(void);
	~AseApp(void) {};

	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

END