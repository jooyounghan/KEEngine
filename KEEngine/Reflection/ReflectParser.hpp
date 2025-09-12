#pragma once
#include "ReflectParser.h"

namespace ke
{
	template<typename PropertyType>
	inline PropertyType ReflectParser<PropertyType>::ParseFromString(const char* src)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser<T>::ParserFromString)."); return  PropertyType();
	}
	template<typename PropertyType>
	inline OwnedStringA ReflectParser<PropertyType>::ParseToString(const PropertyType& property)
	{
		static_assert(false, "This type is not supported as ReflectProperty(ReflectParser<T>::ParseToString)."); return  OwnedStringA();
	}

	template<>
	inline bool ReflectParser<bool>::ParseFromString(const char* src)
	{
		return strcmp(src, "true") == 0;
	}

	template<>
	inline OwnedStringA ReflectParser<bool>::ParseToString(const bool& property)
	{
		return property ? "true" : "false";
	}

	template<>
	inline int32 ReflectParser<int32>::ParseFromString(const char* src)
	{
		return atoi(src);
	}

	template<>
	inline OwnedStringA ReflectParser<int>::ParseToString(const int& property)
	{
		return OwnedStringA("");
	}
}