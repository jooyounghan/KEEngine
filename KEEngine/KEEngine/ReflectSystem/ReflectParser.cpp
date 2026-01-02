#include "ReflectSystemPch.h"
#include "ReflectParser.h"
#include "ReflectObject.h"
#include "StrUtil.h"

#define DEFINE_GET_PROPERTY_BUFFER_SIZE(Type)													\
template<>																						\
size_t ReflectParser::getPropertyBufferSize(const Type* outPropertyTypes)						\
{																								\
    return sizeof(Type);																		\
}

#define DEFINE_PARSE_FROM_STRING(Type, StringParser, ...)										\
template<>																						\
Offset ReflectParser::parseFromString(const char* src, Type* outPropertyTypes)					\
{																								\
    char* endPtr = nullptr;																		\
    *outPropertyTypes = static_cast<Type>(StringParser(src, &endPtr, ## __VA_ARGS__));			\
    return static_cast<size_t>(endPtr - src);													\
}

#define DEFINE_PARSE_TO_STRING(Type, ...)														\
template<>																						\
void ReflectParser::parseToString(IBuffer* outStringBuffer, const Type* property)				\
{																								\
	return StrUtil::convertToStringBuffer(outStringBuffer, *property, ## __VA_ARGS__);			\
}

#define DEFINE_PARSE_FROM_BINARY(Type)													\
template<>																				\
Offset ReflectParser::parseFromBinary(const void* src, Type* outPropertyTypes)			\
{																						\
	Offset offset = sizeof(Type);														\
	memcpy(&outPropertyTypes, src, offset);												\
	return offset;																		\
}

#define DEFINE_PARSE_TO_BINARY(Type)															\
template<>																						\
void ReflectParser::parseToBinary(IBuffer* outStringBuffer, const Type* outPropertyTypes)		\
{																								\
	outStringBuffer->write(&outPropertyTypes, sizeof(Type));									\
}

namespace ke
{
#pragma region getPropertyBufferSize Specializations
	DEFINE_GET_PROPERTY_BUFFER_SIZE(bool);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(uint8);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(uint16);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(uint32);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(uint64);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(int8);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(int16);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(int32);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(int64);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(float);
	DEFINE_GET_PROPERTY_BUFFER_SIZE(double);
#pragma endregion

#pragma region parseFromString Specializations
	template<>
	Offset ReflectParser::parseFromString(const char* src, bool* outPropertyTypes)
	{
		*outPropertyTypes = strcmp(src, "true") == 0;
		return outPropertyTypes ? 4 : 5;
	}

	DEFINE_PARSE_FROM_STRING(uint8, strtoull, 0);
	DEFINE_PARSE_FROM_STRING(uint16, strtoull, 0);
	DEFINE_PARSE_FROM_STRING(uint32, strtoull, 0);
	DEFINE_PARSE_FROM_STRING(uint64, strtoull, 0);
	DEFINE_PARSE_FROM_STRING(int8, strtoull, 0);
	DEFINE_PARSE_FROM_STRING(int16, strtoull, 0);
	DEFINE_PARSE_FROM_STRING(int32, strtoull, 0);
	DEFINE_PARSE_FROM_STRING(int64, strtoull, 0);
	DEFINE_PARSE_FROM_STRING(float, strtof);
	DEFINE_PARSE_FROM_STRING(double, strtod);
#pragma endregion

#pragma region ParseToString Specializations
	DEFINE_PARSE_TO_STRING(bool);
	DEFINE_PARSE_TO_STRING(uint8);
	DEFINE_PARSE_TO_STRING(uint16);
	DEFINE_PARSE_TO_STRING(uint32);
	DEFINE_PARSE_TO_STRING(uint64);
	DEFINE_PARSE_TO_STRING(int8);
	DEFINE_PARSE_TO_STRING(int16);
	DEFINE_PARSE_TO_STRING(int32);
	DEFINE_PARSE_TO_STRING(int64);
	DEFINE_PARSE_TO_STRING(float, 3);
	DEFINE_PARSE_TO_STRING(double, 3);
#pragma endregion

#pragma region ParseFromBinary Specializations
	DEFINE_PARSE_FROM_BINARY(bool);
	DEFINE_PARSE_FROM_BINARY(uint8);
	DEFINE_PARSE_FROM_BINARY(uint16);
	DEFINE_PARSE_FROM_BINARY(uint32);
	DEFINE_PARSE_FROM_BINARY(uint64);
	DEFINE_PARSE_FROM_BINARY(int8);
	DEFINE_PARSE_FROM_BINARY(int16);
	DEFINE_PARSE_FROM_BINARY(int32);
	DEFINE_PARSE_FROM_BINARY(int64);
	DEFINE_PARSE_FROM_BINARY(float);
	DEFINE_PARSE_FROM_BINARY(double);
#pragma endregion

#pragma region ParseToBinary Specializations
	DEFINE_PARSE_TO_BINARY(bool);
	DEFINE_PARSE_TO_BINARY(uint8);
	DEFINE_PARSE_TO_BINARY(uint16);
	DEFINE_PARSE_TO_BINARY(uint32);
	DEFINE_PARSE_TO_BINARY(uint64);
	DEFINE_PARSE_TO_BINARY(int8);
	DEFINE_PARSE_TO_BINARY(int16);
	DEFINE_PARSE_TO_BINARY(int32);
	DEFINE_PARSE_TO_BINARY(int64);
	DEFINE_PARSE_TO_BINARY(float);
	DEFINE_PARSE_TO_BINARY(double);
#pragma endregion
}