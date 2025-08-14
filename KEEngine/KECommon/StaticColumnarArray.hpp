#pragma once
#include "StaticColumnarArray.h"

namespace ke
{
	template<size_t Count, typename ...Types>
	template<size_t ColumnIndex>
	StaticColumnarArray<Count, Types...>::Column<typename GetType<ColumnIndex, Types...>::Type>& StaticColumnarArray<Count, Types...>::getColumn()
	{
		static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
		return ColumnGetter<ColumnIndex, 0, Types...>::get(_columns);
	}

	template<size_t Count, typename ...Types>
	template<size_t ColumnIndex>
	const StaticColumnarArray<Count, Types...>::Column<typename GetType<ColumnIndex, Types...>::Type>& StaticColumnarArray<Count, Types...>::getColumn() const
	{
		static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
		return ColumnGetter<ColumnIndex, 0, Types...>::get(_columns);
	}

	template<size_t Count, typename ...Types>
	template<size_t ColumnIndex>
	typename GetType<ColumnIndex, Types...>::Type& StaticColumnarArray<Count, Types...>::getElement(size_t index)
	{
		static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
		Column<ColumnType<ColumnIndex>>& column = getColumn<ColumnIndex>();
		return column[index];
	}

	template<size_t Count, typename ...Types>
	template<size_t ColumnIndex>
	const typename GetType<ColumnIndex, Types...>::Type& StaticColumnarArray<Count, Types...>::getElement(size_t index) const
	{
		static_assert(ColumnIndex < sizeof...(Types), "Index out of bounds for StaticColumnarArray columns");
		const Column<ColumnType<ColumnIndex>>& column = getColumn<ColumnIndex>();
		return column._data[index];
	}
}