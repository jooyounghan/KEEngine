#pragma once
#include "IReflectProperty.h"
#include "IReflectEnumProperty.h"
#include <vector>

namespace ke
{
	template<typename ObjectType, typename EnumType>
	class ReflectEnumProperty : public IReflectEnumProperty, public ReflectPropertyBase<ObjectType, EnumType>
	{
	public:
		ReflectEnumProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, EnumType> getter
			, ConstGetter<ObjectType, EnumType> constGetter
			, Setter<ObjectType, EnumType> setter
		);
		~ReflectEnumProperty() override = default;

	public:
		// New type system
		inline virtual EReflectPropertyType getPropertyType() const override { return EReflectPropertyType::Enum; }

	public:
		// Legacy compatibility
		inline virtual bool isReflectObject() const override { return false; };
		inline virtual IReflectObject* getReflectObject(IReflectObject* parentReflectObject) override { return nullptr; }
		inline virtual const IReflectObject* getReflectObject(const IReflectObject* parentReflectObject) const override { return nullptr; }

	public:
		// Legacy compatibility
		inline virtual bool isPODProperty() const override { return false; }
		inline virtual IReflectPODProperty* getPODProperty() override { return nullptr; }
		inline virtual const IReflectPODProperty* getPODProperty() const override { return nullptr; };

	public:
		// IReflectEnumProperty implementation
		virtual int64 getEnumValue(const IReflectObject* object) const override;
		virtual void setEnumValue(IReflectObject* object, int64 value) override;
		virtual const char* getEnumName(int64 value) const override;
		virtual const std::vector<int64>& getAllEnumValues() const override;
		virtual const std::vector<const char*>& getAllEnumNames() const override;

	public:
		// Helper methods to register enum values
		void registerEnumValue(const char* name, int64 value);

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src) override;
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const override;
		virtual void setFromString(IReflectObject* object, const char* src, size_t strlen) override;
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const override;

	private:
		std::vector<int64> _enumValues;
		std::vector<const char*> _enumNames;
	};
}
#include "ReflectEnumProperty.hpp"
