#pragma once
#include "ReflectProperty.h"
#include "StringConvertor.h"

namespace ke
{
	template<typename PropertyType>
	ReflectProperty<PropertyType>::ReflectProperty(const char* str, const PropertyType& propertyType)
		: IReflectProperty(str)
	{
		setReflectProperty(propertyType);
	}

	template<typename PropertyType>
	ReflectProperty<PropertyType>::ReflectProperty(const char* str, PropertyType&& propertyType)
		: IReflectProperty(str)
	{
		setReflectProperty(move(propertyType));
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::setFromString(const char* src) 
	{ 
		_property = move(ReflectParser<PropertyType>::ParseFromString(src)); 
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::setFromBinary(void const* src) 
	{
		_property = move(ReflectParser<PropertyType>::ParseFromBinary(src));
	}
	
	template<typename PropertyType>
	OwnedStringA ReflectProperty<PropertyType>::getToString() const
	{ 
		return ReflectParser<PropertyType>::ParseToString(_property);
	}
	
	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToBinary(StaticBuffer<KEConstant::kPropertyBinaryBufferSize>& outBuffer) const
	{ 
		ReflectParser<PropertyType>::ParseToBinary(_property, outBuffer);
	}

	template<typename PropertyType>
	RangedReflectProperty<PropertyType>::RangedReflectProperty(const char* str, const PropertyType& maxPropertyType, const PropertyType& minPropertyType)
		: IReflectProperty(str)
	{
		setMaxReflectProperty(maxPropertyType);
		setMinReflectProperty(minPropertyType);
	}

	template<typename PropertyType>
	RangedReflectProperty<PropertyType>::RangedReflectProperty(const char* str, PropertyType&& maxPropertyType, PropertyType&& minPropertyType)
		: IReflectProperty(str)
	{
		setMaxReflectProperty(move(maxPropertyType));
		setMinReflectProperty(move(minPropertyType));
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::setFromString(const char* src)
	{
		//_property = move(ReflectParser<PropertyType>::ParseFromString(src));
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::setFromBinary(void const* src)
	{
		//_property = move(ReflectParser<PropertyType>::ParseFromBinary(src));
	}

	template<typename PropertyType>
	OwnedStringA RangedReflectProperty<PropertyType>::getToString() const
	{
		return OwnedStringA(""); //ReflectParser<PropertyType>::ParseToString(_property);
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::getToBinary(StaticBuffer<KEConstant::kPropertyBinaryBufferSize>& outBuffer) const
	{
		//ReflectParser<PropertyType>::ParseToBinary(_property, outBuffer);
	}
}