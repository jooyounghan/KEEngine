#include "TraitCommon.h"

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
		move(std::move(other));
	}

	template<typename T>
	Ptr<T>::~Ptr()
	{
		release();
	}
	
	template<typename T>
	Ptr<T>& Ptr<T>::operator=(Ptr<T>&& other) noexcept
	{
		move(std::move(other));
		return *this;
	}

	template<typename T>
	Ptr<T>& Ptr<T>::operator=(std::nullptr_t)
	{
		release();
		return *this;
	}

	template<typename T>
	template<typename U>
	Ptr<T>& Ptr<T>::operator=(Ptr<U>&& other)
	{
		move(std::move(other));
		return *this;
	}

	template<typename T>
	inline void Ptr<T>::release()
	{
		if (_ptr != nullptr)
		{
			delete _ptr;
		}
		_ptr = nullptr;
	}

	template<typename T>
	template<typename U>
	inline void Ptr<T>::move(Ptr<U>&& other) noexcept
	{
		STATIC_ASSERT_IS_BASE_OF(T, U);
		_ptr = other._ptr;
		other._ptr = nullptr;
	}
}