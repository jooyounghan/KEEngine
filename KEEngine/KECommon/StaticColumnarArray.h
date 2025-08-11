#pragma once
#include "MemoryCommon.h"

namespace ke
{
	template<size_t Count, typename ...Types>
	class StaticColumnarArray
	{
	public:
		StaticColumnarArray();
		template<typename... Args>
		StaticColumnarArray(Args... args);
		StaticColumnarArray(const StaticColumnarArray& other);
		StaticColumnarArray(StaticColumnarArray&& other) noexcept;

	public:
		StaticColumnarArray& operator=(const StaticColumnarArray& other);
		StaticColumnarArray& operator=(StaticColumnarArray&& other) noexcept;

	public:
		~StaticColumnarArray();


#pragma region ColumnDefine
	private:
		template<typename T>
		struct Column
		{
			alignas(T) byte _storage[sizeof(T) * Count];

#ifdef _DEBUG
		private:
			const T* _data = reinterpret_cast<T*>(&_storage[0]);
			CONSTEXPR_INLINE static constexpr size_t _count = Count;
#endif			
		};

		template<typename... Ts>
		struct Columns;

		template<>
		struct Columns<> {};

		template<typename T, typename... Ts>
		struct Columns<T, Ts...> : Columns<Ts...>
		{
			Column<T> _col;
		};

	private:
		template <size_t I, size_t J, typename... Ts>
		struct GetBuf;

		template <size_t I, size_t J, typename T, typename... Ts>
		struct GetBuf<I, J, T, Ts...>
		{
			static Column<typename GetType<I, Types...>::Type>& get(Columns<T, Ts...>& s)
			{
				return GetBuf<I, J + 1, Ts...>::get(s);
			}
			static const Column<typename GetType<I, Types...>::Type>& get(const Columns<T, Ts...>& s)
			{
				return GetBuf<I, J + 1, Ts...>::get(s);
			}
		};

		template <size_t I, typename T, typename... Ts>
		struct GetBuf<I, I, T, Ts...>
		{
			static Column<T>& get(Columns<T, Ts...>& s) { return s._col; }
			static const Column<T>& get(const Columns<T, Ts...>& s) { return s._col; }
		};
#pragma endregion

	private:
		Columns<Types...> _columns;

	public:
		template<size_t ColumnIndex>
		using ColumnType = typename GetType<ColumnIndex, Types...>::Type;

	public:
		template<size_t ColumnIndex>
		Column<ColumnType<ColumnIndex>>& getColumn();

		template<size_t ColumnIndex>
		const Column<ColumnType<ColumnIndex>>& getColumn() const;

		template<size_t ColumnIndex>
		ColumnType<ColumnIndex>& getElement(size_t index);

		template<size_t ColumnIndex>
		const ColumnType<ColumnIndex>& getElement(size_t index) const;
	};
}
#include "StaticColumnarArray.hpp"