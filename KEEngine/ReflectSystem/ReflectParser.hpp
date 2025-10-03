#pragma once
#include "ReflectParser.h"
#include "TemplateCommon.h"

#define DECLARE_PARSE_SPECIALIZATION(Type)																	\
template<> KEBufferOffset ReflectParser::parseFromString(const char* src, Type& outPropertyTypes);			\
template<> void ReflectParser::parseToString(IStaticBuffer* outStringBuffer, const Type& outPropertyTypes);	\
template<> KEBufferOffset ReflectParser::parseFromBinary(const void* src, Type& outPropertyTypes);			\
template<> void ReflectParser::parseToBinary(IStaticBuffer* outStringBuffer, const Type& outPropertyTypes);	

namespace ke
{
	template<typename PropertyType>
	KEBufferOffset ReflectParser::parseFromString(const char* src, PropertyType& outPropertyTypes)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}
	template<typename PropertyType, typename ...PropertyTypes>
	KEBufferOffset ReflectParser::parseFromString(const char* src, PropertyType& outPropertyType, PropertyTypes & ...outPropertyTypes)
	{
		return parseFromString(src + parseFromString(src, outPropertyType) + 1, outPropertyTypes...);
	}
	template<typename PropertyType>
	void ReflectParser::parseToString(IStaticBuffer* outStringBuffer, const PropertyType& property)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}
	template<typename PropertyType, typename ...PropertyTypes>
	void ReflectParser::parseToString(IStaticBuffer* outStringBuffer, const PropertyType& propertyType, const PropertyTypes& ...propertyTypes)
	{
		parseToString(outStringBuffer, propertyType);
		outStringBuffer->writeOne(',');
		parseToString(outStringBuffer, propertyTypes...);
	}

	template<typename PropertyType>
	KEBufferOffset ReflectParser::parseFromBinary(const void* src, PropertyType& outPropertyTypes)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType, typename ...PropertyTypes>
	KEBufferOffset ReflectParser::parseFromBinary(const void* src, PropertyType& outPropertyType, PropertyTypes & ...outPropertyTypes)
	{
		return parseFromBinary(static_cast<const uint8*>(src) + parseFromBinary(src, outPropertyType), outPropertyTypes...);
	}

	template<typename PropertyType>
	void ReflectParser::parseToBinary(IStaticBuffer* outBuffer, const PropertyType& property)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType, typename ...PropertyTypes>
	void ReflectParser::parseToBinary(IStaticBuffer* outStringBuffer, const PropertyType& propertyType, const PropertyTypes & ...propertyTypes)
	{
		parseToBinary(outStringBuffer, propertyType);
		parseToBinary(outStringBuffer, propertyTypes...);
	}

#pragma region Parse Specializations
	DECLARE_PARSE_SPECIALIZATION(bool);
	DECLARE_PARSE_SPECIALIZATION(uint8);
	DECLARE_PARSE_SPECIALIZATION(uint16);
	DECLARE_PARSE_SPECIALIZATION(uint32);
	DECLARE_PARSE_SPECIALIZATION(uint64);
	DECLARE_PARSE_SPECIALIZATION(int8);
	DECLARE_PARSE_SPECIALIZATION(int16);
	DECLARE_PARSE_SPECIALIZATION(int32);
	DECLARE_PARSE_SPECIALIZATION(int64);
	DECLARE_PARSE_SPECIALIZATION(float);
	DECLARE_PARSE_SPECIALIZATION(double);
#pragma endregion
}