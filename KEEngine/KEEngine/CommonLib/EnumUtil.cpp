#include "CommonLibPch.h"
#include "EnumUtil.h"

namespace ke
{
	template<typename T>
	const std::unordered_map<size_t, std::string>& EnumWrapper<T>::getStringTable()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(EmumWrapper);
	}
	template<typename T>
	std::string EnumWrapper<T>::toString(T val)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(EmumWrapper);
	}

	template<typename T>
	std::optional<T> EnumWrapper<T>::fromString(const std::string_view& str)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(EmumWrapper);
	}
}
