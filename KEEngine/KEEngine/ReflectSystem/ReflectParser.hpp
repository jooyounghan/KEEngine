#pragma once

#define DECLARE_PARSE_SPECIALIZATION(Type)																\
template<> void ReflectParser::parseFromString(const char* src, size_t strlen, Type* outPropertyTypes);	\
template<> void ReflectParser::parseToString(IBuffer* outStringBuffer, const Type* outPropertyTypes);	\
template<> Offset ReflectParser::parseFromBinary(const void* src, Type* outPropertyTypes);				\
template<> void ReflectParser::parseToBinary(IBuffer* outStringBuffer, const Type* outPropertyTypes);	

namespace ke
{
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