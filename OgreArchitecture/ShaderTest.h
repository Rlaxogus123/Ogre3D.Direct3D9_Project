#pragma once
#include "SceneManager.h"
#include "Root.h"

NAMESPACE(Tipp7)

class ShaderTest
	: public SceneManager
{
public:
	explicit ShaderTest(void);
	~ShaderTest(void) {};

	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

END