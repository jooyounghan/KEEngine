#pragma once
#include "IReflectProperty.h"

namespace ke
{
	class IReflectEnumProperty
	{
	//public:
	//	virtual ~IReflectEnumProperty() = default;

	//public:
	//	// Get enum value as integer
	//	virtual int64 getEnumValue(const IReflectObject* object) const = 0;
	//	virtual void setEnumValue(IReflectObject* object, int64 value) = 0;

	//	// Get enum name from value
	//	virtual const char* getEnumName(int64 value) const = 0;

	//	// Get all possible enum values
	//	virtual const std::vector<int64>& getAllEnumValues() const = 0;
	//	virtual const std::vector<const char*>& getAllEnumNames() const = 0;
	};

	template<typename ObjectType, typename EnumType>
	class ReflectEnumProperty : public IReflectEnumProperty, public ReflectPropertyBase<ObjectType, EnumType>
	{
	//public:
	//	ReflectEnumProperty(
	//		const FlyweightStringA& name
	//		, Getter<ObjectType, EnumType> getter
	//		, ConstGetter<ObjectType, EnumType> constGetter
	//		, Setter<ObjectType, EnumType> setter
	//	);
	//	~ReflectEnumProperty() override = default;

	//public:
	//	// New type system
	//	inline virtual EReflectPropertyType getPropertyType() const override { return EReflectPropertyType::Enum; }

	//protected:
	//	// Override helper methods for type-safe conversion
	//	inline virtual IReflectEnumProperty* asIReflectEnumProperty() override { return this; }
	//	inline virtual const IReflectEnumProperty* asIReflectEnumProperty() const override { return this; }

	//public:
	//	// IReflectEnumProperty implementation
	//	virtual int64 getEnumValue(const IReflectObject* object) const override;
	//	virtual void setEnumValue(IReflectObject* object, int64 value) override;
	//	virtual const char* getEnumName(int64 value) const override;
	//	virtual const std::vector<int64>& getAllEnumValues() const override;
	//	virtual const std::vector<const char*>& getAllEnumNames() const override;

	//public:
	//	// Helper methods to register enum values
	//	void registerEnumValue(const char* name, int64 value);

	//public:
	//	virtual void setFromBianry(IReflectObject* object, const void* src) override;
	//	virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const override;
	//	virtual void setFromString(IReflectObject* object, const char* src, size_t strlen) override;
	//	virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const override;

	//private:
	//	std::vector<int64> _enumValues;
	//	std::vector<const char*> _enumNames;
	};
}
#include "ReflectEnumProperty.hpp"
