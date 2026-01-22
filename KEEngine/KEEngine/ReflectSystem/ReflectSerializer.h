#pragma once
#include "File.h"
#include "XMLReader.h"
#include "ReflectObject.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectSerializer
	{
	public:
		static void serializeToXML(IBuffer* outBuffer, const ReflectObject<ObjectType>* obj);
		static void deserializeFromXML(const IBuffer* const outBuffer, ReflectObject<ObjectType>* obj);

	private:
		static void serializeToXMLInner(IBuffer* outBuffer, const ReflectMetaData* reflectMetaData);

	public:
		static void serializeToBinary(IBuffer* outBuffer, const ReflectObject<ObjectType>* obj);
		static void deserializeFromBinary(const IBuffer* const outBuffer, ReflectObject<ObjectType>* obj);
	};
}
#include "ReflectSerializer.hpp"