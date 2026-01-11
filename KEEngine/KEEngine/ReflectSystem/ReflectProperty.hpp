#include "ReflectProperty.h"
namespace ke
{
	template<typename ObjectType, typename PropertyType>
	ReflectPropertyBase<ObjectType, PropertyType>::ReflectPropertyBase(
		const FlyweightStringA& name
		, Getter<ObjectType, PropertyType> getter
		, ConstGetter<ObjectType, PropertyType> constGetter
		, Setter<ObjectType, PropertyType> setter
	)
		: IReflectProperty(name)
		, _getter(getter)
		, _constGetter(constGetter)
		, _setter(setter)
	{
		STATIC_ASSERT_IS_BASE_OF(IReflectObject, ObjectType);
	}

	template<typename ObjectType, typename PropertyType>
	ReflectPODProperty<ObjectType, PropertyType>::ReflectPODProperty(
		const FlyweightStringA& name
		, Getter<ObjectType, PropertyType> getter
		, ConstGetter<ObjectType, PropertyType> constGetter
		, Setter<ObjectType, PropertyType> setter
	)
		: ReflectPropertyBase<ObjectType, PropertyType>(name, getter, constGetter, setter)
	{
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::setFromBianry(IReflectObject* object, const void* src)
	{
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToBinary(const IReflectObject* object, void* outDst) const
	{
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src)
	{
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
	}

	template<typename ObjectType, typename PropertyType>
	ReflectObjectProperty<ObjectType, PropertyType>::ReflectObjectProperty(
		const FlyweightStringA& name
		, Getter<ObjectType, PropertyType> getter
		, ConstGetter<ObjectType, PropertyType> constGetter
		, Setter<ObjectType, PropertyType> setter
	)
		: ReflectPropertyBase<ObjectType, PropertyType>(name, getter, constGetter, setter)
	{
		STATIC_ASSERT_IS_BASE_OF(IReflectObject, PropertyType);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::setFromBianry(IReflectObject* object, const void* src)
	{
		KE_ASSERT(false, "ReflectObjectProperty::setFromBianry is not allowed.");
	}
	
	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::getToBinary(const IReflectObject* object, void* outDst) const
	{
		KE_ASSERT(false, "ReflectObjectProperty::getToBinary is not allowed.");
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src)
	{
		KE_ASSERT(false, "ReflectObjectProperty::setFromString is not allowed.");
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		KE_ASSERT(false, "ReflectObjectProperty::getToString is not allowed.");
	}
}