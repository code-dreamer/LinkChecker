#pragma once
#include <mutex>
#include <cassert>

#pragma warning(push)
#pragma warning(disable : 4640)	

template<typename T>
class Singleton
{
public:
	static T* instance()	
	{
		assert(!isDestructed_);

		(void)isDestructed_; // prevent removing is_destructed in Release configuration

		std::lock_guard<std::mutex> lock(mutex());
		static T instance;
		return &instance;
	}

private:
	static bool isDestructed_;

	static std::mutex& mutex()	
	{
		static std::mutex mutex;
		return mutex;
	}

protected:
	Singleton() {}
	virtual ~Singleton() 
	{ 
		isDestructed_ = true; 
	}
};

#pragma warning(pop)

// force creating mutex before main() is called
template<typename T>
bool Singleton<T>::isDestructed_ = (Singleton<T>::mutex(), false);