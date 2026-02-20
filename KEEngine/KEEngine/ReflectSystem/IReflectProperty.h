#pragma once
#include "FlyweightString.h"

namespace ke
{
	enum class EReflectUIOption : uint8
	{
		None,
		Visible = 1 << 0,
		Editable = 1 << 1
	};

	enum class EReflectPropertyType : uint8
	{
		POD,
		ReflectObject,
		PODContainer,
		ReflectObjectContainer,
		Count
	};

	class IReflectProperty;

	template<typename T>
	struct ReflectCastHelper
	{
		static T* cast(IReflectProperty* prop);
		static const T* cast(const IReflectProperty* prop);
	};

	class IReflectProperty
	{
	public:
		IReflectProperty(const FlyweightStringA& name);
		virtual ~IReflectProperty() = default;

		template<typename T> friend struct ReflectCastHelper;

	public:
		virtual EReflectPropertyType getType() const = 0;
		virtual bool isAttributeProperty() const { return false; }

	protected:
		inline virtual void* getInterface() { return nullptr; }
		inline virtual const void* getInterface() const { return nullptr; }

	public:
		const FlyweightStringA& getName() const { return _name; }
		const EReflectUIOption	getUIOption() const { return _uiOption; }
		void					setUIOption(const EReflectUIOption& uiOption) { _uiOption = uiOption; }

	public:
		template<typename T>
		T* castTo();
		template<typename T>
		const T* castTo() const;

	protected:
		FlyweightStringA _name;
		EReflectUIOption _uiOption = EReflectUIOption::None;
	};
}
#include "IReflectProperty.hpp"