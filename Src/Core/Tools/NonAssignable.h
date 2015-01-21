#pragma once

// usage:
// class MyClass : private NonAssignable {};

namespace Tools {
// protection from unintended ADL
namespace NonAssignable_ {

class NonAssignable
{
protected:
	NonAssignable() {}
	~NonAssignable() {}
private:
	const NonAssignable& operator=(const NonAssignable&);
	const NonAssignable& operator=(const NonAssignable&&);
};

} // namespace NonAssignable_

typedef NonAssignable_::NonAssignable NonAssignable;
} // namespace Tools