#pragma once

#define DECLARE_PARSE_SPECIALIZATION(Type)																\
template<> size_t ReflectParser::getPropertyBufferSize(const Type* outPropertyTypes);					\
template<> Offset ReflectParser::parseFromString(const char* src, Type* outPropertyTypes);				\
template<> void ReflectParser::parseToString(IBuffer* outStringBuffer, const Type* outPropertyTypes);	\
template<> Offset ReflectParser::parseFromBinary(const void* src, Type* outPropertyTypes);				\
template<> void ReflectParser::parseToBinary(IBuffer* outStringBuffer, const Type* outPropertyTypes);	

namespace ke
{
	template<typename PropertyType>
	size_t ReflectParser::getPropertyBufferSize(const PropertyType* outPropertyTypes)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType>
	Offset ReflectParser::parseFromString(const char* src, PropertyType* outPropertyTypes) NOT_REQUIRES_REFLECT_OBJECT(PropertyType)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType>
	Offset ReflectParser::parseFromString(const char* src, PropertyType* outPropertyTypes) REQUIRES_REFLECT_OBJECT(PropertyType)
	{
		return Offset();
	}

	template<typename PropertyType, typename ...PropertyTypes>
	Offset ReflectParser::parseFromString(const char* src, PropertyType* outPropertyType, PropertyTypes* ...outPropertyTypes)
	{
		return parseFromString(src + parseFromString(src, outPropertyType) + 1, outPropertyTypes...);
	}

	template<typename PropertyType>
	void ReflectParser::parseToString(IBuffer* outStringBuffer, const PropertyType* property) NOT_REQUIRES_REFLECT_OBJECT(PropertyType)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType>
	void ReflectParser::parseToString(IBuffer* outStringBuffer, const PropertyType* property) REQUIRES_REFLECT_OBJECT(PropertyType)
	{
	}

	template<typename PropertyType, typename ...PropertyTypes>
	void ReflectParser::parseToString(IBuffer* outStringBuffer, const PropertyType* propertyType, const PropertyTypes* ...propertyTypes)
	{
		parseToString(outStringBuffer, propertyType);
		outStringBuffer->writeOne(',');
		parseToString(outStringBuffer, propertyTypes...);
	}


	template<typename PropertyType>
	Offset ReflectParser::parseFromBinary(const void* src, PropertyType* outPropertyTypes) NOT_REQUIRES_REFLECT_OBJECT(PropertyType)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}
	
	template<typename PropertyType>
	Offset ReflectParser::parseFromBinary(const void* src, PropertyType* outPropertyTypes) REQUIRES_REFLECT_OBJECT(PropertyType)
	{
		return Offset();
	}

	template<typename PropertyType, typename ...PropertyTypes>
	Offset ReflectParser::parseFromBinary(const void* src, PropertyType* outPropertyType, PropertyTypes* ...outPropertyTypes)
	{
		return parseFromBinary(static_cast<const uint8*>(src) + parseFromBinary(src, outPropertyType), outPropertyTypes...);
	}

	template<typename PropertyType>
	void ReflectParser::parseToBinary(IBuffer* outBuffer, const PropertyType* property) NOT_REQUIRES_REFLECT_OBJECT(PropertyType)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectParser);
	}

	template<typename PropertyType>
	void ReflectParser::parseToBinary(IBuffer* outBuffer, const PropertyType* property) REQUIRES_REFLECT_OBJECT(PropertyType)
	{
	}

	template<typename PropertyType, typename ...PropertyTypes>
	void ReflectParser::parseToBinary(IBuffer* outStringBuffer, const PropertyType* propertyType, const PropertyTypes* ...propertyTypes)
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