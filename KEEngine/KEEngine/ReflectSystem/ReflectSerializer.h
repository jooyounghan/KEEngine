#pragma once

namespace ke
{
	class IReflectObject;
	class XmlWriter;

	class ReflectSerializer
	{
	public:
		static void serializeToXML(const char* fileDir, const IReflectObject* obj);
		static void deserializeFromXML(const char* fileDir, const IReflectObject* obj);

	private:
		static void serializeToXMLInner(XmlWriter& xmlWriter, const IReflectObject* reflectObject, uint32 depth);

	public:
		//static void serializeToBinary(IBuffer* outBuffer, const IReflectObject* obj);
		//static void deserializeFromBinary(const IBuffer* const IReflectObject* obj);
	};
}