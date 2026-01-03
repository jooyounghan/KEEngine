#pragma once
#include "ReflectProperty.h"
#include "DynamicBuffer.h"

namespace ke
{
	template<typename ObjectType>
	class IPropertyMetaData
	{
	public:
		virtual ~IPropertyMetaData() = default;

	public:
		virtual void				applyDefaultValue(IReflectProperty* reflection) = 0;
	};

	template<typename ObjectType, typename PropertyType>
	class PropertyMetaData : public IPropertyMetaData<ObjectType>
	{
	public:
		PropertyMetaData(const PropertyType& defaultValue);
		~PropertyMetaData() override = default;

	public:
		virtual void applyDefaultValue(IReflectProperty* reflection) override;

	protected:
		DynamicBuffer _defaultValueBuffer;
	};
};
#include "PropertyMetaData.hpp"