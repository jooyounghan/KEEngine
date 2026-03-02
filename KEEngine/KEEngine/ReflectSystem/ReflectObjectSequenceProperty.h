#pragma once
#include "IReflectObjectSequenceProperty.h"
#include "ReflectPropertyAccessor.h"

namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	class ReflectObjectSequenceProperty : public IReflectObjectSequenceProperty, public ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>
	{
	public:
		ReflectObjectSequenceProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
		);

	public:
		virtual size_t	size(const IReflectObject* object) const override;
		virtual void	resize(IReflectObject* object, size_t newSize) override;

	public:
		virtual IReflectObject*			getReflectObject(const size_t index, IReflectObject* object) override;
		virtual const IReflectObject*	getReflectObject(const size_t index, const IReflectObject* object) const override;
	};
}
#include "ReflectObjectSequenceProperty.hpp"