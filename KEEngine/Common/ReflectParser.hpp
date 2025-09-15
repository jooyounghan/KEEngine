#pragma once
#include "ReflectParser.h"
#include "StringConvertor.h"

#define DEFINE_Z_PARSE_FROM_STRING(Type)					\
template<>                                                  \
Type ReflectParser<Type>::ParseFromString(const char* src)  \
{															\
	return 	static_cast<Type>(strtoull(src, nullptr, 0));	\
}

#define DEFINE_PARSE_TO_STRING(Type)									\
template<>																\
OwnedStringA ReflectParser<Type>::ParseToString(const Type& property)	\
{																		\
	return StringConvertor::convertToString<Type>(property);			\
}

#define DEFINE_PARSE_TO_STRING_F(Type)									\
template<>																\
OwnedStringA ReflectParser<Type>::ParseToString(const Type& property)	\
{																		\
	return StringConvertor::convertToString<Type>(property, 3);			\
}

#define DEFINE_PARSE_FROM_BINARY_POD(Type)					\
template<>													\
Type ReflectParser<Type>::ParseFromBinary(const void* src)	\
{															\
	Type result;											\
	memcpy(&result, src, sizeof(Type));						\
	return result;											\
}

#define DEFINE_PARSE_TO_BINARY_POD(Type)																			\
template<>																											\
void ReflectParser<Type>::ParseToBinary(const Type& property, StaticBuffer<kPropertyBinaryBufferSize>& outBuffer)	\
{																													\
	outBuffer.write(&property, sizeof(Type));																		\
}



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
	void ReflectParser<PropertyType>::ParseToBinary(const PropertyType& property, StaticBuffer<kPropertyBinaryBufferSize>& outBuffer)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser<T>::ParseToBinary)."); return;
	}

#pragma region ParseFromString Specializations
	template<>
	bool ReflectParser<bool>::ParseFromString(const char* src)
	{
		return strcmp(src, "true") == 0;
	}

	DEFINE_Z_PARSE_FROM_STRING(uint8);
	DEFINE_Z_PARSE_FROM_STRING(uint16);
	DEFINE_Z_PARSE_FROM_STRING(uint32);
	DEFINE_Z_PARSE_FROM_STRING(uint64);
	DEFINE_Z_PARSE_FROM_STRING(int8);
	DEFINE_Z_PARSE_FROM_STRING(int16);
	DEFINE_Z_PARSE_FROM_STRING(int32);
	DEFINE_Z_PARSE_FROM_STRING(int64);	

	template<> 
	float ReflectParser<float>::ParseFromString(const char* src) 
	{
		return strtof(src, nullptr);
	};

	template<> 
	double ReflectParser<double>::ParseFromString(const char* src)
	{
		return strtod(src, nullptr);
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
	DEFINE_PARSE_TO_STRING_F(float);
	DEFINE_PARSE_TO_STRING_F(double);
#pragma endregion

#pragma region ParseFromBinary Specializations
	DEFINE_PARSE_FROM_BINARY_POD(bool);
	DEFINE_PARSE_FROM_BINARY_POD(uint8);
	DEFINE_PARSE_FROM_BINARY_POD(uint16);
	DEFINE_PARSE_FROM_BINARY_POD(uint32);
	DEFINE_PARSE_FROM_BINARY_POD(uint64);
	DEFINE_PARSE_FROM_BINARY_POD(int8);
	DEFINE_PARSE_FROM_BINARY_POD(int16);
	DEFINE_PARSE_FROM_BINARY_POD(int32);
	DEFINE_PARSE_FROM_BINARY_POD(int64);
	DEFINE_PARSE_FROM_BINARY_POD(float);
	DEFINE_PARSE_FROM_BINARY_POD(double);
#pragma endregion

#pragma region ParseToBinary Specializations
	DEFINE_PARSE_TO_BINARY_POD(bool);
	DEFINE_PARSE_TO_BINARY_POD(uint8);
	DEFINE_PARSE_TO_BINARY_POD(uint16);
	DEFINE_PARSE_TO_BINARY_POD(uint32);
	DEFINE_PARSE_TO_BINARY_POD(uint64);
	DEFINE_PARSE_TO_BINARY_POD(int8);
	DEFINE_PARSE_TO_BINARY_POD(int16);
	DEFINE_PARSE_TO_BINARY_POD(int32);
	DEFINE_PARSE_TO_BINARY_POD(int64);
	DEFINE_PARSE_TO_BINARY_POD(float);
	DEFINE_PARSE_TO_BINARY_POD(double);
#pragma endregion
}