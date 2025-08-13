#pragma once
#include "StaticColumnarArray.h"

namespace ke
{
	template<size_t Count, typename ...Ts>
	StaticColumnarArray<Count, Ts...>::StaticColumnarArray()
	{
	}

	template<size_t Count, typename ...Ts>
	template<typename ...Args>
	StaticColumnarArray<Count, Ts...>::StaticColumnarArray(Args ...args)
	{
	}

	template<size_t Count, typename ...Types>
	StaticColumnarArray<Count, Types...>::StaticColumnarArray(const StaticColumnarArray& other)
	{
	}

	template<size_t Count, typename ...Types>
	StaticColumnarArray<Count, Types...>::StaticColumnarArray(StaticColumnarArray&& other) noexcept
	{
	}

	template<size_t Count, typename ...Types>
	StaticColumnarArray<Count, Types...>& StaticColumnarArray<Count, Types...>::operator=(const StaticColumnarArray& other)
	{
	}

	template<size_t Count, typename ...Types>
	StaticColumnarArray<Count, Types...>& StaticColumnarArray<Count, Types...>::operator=(StaticColumnarArray&& other) noexcept
	{
	}

	template<size_t Count, typename ...Types>
	StaticColumnarArray<Count, Types...>::~StaticColumnarArray() 
	{
	
	}

	template<size_t Count, typename ...Types>
	template<typename T>
	StaticColumnarArray<Count, Types...>::Column<T>::Column()
	{
	}
	
	template<size_t Count, typename ...Types>
	template<typename T>
	StaticColumnarArray<Count, Types...>::Column<T>::Column(const Column& column)
	{
	}
	
	template<size_t Count, typename ...Types>
	template<typename T>
	StaticColumnarArray<Count, Types...>::Column<T>::Column(Column&& column)
	{
	}

	template<size_t Count, typename ...Types>
	template<typename T>
	StaticColumnarArray<Count, Types...>::Column<T>& StaticColumnarArray<Count, Types...>::Column<T>::operator=(const Column& column)
	{

	}
	template<size_t Count, typename ...Types>
	template<typename T>
	StaticColumnarArray<Count, Types...>::Column<T>& StaticColumnarArray<Count, Types...>::Column<T>::operator=(Column&& column)
	{

	}

	template<size_t Count, typename ...Types>
	template<typename T>
	StaticColumnarArray<Count, Types...>::Column<T>::~Column()
	{
	}

	template<size_t Count, typename ...Types>
	template<size_t ColumnIndex>
	StaticColumnarArray<Count, Types...>::Column<typename GetType<ColumnIndex, Types...>::Type>& StaticColumnarArray<Count, Types...>::getColumn()
	{
		static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
		return GetBuf<ColumnIndex, 0, Types...>::get(_columns);
	}

	template<size_t Count, typename ...Types>
	template<size_t ColumnIndex>
	const StaticColumnarArray<Count, Types...>::Column<typename GetType<ColumnIndex, Types...>::Type>& StaticColumnarArray<Count, Types...>::getColumn() const
	{
		static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
		return GetBuf<ColumnIndex, 0, Types...>::get(_columns);
	}

	template<size_t Count, typename ...Types>
	template<size_t ColumnIndex>
	typename GetType<ColumnIndex, Types...>::Type& StaticColumnarArray<Count, Types...>::getElement(size_t index)
	{
		static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
		using CurrentType = typename GetType<ColumnIndex, Types...>::Type;

		Column<CurrentType>& column = getColumn<ColumnIndex>();
		return *(reinterpret_cast<CurrentType*>(&column._storage[0]) + index);
	}

	template<size_t Count, typename ...Types>
	template<size_t ColumnIndex>
	const typename GetType<ColumnIndex, Types...>::Type& StaticColumnarArray<Count, Types...>::getElement(size_t index) const
	{
		static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
		using CurrentType = typename GetType<ColumnIndex, Types...>::Type;

		const Column<CurrentType>& column = getColumn<ColumnIndex>();
		return *(reinterpret_cast<const CurrentType*>(&column._storage[0]) + index);
	}
}