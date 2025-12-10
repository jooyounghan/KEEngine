#pragma once
#include "UtilityCommon.h"

namespace ke
{
	template<typename T>
	class RefPtr
	{
	public:
		template<typename... Args>
		static RefPtr<T> makeRefPtr(Args&&... args);

	public:
		explicit RefPtr(T* ptr);
		~RefPtr()
		{
			release();
		}

	public:
		RefPtr(const RefPtr& other)
			: _ptr(other._ptr)
		{
			addRef();
		}
		RefPtr& operator=(const RefPtr& other)
		{
			if (this != &other)
			{
				release();
				_ptr = other._ptr;
				addRef();
			}
			return *this;
		}
	public:
		RefPtr(RefPtr&& other) noexcept
			: _ptr(other._ptr)
		{
			other._ptr = nullptr;
		}
		RefPtr& operator=(RefPtr&& other) noexcept
		{
			if (this != &other)
			{
				release();
				_ptr = other._ptr;
				other._ptr = nullptr;
			}
			return *this;
		}

	private:
		T*		_ptr = nullptr;
		size_t* _refCount = nullptr;

	private:
		void addRef()
		{
			if (_ptr)
			{
				_ptr->addRef();
			}
		}
		void release()
		{
			if (_ptr)
			{
				--(*_refCount);
				if (*_refCount == 0)
				{
					delete _ptr;
					delete _refCount;
				}
			}
			_ptr = nullptr;
			_refCount = nullptr;
		}

	};
}

#include "RefPtr.hpp"