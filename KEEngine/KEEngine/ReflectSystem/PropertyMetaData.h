#pragma once
#include "ReflectProperty.h"
#include "DynamicBuffer.h"

namespace ke
{
	template<typename ObjectType>
	class IPropertyMetaData
	{
	public:
		virtual IReflectProperty*	getFromObject(ObjectType* reflectObject) = 0;
		virtual void				applyDefaultValue(IReflectProperty* reflection) = 0;
		virtual const void*			getDefaultValue() const = 0;
	};

	template<typename ObjectType, typename PropertyType>
	class PropertyMetaData : public IPropertyMetaData<ObjectType>
	{
		using Getter = IReflectProperty* (ObjectType::*)();

	public:
		PropertyMetaData(const PropertyType& defaultValue, Getter getter);
		virtual ~PropertyMetaData() = default;

	public:
		virtual IReflectProperty*	getFromObject(ObjectType* reflectObject) override;
		virtual void				applyDefaultValue(IReflectProperty* reflection) override;
		virtual const void*			getDefaultValue() const override;

	public:

	protected:
		DynamicBuffer _defaultValueBuffer;

	protected:
		Getter _getter;
	};
};
#include "PropertyMetaData.hpp"