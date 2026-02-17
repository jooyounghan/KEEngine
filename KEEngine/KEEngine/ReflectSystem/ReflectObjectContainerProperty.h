#pragma once
#include "IReflectObjectContainerProperty.h"
#include "ReflectPropertyAccessor.h"

namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	class ReflectObjectContainerProperty : public IReflectObjectContainerProperty, public ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>
	{
	public:
		ReflectObjectContainerProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
		);

	public:
		virtual size_t	getSize(const IReflectObject* parentReflectObject) const override;

	public:
		virtual IReflectObject*			getReflectObject(const size_t index, IReflectObject* parentReflectObject) override;
		virtual const IReflectObject*	getReflectObject(const size_t index, const IReflectObject* parentReflectObject) const override;
	};
}
#include "ReflectObjectContainerProperty.hpp"