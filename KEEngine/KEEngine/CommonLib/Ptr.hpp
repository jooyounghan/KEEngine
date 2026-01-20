#include "Ptr.h"
#pragma once

namespace ke
{
	template<typename T, typename ...Args>
	Ptr<T> makePtr(Args... args)
	{
		return Ptr<T>(new T(args...));
	}

	template<typename T>
	Ptr<T>::Ptr(T* ptr)
		: _ptr(ptr)
	{

	}

	template<typename T>
	Ptr<T>::Ptr(Ptr<T>&& other) noexcept
	{
		_ptr = other._ptr;
		other._ptr = nullptr;
	}

	template<typename T>
	Ptr<T>::~Ptr()
	{
		if (_ptr != nullptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
	
	template<typename T>
	Ptr<T>& Ptr<T>::operator=(Ptr<T>&& other) noexcept
	{
		_ptr = other._ptr;
		other._ptr = nullptr;
		return *this;
	}

	template<typename T>
	Ptr<T>& Ptr<T>::operator=(std::nullptr_t)
	{
		if (_ptr != nullptr)
		{
			delete _ptr;
		}
		_ptr = nullptr;
		return *this;
	}
}