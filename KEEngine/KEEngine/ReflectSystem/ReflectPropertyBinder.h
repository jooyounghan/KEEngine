#pragma once
#include "ReflectProperty.h"

namespace ke
{
	template<typename PropertyType>
	class ReflectPropertyBinder
	{
	public:
		static void bindProperty(
			IReflectProperty* reflectProperty
			, const EReflectUIOption& uiOption
		);

		template<typename... Args>
		static void bindProperty(
			IReflectProperty* reflectProperty
			, const EReflectUIOption& uiOption
			, const Args&... args
		);
	};
}

#include "ReflectPropertyBinder.hpp"