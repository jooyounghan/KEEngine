#pragma once
#include "IReflectProperty.h"
#include "ReflectPropertyInfo.h"
#include "ReflectPropertyAccessor.h"
#include "EnumUtil.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectEnumProperty : public IReflectProperty, public IReflectPropertyInfoAccessor, public ReflectPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, PropertyType>
	{
	public:
		ReflectEnumProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);
		~ReflectEnumProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::POD; }

	protected:
		virtual void* getPropertyInfoPtr() override { return static_cast<ReflectPropertyInfo<PropertyType>*>(this); }
		virtual const void* getPropertyInfoPtr() const override { return static_cast<const ReflectPropertyInfo<PropertyType>*>(this); }

	public:
		inline virtual IReflectPropertyInfoAccessor*		getPropertyInfoAccessor() override { return static_cast<IReflectPropertyInfoAccessor*>(this); }
		inline virtual const IReflectPropertyInfoAccessor*	getPropertyInfoAccessor() const override { return static_cast<const IReflectPropertyInfoAccessor*>(this); }

	public:
		virtual void fromBianry(IReflectObject* object, const void* src) override;
		virtual void toBinary(const IReflectObject* object, IBuffer* outDst) const override;
		virtual void fromString(IReflectObject* object, const char* src, size_t strLen) override;
		virtual void toString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectEnumProperty.hpp"