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
		ReflectParser::parseFromString(src, _property);
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::setFromBinary(void const* src) 
	{
		ReflectParser::parseFromBinary(src, _property);
	}
	
	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToString(IStaticBuffer* outBuffer) const
	{ 
		ReflectParser::parseToString(outBuffer, _property);
	}
	
	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToBinary(IStaticBuffer* outBuffer) const
	{ 
		ReflectParser::parseToBinary(outBuffer, _property);
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
		ReflectParser::parseFromString(src, _minProperty, _maxProperty);
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::setFromBinary(void const* src)
	{
		ReflectParser::parseFromBinary(src, _minProperty, _maxProperty);
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::getToString(IStaticBuffer* outBuffer) const
	{
		ReflectParser::parseToString(outBuffer, _minProperty, _maxProperty);
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::getToBinary(IStaticBuffer* outBuffer) const
	{
		ReflectParser::parseToBinary(outBuffer, _minProperty, _maxProperty);
	}
}