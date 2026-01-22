#pragma once
#include <memory>

#define USE_MANUAL_PTR true

#if USE_MANUAL_PTR
#define PTR(T) ke::Ptr<T>
#define MAKE_PTR(T, ...) ke::makePtr<T>(__VA_ARGS__)
#else
#define PTR(T) std::unique_ptr<T>
#define MAKE_PTR(T, ...) std::make_unique<T>(__VA_ARGS__)
#endif // DEBUG

namespace ke
{
	template<typename T>
	class Ptr;

	template<typename T, typename ...Args>
	Ptr<T> makePtr(Args... args);

	template<typename T>
	class Ptr
	{
		template<typename U>
		friend class Ptr;

	public:
		Ptr(T* ptr = nullptr);
		Ptr(const Ptr<T>& other) = delete;
		Ptr(Ptr<T>&& other) noexcept;
		~Ptr();

	public:
		Ptr<T>& operator=(const Ptr<T>& other) = delete;
		Ptr<T>& operator=(Ptr<T>&& other) noexcept;
		Ptr<T>& operator=(std::nullptr_t);

	public:
		template<typename U>
		Ptr<T>& operator=(const Ptr<U>& other) = delete;
		template<typename U>
		Ptr<T>& operator=(Ptr<U>&& other);


	public:
		inline bool operator==(std::nullptr_t) { return _ptr == nullptr; }
		inline bool operator!=(std::nullptr_t) { return _ptr != nullptr; }

	public:
		inline T* get() const { return _ptr; }
		inline T* operator->() const { return _ptr; }

	private:
		inline void release();
		template<typename U>
		inline void move(Ptr<U>&& other) noexcept;

	private:
		T* _ptr = nullptr;
	};
}
#include "Ptr.hpp"	