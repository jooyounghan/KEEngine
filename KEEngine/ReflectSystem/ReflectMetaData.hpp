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
	void ReflectMetaData<ObjectType>::registerProperty(const FlyweightStringA& propertyName, PropertyMetaData<ObjectType> propertyMetaData)
	{
		HashBucketFindResult<FlyweightStringA, PropertyMetaData<ObjectType>> findResult = _propertyMetaDataMap.find(propertyName);
		KE_DEBUG_ASSERT(findResult._keyPtr == nullptr, "Property already registered in ReflectMetaData.");
		if (findResult._keyPtr == nullptr)
		{
			_propertyMetaDataMap.insert(propertyName, propertyMetaData);
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
		PropertyMetaData<ObjectType>* metaData = _propertyMetaDataMap.find(propertyName);
		if (metaData != nullptr)
		{
			property->setFromBinary(metaData->_defaultValueBuffer.getBuffer());
		}
	}
}