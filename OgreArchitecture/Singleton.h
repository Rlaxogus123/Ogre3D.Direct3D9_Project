#pragma once

NAMESPACE(Tipp7)

template <class T>
class Singleton
{
private:
	static T* instance;
public:
	static T* GetInstance(void)
	{
		if (instance == nullptr)
			instance = new T();
		return instance;
	}

	static void DestroyInstance(void)
	{
		delete instance;
	}
};

template<class T>
T* Singleton<T>::instance = nullptr;

END