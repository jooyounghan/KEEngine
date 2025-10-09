#pragma once
#include "HashMap.h"
#include "ReflectProperty.h"
#include "EnumMacro.h"

namespace ke
{
	DECLARE_ENUM_DESCRIPTOR(
		EPropertyType, 
		uint8,
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
	);
	
	DECLARE_ENUM_DESCRIPTOR(
		EPropertyFlag,
		uint8,
		None = 0,
		ReadOnly,
		WriteOnly,
		ReadWrite
	)

	template<typename Type>
	struct PropertyTypeConvertor
	{
		static EPropertyType GetType();
	};

	struct SPropertyMetaData
	{
		FlyweightStringA									_propertyName;
		StaticBuffer<KEConstant::kPropertyBinaryBufferSize> _defaultValueBuffer;
		EPropertyType										_propertyType = EPropertyType::None;
	};

	class ReflectMetaData
	{
	public:
		CompactBinHoodHashMap<FlyweightStringA, SPropertyMetaData> _propertyMetaDataMap;

	public:
		void registerProperty(EPropertyType type, IReflectProperty* property);
		//const SPropertyMetaData* findProperty(const char* propertyName) const;
	
	public:
		void setDefaultValue(IReflectProperty* property) const;
	};
}

#include "ReflectMetaData.hpp"