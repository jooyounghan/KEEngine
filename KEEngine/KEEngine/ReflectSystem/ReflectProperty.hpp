#pragma once
#include "ReflectProperty.h"
#include "ReflectParser.h"

namespace ke
{
	IReflectProperty::IReflectProperty(const char* str) : _propertyName(str) {}

	template<typename PropertyType>
	ReflectProperty<PropertyType>::ReflectProperty(const char* str)
		: IReflectProperty(str)
	{
	}

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
		OnPropertyChanged();
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::setFromBinary(void const* src)
	{
		ReflectParser::parseFromBinary(src, _property);
		OnPropertyChanged();
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToString(IBuffer* outBuffer) const
	{
		ReflectParser::parseToString(outBuffer, _property);
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToBinary(IBuffer* outBuffer) const
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
		OnPropertyChanged();
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::setFromBinary(void const* src)
	{
		ReflectParser::parseFromBinary(src, _minProperty, _maxProperty);
		OnPropertyChanged();
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::getToString(IBuffer* outBuffer) const
	{
		ReflectParser::parseToString(outBuffer, _minProperty, _maxProperty);
	}

	template<typename PropertyType>
	void RangedReflectProperty<PropertyType>::getToBinary(IBuffer* outBuffer) const
	{
		ReflectParser::parseToBinary(outBuffer, _minProperty, _maxProperty);
	}
}