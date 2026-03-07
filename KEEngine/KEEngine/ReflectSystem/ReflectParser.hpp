#include "ReflectParser.h"
#pragma once

#define DECLARE_PARSE_SPECIALIZATION(Type)																\
template<> void ReflectParser::parseFromString(const char* src, size_t strlen, Type* outPropertyTypes);	\
template<> void ReflectParser::parseToString(IBuffer* outStringBuffer, const Type* outPropertyTypes);	\
template<> Offset ReflectParser::parseFromBinary(const void* src, Type* outPropertyTypes);				\
template<> void ReflectParser::parseToBinary(IBuffer* outStringBuffer, const Type* outPropertyTypes);	

namespace ke
{
	template<typename PropertyType>
	void ReflectParser::fromString(const char* src, size_t strlen, PropertyType* property)
	{
		if (property == nullptr)
		{
			KE_ASSERT_DEV(false, "인자로 들어오는 property가 nullptr입니다.");
			return;
		}

		if constexpr (std::is_enum_v<PropertyType>)
		{
			std::optional<PropertyType> optVal = EnumWrapper<PropertyType>::fromString(std::string_view(src, strlen));
			if (optVal.has_value())
			{
				*property = optVal.value();
			}
		}
		else
		{
			ReflectParser::parseFromString(src, strlen, property);
		}
	}

	template<typename PropertyType>
	void ReflectParser::toString(IBuffer* dstBuffer, const PropertyType* property)
	{
		if (property == nullptr)
		{
			KE_ASSERT_DEV(false, "인자로 들어오는 property가 nullptr입니다.");
			return;
		}

		if constexpr (std::is_enum_v<PropertyType>)
		{
			const std::string& enumString = EnumWrapper<PropertyType>::toString(*property);
			dstBuffer->write(enumString.c_str(), enumString.length());
		}
		else
		{
			ReflectParser::parseToString(dstBuffer, &property);
		}
	}

	template<typename PropertyType>
	void ReflectParser::parseFromString(const char* src, size_t strlen, PropertyType* outPropertyTypes)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType>
	void ReflectParser::parseToString(IBuffer* outStringBuffer, const PropertyType* property)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType>
	Offset ReflectParser::parseFromBinary(const void* src, PropertyType* outPropertyTypes)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType>
	void ReflectParser::parseToBinary(IBuffer* outBuffer, const PropertyType* property)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
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

	DECLARE_PARSE_SPECIALIZATION(std::string);

	template<typename T> class FlyweightString;
	DECLARE_PARSE_SPECIALIZATION(FlyweightString<char>);
#pragma endregion
}