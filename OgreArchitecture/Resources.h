#pragma once

NAMESPACE(Tipp7)

class Resources
{
public:
	explicit Resources(void) {};
	explicit Resources(const Resources& copy);
	virtual ~Resources(void) {};

	bool isCloned = false;
	string resName = "";

	virtual Resources* Clone(void) PURE;
	virtual void Exit(void) PURE;
};

END