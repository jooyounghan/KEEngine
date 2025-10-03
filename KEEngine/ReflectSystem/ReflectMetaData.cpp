#include "ReflectMetaData.h"

#define DEFINE_PROPERTY_TYPE_CONVERTOR(Type, PropertyType)		\
template<>														\
EPropertyType PropertyTypeConvertor<Type>::GetType() const		\
{																\
	return PropertyType;										\
}

namespace ke
{
	DEFINE_ENUM_DESCRIPTOR(
		EPropertyType,
		None,
		Boolean,
		Int8,
		Int16,
		Int32,
		Int64,
		UInt8,
		UInt16,
		UInt32,
		UInt64,
		Float,
		Double,
		String,
		Count
	);

	DEFINE_ENUM_DESCRIPTOR(
		EPropertyFlag,
		None,
		ReadOnly,
		WriteOnly,
		ReadWrite
	);

	DEFINE_PROPERTY_TYPE_CONVERTOR(bool, EPropertyType::Boolean);
	DEFINE_PROPERTY_TYPE_CONVERTOR(int8, EPropertyType::Int8);
	DEFINE_PROPERTY_TYPE_CONVERTOR(int16, EPropertyType::Int16);
	DEFINE_PROPERTY_TYPE_CONVERTOR(int32, EPropertyType::Int32);
	DEFINE_PROPERTY_TYPE_CONVERTOR(int64, EPropertyType::Int64);
	DEFINE_PROPERTY_TYPE_CONVERTOR(uint8, EPropertyType::UInt8);
	DEFINE_PROPERTY_TYPE_CONVERTOR(uint16, EPropertyType::UInt16);
	DEFINE_PROPERTY_TYPE_CONVERTOR(uint32, EPropertyType::UInt32);
	DEFINE_PROPERTY_TYPE_CONVERTOR(uint64, EPropertyType::UInt64);
	DEFINE_PROPERTY_TYPE_CONVERTOR(float, EPropertyType::Float);
	DEFINE_PROPERTY_TYPE_CONVERTOR(double, EPropertyType::Double);		

	void ReflectMetaData::registerProperty(EPropertyType type, IReflectProperty* property)
	{
		const FlyweightStringA& propertyName = property->getPropertName();
		if (_propertyMetaDataMap.find(propertyName) == nullptr)
		{
			SPropertyMetaData metaData;
			metaData._propertyType = type;
			property->getToBinary(&metaData._defaultValueBuffer);

			_propertyMetaDataMap.insert(propertyName, metaData);			
		}
	}

	//const SPropertyMetaData* ReflectMetaData::findProperty(const char* propertyName) const
	//{
	//	return nullptr;
	//}

	void ReflectMetaData::setDefaultValue(IReflectProperty* property) const
	{
		const FlyweightStringA& propertyName = property->getPropertName();
		SPropertyMetaData* metaData = _propertyMetaDataMap.find(propertyName);
		if (metaData != nullptr)
		{
			property->setFromBinary(metaData->_defaultValueBuffer.getBuffer());
		}
	}
}
