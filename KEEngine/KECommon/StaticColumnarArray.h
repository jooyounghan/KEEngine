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
		~StaticColumnarArray() {};

#pragma region ColumnDefine
	private:
		template<typename T>
		struct SoAColumn
		{
			alignas(T) byte _storage[sizeof(T) * Count];

#ifdef _DEBUG
		private:
			const T* _data = reinterpret_cast<T*>(&_storage[0]);
#endif			
		};

		template<typename... Ts>
		struct SoAColumns;

		template<>
		struct SoAColumns<> {};

		template<typename T, typename... Ts>
		struct SoAColumns<T, Ts...> : SoAColumns<Ts...>
		{
			SoAColumn<T> _col;
		};

	private:
		template <size_t I, size_t J, typename... Ts>
		struct GetBuf;

		template <size_t I, size_t J, typename T, typename... Ts>
		struct GetBuf<I, J, T, Ts...>
		{
			static SoAColumn<typename GetType<I, Types...>::Type>& get(SoAColumns<T, Ts...>& s)
			{
				return GetBuf<I, J + 1, Ts...>::get(s);
			}
			static const SoAColumn<typename GetType<I, Types...>::Type>& get(const SoAColumns<T, Ts...>& s)
			{
				return GetBuf<I, J + 1, Ts...>::get(s);
			}
		};

		template <size_t I, typename T, typename... Ts>
		struct GetBuf<I, I, T, Ts...>
		{
			static SoAColumn<T>& get(SoAColumns<T, Ts...>& s) { return s._col; }
			static const SoAColumn<T>& get(const SoAColumns<T, Ts...>& s) { return s._col; }
		};
#pragma endregion

	private:
		SoAColumns<Types...> _columns;

	public:
		template<size_t Index>
		typename GetType<Index, Types...>::Type& getColumn(size_t index)
		{
			static_assert(Index < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
			using CurrentType = typename GetType<Index, Types...>::Type;

			SoAColumn<CurrentType>& column = GetBuf<Index, 0, Types...>::get(_columns);
			return *(reinterpret_cast<CurrentType*>(&column._storage[0]) + index);
		}

		template<size_t Index>
		const typename GetType<Index, Types...>::Type& getColumn(size_t index) const
		{
			static_assert(Index < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
			using CurrentType = typename GetType<Index, Types...>::Type;

			const SoAColumn<CurrentType>& column = GetBuf<Index, 0, Types...>::get(_columns);
			return *(reinterpret_cast<const CurrentType*>(&column._storage[0]) + index);
		}
	};
}
#include "StaticColumnarArray.hpp"