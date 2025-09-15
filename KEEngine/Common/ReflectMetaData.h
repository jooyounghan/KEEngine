#pragma once
#include "HashMap.h"
#include "ReflectProperty.h"

#define DECLARE_REFLECT_PROPERTY(PropertyType, PropertyName) ;
#define DEFINE_REFLECT_PROPERTY(PropertyType, PropertyName) ;

namespace ke
{
	enum class EPropertyType : uint8
	{
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
		Boolean,
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

	};

	class ReflectMetaData
	{
	public:
	};
}

