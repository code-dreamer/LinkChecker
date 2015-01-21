#pragma once

namespace Tools {
namespace Cpp {

// TODO: change to GetTicksCount
// Measure function call time in ms
template <class Function>
qint64 TimedCall(Function&& calledFunc)
{
	QElapsedTimer elapsedTimer;
	elapsedTimer.start();

	calledFunc();

	return elapsedTimer.elapsed();
}

template<class T, std::size_t N> 
char(&lenghtOf(T(&)[N]))[N];

template<typename T>
static void safeDelete(T*& ptr)
{
	typedef char TypeIsCompleteCheck[sizeof(T)];
	if (ptr != nullptr) {
		delete ptr;
		ptr = nullptr;
	}
}

template<typename T>
static void safeDeleteA(T*& ptr) 
{
	typedef char TypeIsCompleteCheck[sizeof(T)];
	if (ptr != nullptr) {
		delete[] ptr;
		ptr = nullptr;
	}
}

} // namespace Cpp
} // namespace Tools

#define STATIC_ARRAY_SIZE(arr) sizeof(Tools::Cpp::lenghtOf(arr))


