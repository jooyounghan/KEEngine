#pragma once
#include "HashMap.h"
#include "ReflectProperty.h"

#define DECLARE_REFLECT_PROPERTY(PropertyType, PropertyName) ;
#define DEFINE_REFLECT_PROPERTY(PropertyType, PropertyName) ;

namespace ke
{
	enum class EPropertyType : uint8
	{
		None = 0,
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
	};

	enum class EPropertyFlag : uint8
	{
		None = 0,
		ReadOnly = 1 << 0,
		WriteOnly = 1 << 1,
		ReadWrite = ReadOnly | WriteOnly
	};

	struct SPropertyMetaData
	{
		FlyweightStringA						_propertyName;
		EPropertyType							_propertyType = EPropertyType::None;
		StaticBuffer<kPropertyBinaryBufferSize> _defaultValueBuffer;
	};

	class ReflectMetaData
	{
	public:
		Vector<SPropertyMetaData> _propertyMetaDatas;

	public:
		void registerProperty(EPropertyType type, IReflectProperty* property);
		const SPropertyMetaData* findProperty(const char* propertyName) const;
	
	public:
		void setDefaultValue(IReflectProperty* property) const;
	};
}

