#pragma once
#include "UtilityCommon.h"

namespace ke
{
	template<typename T>
	class UniquePtr
	{
	public:
		template<typename... Args>
		static UniquePtr<T> makeUniquePtr(Args&&... args)
		{
			return UniquePtr<T>(new T(forward<Args>(args)...));
		}

	public:
		explicit UniquePtr(T* ptr = nullptr)
			: _ptr(ptr)
		{
		}
		~UniquePtr()
		{
			reset();
		}
	public:
		UniquePtr(const UniquePtr&) = delete;
		UniquePtr& operator=(const UniquePtr&) = delete;
	public:
		UniquePtr(UniquePtr&& other) noexcept
			: _ptr(other._ptr)
		{
			other._ptr = nullptr;
		}
		UniquePtr& operator=(UniquePtr&& other) noexcept
		{
			if (this != &other)
			{
				reset();
				_ptr = other._ptr;
				other._ptr = nullptr;
			}
			return *this;
		}
	public:
		inline T* get() const { return _ptr; }
		inline T& operator*() const { return *_ptr; }
		inline T* operator->() const { return _ptr; }
		inline explicit operator bool() const { return _ptr != nullptr; }
	public:
		void reset(T* ptr = nullptr)
		{
			if (_ptr)
			{
				delete _ptr;
			}
			_ptr = ptr;
		}
	private:
		T* _ptr = nullptr;
	};
}