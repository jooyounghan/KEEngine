#pragma once
#include "OwnedString.h"

#include "KEConstant.h"
#include "StaticBuffer.h"

namespace ke
{
	template<typename PropertyType>
	class ReflectParser
	{
	public:
		// This Function has to be specialized
		static PropertyType ParseFromString(const char* src);
		static OwnedStringA ParseToString(const PropertyType& property);

	public:
		static PropertyType ParseFromBinary(const void* src);
		static void ParseToBinary(const PropertyType& property, StaticBuffer<KEConstant::kPropertyBinaryBufferSize>& outBuffer);
	};


	class ReflectParser2
	{
	public:
		using BufferOffset = size_t;
		// This Function has to be specialized
	public:
		template<typename PropertyType>
		static BufferOffset parseFromString(const char* src, PropertyType& outPropertyTypes);
		template<typename PropertyType, typename ...PropertyTypes>
		static BufferOffset parseFromString(const char* src, PropertyType& outPropertyType, PropertyTypes&... outPropertyTypes);


		template<typename PropertyType>
		static void ParseToString(StaticBuffer<KEConstant::kStringConvertorBufferSize>& outStringBuffer, const PropertyType& property);
		template<typename PropertyType, typename ...PropertyTypes>
		static void ParseToString(StaticBuffer<KEConstant::kStringConvertorBufferSize>& outStringBuffer, const PropertyType& propertyType, const PropertyTypes&... propertyTypes);

	public:
		//static ParseFromBinary(const void* src, PropertyTypes&... outPropertyTypes);
		//static void ParseToBinary(StaticBuffer<kPropertyBinaryBufferSize>& outBuffer, const PropertyTypes&... property);
	};

	using BufferOffset = ReflectParser2::BufferOffset;
}
#include "ReflectParser.hpp"
