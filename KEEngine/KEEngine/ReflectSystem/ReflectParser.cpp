#include "ReflectSystemPch.h"
#include "ReflectParser.h"
#include "FlyweightString.h"
#include "StrUtil.h"

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

	template<>
	Offset ReflectParser::parseFromString(const char* src, std::string* outPropertyTypes)
	{
		size_t length = strlen(src);
		outPropertyTypes->assign(src, length);
		return static_cast<Offset>(length);
	}

	template<>
	Offset ReflectParser::parseFromString(const char* src, FlyweightStringA* outPropertyTypes)
	{
		size_t length = strlen(src);
		std::string_view strView(static_cast<const char*>(src), length);
		outPropertyTypes->operator=(strView);
		return static_cast<Offset>(length);
	}

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
	DEFINE_PARSE_TO_STRING(float, 5);
	DEFINE_PARSE_TO_STRING(double, 5);

	template<>
	void ReflectParser::parseToString(IBuffer* outStringBuffer, const std::string* property)
	{
		outStringBuffer->write(property->c_str(), property->length());
	}

	template<>
	void ReflectParser::parseToString(IBuffer* outStringBuffer, const FlyweightStringA* property)
	{
		const char* str = property->c_str();
		if (str)
		{
			outStringBuffer->write(str, property->length());
		}
	}
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

	template<>
	Offset ReflectParser::parseFromBinary(const void* src, std::string* outPropertyTypes)
	{
		uint32 length = 0;
		memcpy(&length, src, sizeof(uint32));
		outPropertyTypes->resize(length);
		memcpy(outPropertyTypes->data(), static_cast<const char*>(src) + sizeof(uint32), length);
		return sizeof(uint32) + length;
	}

	template<>
	Offset ReflectParser::parseFromBinary(const void* src, FlyweightStringA* outPropertyTypes)
	{
		uint32 length = 0;
		memcpy(&length, src, sizeof(uint32));
		std::string_view strView(static_cast<const char*>(src) + sizeof(uint32), length);
		outPropertyTypes->operator=(strView);
		return sizeof(uint32) + length;
	}
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

	template<>
	void ReflectParser::parseToBinary(IBuffer* outStringBuffer, const std::string* outPropertyTypes)
	{
		uint32 length = static_cast<uint32>(outPropertyTypes->length());
		outStringBuffer->write(&length, sizeof(uint32));
		outStringBuffer->write(outPropertyTypes->c_str(), length);
	}

	template<>
	void ReflectParser::parseToBinary(IBuffer* outStringBuffer, const FlyweightStringA* outPropertyTypes)
	{
		uint32 length = static_cast<uint32>(outPropertyTypes->length());
		outStringBuffer->write(&length, sizeof(uint32));
		const char* str = outPropertyTypes->c_str();
		if (str)
		{
			outStringBuffer->write(str, length);
		}
	}
#pragma endregion
}