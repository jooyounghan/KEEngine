#pragma once
#include "ReflectProperty.h"
#include "StaticBuffer.h"

namespace ke
{
	DECLARE_ENUM_CLASS(
		EPropertyType,
		uint8,
		None,
		Boolean,
		Int8,
		Int16,
		Int32,
		Int64,
		UInt8,
		UInt16,
		UInt32,
		UInt64,
		Float,
		Double,
		String,
		Count
	);

	DECLARE_ENUM_CLASS(
		EPropertyFlag,
		uint8,
		None,
		ReadOnly,
		WriteOnly,
		ReadWrite
	);

	template<typename Type>
	struct PropertyTypeConvertor
	{
		static EPropertyType GetType();
	};

	template<typename ObjectType>
	class IPropertyMetaData
	{
		using PropertyGetter = const void* (*)(ObjectType* reflectObject);
		using PropertySetter = void (*)(ObjectType* reflectObject, const void* value);

		static constexpr size_t kDefaultValueBufferSize = 128;

	public:
		IPropertyMetaData(EPropertyType propertyType, EPropertyFlag propertyFlag);
		virtual ~IPropertyMetaData() = default;

	protected:
		EPropertyType							_propertyType = EPropertyType::None;
		EPropertyFlag							_propertyFlag = EPropertyFlag::None;
		StaticBuffer<kDefaultValueBufferSize>	_defaultValueBuffer;

	protected:
		EPropertyType getPropertyType() const { return _propertyType; };
		EPropertyFlag getPropertyFlag() const { return _propertyFlag; };

	public:
		void applyDefaultValue(IReflectProperty* reflectProperty);

	public:
		virtual const void* getPropertyFromObject(ObjectType* reflectObject) const = 0;
		virtual void		setPropertyFromObject(ObjectType* reflectObject, const void* value) = 0;
	};


	template<typename ObjectType, typename PropertyType>
	class PropertyMetaData : public IPropertyMetaData<ObjectType>
	{
		using Getter = const PropertyType& (ObjectType::*)() const;
		using Setter = void (ObjectType::*)(const PropertyType&);

	public:
		PropertyMetaData(
			EPropertyFlag propertyFlag,
			const PropertyType& defaultPropertyValue,
			Getter getter,
			Setter setter
		);
		virtual ~PropertyMetaData() override = default;

	protected:
		Getter _getter;
		Setter _setter;

	public:
		virtual const void* getPropertyFromObject(ObjectType* reflectObject) const override;
		virtual void		setPropertyFromObject(ObjectType* reflectObject, const void* value) override;
	};
}

#include "PropertyMetaData.hpp"