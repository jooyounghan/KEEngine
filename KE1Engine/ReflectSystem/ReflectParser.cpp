#include "ReflectParser.h"
#include "StringConvertor.h"

#define DEFINE_PARSE_FROM_STRING(Type, StringParser, ...)										\
template<>																						\
KEBufferOffset ReflectParser::parseFromString(const char* src, Type& outPropertyTypes)			\
{																								\
    char* endPtr = nullptr;																		\
    outPropertyTypes = static_cast<Type>(StringParser(src, &endPtr, ## __VA_ARGS__));			\
    return static_cast<size_t>(endPtr - src);													\
}

#define DEFINE_PARSE_TO_STRING(Type, ...)														\
template<>																						\
void ReflectParser::parseToString(IBuffer* outStringBuffer, const Type& property)			\
{																								\
	return StringConvertor::convertToStringBuffer(outStringBuffer, property, ## __VA_ARGS__);	\
}

#define DEFINE_PARSE_FROM_BINARY(Type)												\
template<>																				\
KEBufferOffset ReflectParser::parseFromBinary(const void* src, Type& outPropertyTypes)	\
{																						\
	KEBufferOffset offset = sizeof(Type);												\
	memcpy(&outPropertyTypes, src, offset);												\
	return offset;																		\
}

#define DEFINE_PARSE_TO_BINARY(Type)														\
template<>																						\
void ReflectParser::parseToBinary(IBuffer* outStringBuffer, const Type& outPropertyTypes)	\
{																								\
	outStringBuffer->write(&outPropertyTypes, sizeof(Type));									\
}

namespace ke
{
#pragma region parseFromString Specializations
	template<>
	KEBufferOffset ReflectParser::parseFromString(const char* src, bool& outPropertyTypes)
	{
		outPropertyTypes = strcmp(src, "true") == 0;
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