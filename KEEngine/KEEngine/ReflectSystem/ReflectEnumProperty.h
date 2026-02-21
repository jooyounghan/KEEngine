#pragma once
#include "IReflectPODProperty.h"
#include "ReflectPropertyAccessor.h"
#include "EnumUtil.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectEnumProperty : public IReflectPODProperty, public ReflectPODPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, PropertyType>
	{
	public:
		ReflectEnumProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);
		~ReflectEnumProperty() override = default;

	protected:
		virtual const void* getTypeId() const;

	public:
		virtual void fromBianry(IReflectObject* object, const void* src) override;
		virtual void toBinary(const IReflectObject* object, IBuffer* outDst) const override;
		virtual void fromString(IReflectObject* object, const char* src, size_t strLen) override;
		virtual void toString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectEnumProperty.hpp"