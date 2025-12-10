#pragma once
#include "RefPtr.h"

namespace ke
{
	template<typename T>
	template<typename... Args>
	RefPtr<T> RefPtr<T>::makeRefPtr(Args&&... args)
	{
		return RefPtr<T>(new T(forward<Args>(args)...));
	}

	template<typename T>
	RefPtr<T>::RefPtr(T* ptr)
		: _ptr(ptr), _refCount(new size_t(1))
	{
	}
}