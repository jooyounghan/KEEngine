#pragma once

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	template<typename... Args>
	void ReflectPropertyBinder<ObjectType, PropertyType>::bindProperty(
		IReflectProperty* reflectProperty
		, const EReflectUIOption& uiOption
		, Args... args
	)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(bindProperty);
	}
}