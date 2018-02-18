#ifndef _SINGLETON_H
#define _SINGLETON_H

template<typename T>
class Singleton
{
public:
	static T& GetInstance();

	// Do not want to copy a Singleton instance
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
protected:
	~Singleton() = default;
	static T* _instance;

	Singleton() = default;
};

template<typename T>
T* Singleton<T>::_instance = nullptr;

template<typename T>
T& Singleton<T>::GetInstance()
{
	// Guaranteed to be destroyed.
	// Instantiated on first use.
	static T instance;

	return instance;
}

#endif