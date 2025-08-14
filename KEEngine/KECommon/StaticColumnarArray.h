#pragma once
#include "LinearContainer.h"
#include "MemoryCommon.h"
namespace ke
{
	template<size_t Count, typename ...Types>
	class StaticColumnarArray
	{
	public:
		StaticColumnarArray() = default;
		StaticColumnarArray(const StaticColumnarArray& other) = default;
		StaticColumnarArray(StaticColumnarArray&& other) noexcept = default;

	public:
		StaticColumnarArray& operator=(const StaticColumnarArray& other) = default;
		StaticColumnarArray& operator=(StaticColumnarArray&& other) noexcept = default;

	public:
		~StaticColumnarArray() = default;


#pragma region ColumnDefine
		template<typename T>
		using Column = LinearContainer<T, Count>;

		template<size_t ColumnIndex>
		using ColumnType = typename GetType<ColumnIndex, Types...>::Type;


		template<typename... Ts>
		struct Columns;

		template<>
		struct Columns<> {};

		template<typename T, typename... Ts>
		struct Columns<T, Ts...> : Columns<Ts...>
		{
			Column<T> _column;
		};

	private:
		template <size_t I, size_t J, typename... Ts>
		struct ColumnGetter;

		template <size_t I, size_t J, typename T, typename... Ts>
		struct ColumnGetter<I, J, T, Ts...>
		{
			static Column<ColumnType<I>>& get(Columns<T, Ts...>& s)
			{
				return ColumnGetter<I, J + 1, Ts...>::get(s);
			}
			static const Column<ColumnType<I>>& get(const Columns<T, Ts...>& s)
			{
				return ColumnGetter<I, J + 1, Ts...>::get(s);
			}
		};

		template <size_t I, typename T, typename... Ts>
		struct ColumnGetter<I, I, T, Ts...>
		{
			static Column<T>& get(Columns<T, Ts...>& s) { return s._column; }
			static const Column<T>& get(const Columns<T, Ts...>& s) { return s._column; }
		};
#pragma endregion

	private:
		Columns<Types...> _columns;

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