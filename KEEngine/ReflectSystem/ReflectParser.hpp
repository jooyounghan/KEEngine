#pragma once
#include "ReflectParser.h"
#include "StringConvertor.h"

#define DECLARE_REFLECT_PARSER(PropertyType)												\
    template<> int32 ReflectParser<int32>::ParseFromString(const char* src);				\
	template<> OwnedStringA ReflectParser<int32>::ParseToString(const int32& property);		\
	template<> int32 ReflectParser<int32>::ParseFromBinary(const void* src);				\
	template<> void ReflectParser<int32>::ParseToBinary(const int32& property, StaticBuffer<KEConstant::kPropertyBinaryBufferSize>& outBuffer);

namespace ke
{
	template<typename PropertyType>
	PropertyType ReflectParser<PropertyType>::ParseFromString(const char* src)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser<T>::ParserFromString)."); return  PropertyType();
	}

	template<typename PropertyType>
	OwnedStringA ReflectParser<PropertyType>::ParseToString(const PropertyType& property)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser<T>::ParseToString)."); return OwnedStringA();
	}

	template<typename PropertyType>
	PropertyType ReflectParser<PropertyType>::ParseFromBinary(const void* src)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser<T>::ParseFromBinary)."); return PropertyType();
	}

	template<typename PropertyType>
	void ReflectParser<PropertyType>::ParseToBinary(const PropertyType& property, StaticBuffer<KEConstant::kPropertyBinaryBufferSize>& outBuffer)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser<T>::ParseToBinary)."); return;
	}

	DECLARE_REFLECT_PARSER(bool);
	DECLARE_REFLECT_PARSER(uint8);
	DECLARE_REFLECT_PARSER(uint16);
	DECLARE_REFLECT_PARSER(uint32);
	DECLARE_REFLECT_PARSER(uint64);
	DECLARE_REFLECT_PARSER(int8);
	DECLARE_REFLECT_PARSER(int16);
	DECLARE_REFLECT_PARSER(int32);
	DECLARE_REFLECT_PARSER(int64);
	DECLARE_REFLECT_PARSER(float);
	DECLARE_REFLECT_PARSER(double);

	template<typename PropertyType>
	size_t ReflectParser2::parseFromString(const char* src, PropertyType& outPropertyTypes)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser::ParserFromString).");
	}
	template<typename PropertyType, typename ...PropertyTypes>
	size_t ReflectParser2::parseFromString(const char* src, PropertyType& outPropertyType, PropertyTypes & ...outPropertyTypes)
	{
		return parseFromString(src + parseFromString(src, outPropertyType) + 1, outPropertyTypes...);
	}
	template<typename PropertyType>
	void ReflectParser2::ParseToString(StaticBuffer<KEConstant::kStringConvertorBufferSize>& outStringBuffer, const PropertyType& property)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser::ParseToString).");
	}
	template<typename PropertyType, typename ...PropertyTypes>
	void ReflectParser2::ParseToString(StaticBuffer<KEConstant::kStringConvertorBufferSize>& outStringBuffer, const PropertyType& propertyType, const PropertyTypes& ...propertyTypes)
	{
		ParseToString(outStringBuffer, propertyType);
		ParseToString(outStringBuffer, propertyTypes...);
	}

	template<> BufferOffset ReflectParser2::parseFromString(const char* src, int32& outPropertyTypes);
	template<> void ReflectParser2::ParseToString(StaticBuffer<KEConstant::kStringConvertorBufferSize>& outStringBuffer, const int32& outPropertyTypes);
}