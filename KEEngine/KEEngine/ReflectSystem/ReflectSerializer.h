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
		void SerializeToXML(IBuffer* outBuffer, const ReflectObject<ObjectType>& obj);
		void DeserializeFromXML(const IBuffer* const outBuffer, ReflectObject<ObjectType>& obj);

	};
}