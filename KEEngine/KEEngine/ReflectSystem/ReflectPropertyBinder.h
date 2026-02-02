#pragma once
#include "ReflectPropertyBase.h"
#include "ReflectPODProperty.h"
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

		static void bindPropertyInner(
			IReflectProperty* reflectProperty
			, const EReflectUIOption& uiOption
		);

	public:
		template<typename... Args>
		static void bindProperty(
			IReflectProperty* reflectProperty
			, const EReflectUIOption& uiOption
			, const Args&... args
		);

		template<typename... Args>
		static void bindPropertyInner(
			IReflectProperty* reflectProperty
			, const EReflectUIOption& uiOption
			, const Args&... args
		);
	};
}

#include "ReflectPropertyBinder.hpp"