#include "ReflectMetaData.h"
#include "TemplateCommon.h"
#include "AssertManager.h"

#define DECLARE_PROPERTY_TYPE_CONVERTOR(Type)			\
template<>												\
EPropertyType PropertyTypeConvertor<Type>::GetType();

#define DEFINE_PROPERTY_TYPE_CONVERTOR(Type, PropertyType)		\
template<>														\
EPropertyType PropertyTypeConvertor<Type>::GetType()			\
{																\
	return PropertyType;										\
}

namespace ke
{
	template<typename Type>
	EPropertyType PropertyTypeConvertor<Type>::GetType()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(PropertyTypeGetter);
	};

	DECLARE_PROPERTY_TYPE_CONVERTOR(bool);
	DECLARE_PROPERTY_TYPE_CONVERTOR(int8);
	DECLARE_PROPERTY_TYPE_CONVERTOR(int16);
	DECLARE_PROPERTY_TYPE_CONVERTOR(int32);
	DECLARE_PROPERTY_TYPE_CONVERTOR(int64);
	DECLARE_PROPERTY_TYPE_CONVERTOR(uint8);
	DECLARE_PROPERTY_TYPE_CONVERTOR(uint16);
	DECLARE_PROPERTY_TYPE_CONVERTOR(uint32);
	DECLARE_PROPERTY_TYPE_CONVERTOR(uint64);
	DECLARE_PROPERTY_TYPE_CONVERTOR(float);
	DECLARE_PROPERTY_TYPE_CONVERTOR(double);

	template<typename ObjectType>
	IPropertyMetaData<ObjectType>::IPropertyMetaData(EPropertyType propertyType, EPropertyFlag propertyFlag)
		: _propertyType(propertyType)
		, _propertyFlag(propertyFlag)
	{
	}

	template<typename ObjectType, typename PropertyType>
	PropertyMetaData<ObjectType, PropertyType>::PropertyMetaData(
		EPropertyFlag propertyFlag,
		const PropertyType& defaultPropertyValue, 
		Getter getter, 
		Setter setter
	) : IPropertyMetaData<ObjectType>(PropertyTypeConvertor<PropertyType>::GetType(), propertyFlag)
		, _getter(getter)
		, _setter(setter)
	{
		ReflectParser::parseToBinary(&__super::_defaultValueBuffer, defaultPropertyValue);
	}

	template<typename ObjectType, typename PropertyType>
	const void* PropertyMetaData<ObjectType, PropertyType>::getPropertyFromObject(ObjectType* reflectObject) const
	{
		const PropertyType& ref = (reflectObject->*(_getter))();
		return static_cast<const void*>(&ref);
	}
	
	template<typename ObjectType, typename PropertyType>
	void PropertyMetaData<ObjectType, PropertyType>::setPropertyFromObject(ObjectType* reflectObject, const void* value)
	{
		const PropertyType* propertyPtr = static_cast<const PropertyType*>(value);
		(reflectObject->*(_setter))(*propertyPtr);
	}

	template<typename ObjectType>
	template<typename PropertyType, typename ...Args>
	void ReflectMetaData<ObjectType>::registerProperty(const FlyweightStringA& propertyName, Args... args)
	{
		HashBucketFindResult<FlyweightStringA, uint32> findResult = _propertyMetaDataIndexMap.find(propertyName);
		KE_DEBUG_ASSERT(findResult._keyPtr == nullptr, "Property already registered in ReflectMetaData.");
		if (findResult._keyPtr == nullptr)
		{
			_propertyMetaDataList.pushBack(new PropertyMetaData<ObjectType, PropertyType>(args...));
			uint32 propertyIndex = static_cast<uint32>(_propertyMetaDataList.size() - 1);
			_propertyMetaDataIndexMap.insert(propertyName, propertyIndex);
		}

	}

	//const SPropertyMetaData* ReflectMetaData::findProperty(const char* propertyName) const
	//{
	//	return nullptr;
	//}

	template<typename ObjectType>
	void ReflectMetaData<ObjectType>::setDefaultValue(IReflectProperty* property) const
	{
		const FlyweightStringA& propertyName = property->getPropertName();
		HashBucketFindResult<FlyweightStringA, uint32> findResult = _propertyMetaDataIndexMap.find(propertyName);
		if (findResult._keyPtr != nullptr)
		{
			const uint32& propertyIndex = *findResult._valuePtr;
			property->setFromBinary(_propertyMetaDataList[propertyIndex]->getDefaultValueBuffer());
		}
	}
}