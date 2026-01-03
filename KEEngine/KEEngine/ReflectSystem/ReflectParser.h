#pragma once
#include "IBuffer.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectObject;

#define IS_BASE_OF_REFLECT_OBJECT(PropertyType) IS_BASE_OF(ReflectObject<PropertyType>, PropertyType)
#define REQUIRES_REFLECT_OBJECT(PropertyType) requires (IS_BASE_OF(ReflectObject<PropertyType>, PropertyType))
#define NOT_REQUIRES_REFLECT_OBJECT(PropertyType) requires (!IS_BASE_OF(ReflectObject<PropertyType>, PropertyType))

	class ReflectParser
	{
	public:
		template<typename PropertyType>
		static size_t getPropertyBufferSize(const PropertyType* outPropertyTypes);

	public:
		template<typename PropertyType>
		static Offset parseFromString(const char* src, PropertyType* outPropertyTypes) NOT_REQUIRES_REFLECT_OBJECT(PropertyType);
		template<typename PropertyType>
		static Offset parseFromString(const char* src, PropertyType* outPropertyTypes) REQUIRES_REFLECT_OBJECT(PropertyType);
		template<typename PropertyType, typename ...PropertyTypes>
		static Offset parseFromString(const char* src, PropertyType* outPropertyType, PropertyTypes*... outPropertyTypes);

	public:
		template<typename PropertyType>
		static void parseToString(IBuffer* outStringBuffer, const PropertyType* property) NOT_REQUIRES_REFLECT_OBJECT(PropertyType);
		template<typename PropertyType>
		static void parseToString(IBuffer* outStringBuffer, const PropertyType* property) REQUIRES_REFLECT_OBJECT(PropertyType);
		template<typename PropertyType, typename ...PropertyTypes>
		static void parseToString(IBuffer* outStringBuffer, const PropertyType* propertyType, const PropertyTypes*... propertyTypes);

	public:
		template<typename PropertyType>
		static Offset parseFromBinary(const void* src, PropertyType* outPropertyTypes) NOT_REQUIRES_REFLECT_OBJECT(PropertyType);
		template<typename PropertyType>
		static Offset parseFromBinary(const void* src, PropertyType* outPropertyTypes) REQUIRES_REFLECT_OBJECT(PropertyType);
		template<typename PropertyType, typename ...PropertyTypes>
		static Offset parseFromBinary(const void* src, PropertyType* outPropertyType, PropertyTypes*... outPropertyTypes);

	public:
		template<typename PropertyType>
		static void parseToBinary(IBuffer* outBuffer, const PropertyType* property) NOT_REQUIRES_REFLECT_OBJECT(PropertyType);
		template<typename PropertyType>
		static void parseToBinary(IBuffer* outBuffer, const PropertyType* property) REQUIRES_REFLECT_OBJECT(PropertyType);
		template<typename PropertyType, typename ...PropertyTypes>
		static void parseToBinary(IBuffer* outBuffer, const PropertyType* propertyType, const PropertyTypes*... propertyTypes);
	};
}

#include "ReflectParser.hpp"
