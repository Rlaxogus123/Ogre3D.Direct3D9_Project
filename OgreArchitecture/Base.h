#pragma once

NAMESPACE(Tipp7)

class Base
{
private:
	int refCount = 0;
public:
	explicit Base(void) {};
	virtual ~Base(void) {};

	int AddReference(void);
	int Release(void);
	virtual void Free(void) {};
};

END