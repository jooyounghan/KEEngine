#pragma once

namespace ke
{
	template <typename T>
	class EnumWrapper
	{
	public:
		static const std::unordered_map<size_t, std::string>& getStringTable();
		static const std::string& toString(T val);
		static const std::optional<T> fromString(const std::string_view& str);
	};
}
#include "EnumUtil.hpp"