#pragma once
#include "ReflectProperty.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectPropertyBinder
	{
	public:
		template<typename... Args>
		static void bindProperty(
			IReflectProperty* reflectProperty
			, const EReflectUIOption& uiOption
			, Args... args
		);
	};
}

#include "ReflectPropertyBinder.hpp"