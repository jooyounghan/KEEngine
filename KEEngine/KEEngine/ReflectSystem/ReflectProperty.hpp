#include "IDefaultableReflectProperty.h"
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
		ReflectParser::parseFromBinary(src, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToBinary(const IReflectObject* object, IBuffer* outDst) const
	{
		ReflectParser::parseToBinary(outDst, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src)
	{
		ReflectParser::parseFromString(src, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		ReflectParser::parseToString(outStringBuffer, &this->get(object));
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

#define ERROR_REFLECT_OBJECT_METHOD_NOT_ALLOWED(methodName, description) \
    KE_ASSERT(false, "ReflectObjectProperty::" #methodName               \
                     " is not allowed. (" #description ")")

#define ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(methodName) \
	ERROR_REFLECT_OBJECT_METHOD_NOT_ALLOWED(methodName, "Serialize/Deserialize is not allowed for ReflectObjectProperty.")

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::setFromBianry(IReflectObject* object, const void* src)
	{
		ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(setFromBianry);
	}
	
	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::getToBinary(const IReflectObject* object, IBuffer* outDst) const
	{
		ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(getToBinary);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src)
	{
		ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(setFromString);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(getToString);
	}
}