#pragma once

namespace ke
{
	template <typename T>
	class EnumWrapper
	{
	public:
		static const std::unordered_map<size_t, std::string>& getStringTable();
		static std::string toString(T val);
		static std::optional<T> fromString(const std::string_view& str);
	};

	class EnumUtil
	{
	public:
		template<typename T>
		inline static bool isEnumFlagOn(T value, T flag) { return (static_cast<std::underlying_type_t<T>>(value) & static_cast<std::underlying_type_t<T>>(flag)) != 0; }
	};
}

#include "EnumUtil.hpp"