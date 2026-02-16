#pragma once
#include "IReflectProperty.h"

namespace ke
{
	class IReflectEnumProperty
	{
	public:
		virtual ~IReflectEnumProperty() = default;

	public:
		// Get enum value as integer
		virtual int64 getEnumValue(const IReflectObject* object) const = 0;
		virtual void setEnumValue(IReflectObject* object, int64 value) = 0;
		
		// Get enum name from value
		virtual const char* getEnumName(int64 value) const = 0;
		
		// Get all possible enum values
		virtual const std::vector<int64>& getAllEnumValues() const = 0;
		virtual const std::vector<const char*>& getAllEnumNames() const = 0;
	};
}
