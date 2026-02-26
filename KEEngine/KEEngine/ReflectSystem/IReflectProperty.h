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

	class IBuffer;
	class IReflectObject;
	class IReflectPropertyInfoAccessor;
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

	protected:
		inline virtual void* getInterface() { return nullptr; }
		inline virtual const void* getInterface() const { return nullptr; }

	public:
		const FlyweightStringA& getName() const { return _name; }
		const EReflectUIOption	getUIOption() const { return _uiOption; }
		void					setUIOption(const EReflectUIOption& uiOption) { _uiOption = uiOption; }

	public:
		inline virtual IReflectPropertyInfoAccessor*		getPropertyInfoAccessor() { return nullptr; }
		inline virtual const IReflectPropertyInfoAccessor*	getPropertyInfoAccessor() const { return nullptr; }

	public:
		virtual void fromBianry(IReflectObject* object, const void* src) {}
		virtual void toBinary(const IReflectObject* object, IBuffer* outDst) const {}
		virtual void fromString(IReflectObject* object, const char* src, size_t strLen) {}
		virtual void toString(const IReflectObject* object, IBuffer* outStringBuffer) const {}

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