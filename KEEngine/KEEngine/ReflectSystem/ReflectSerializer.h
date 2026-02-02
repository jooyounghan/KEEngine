#pragma once

namespace ke
{
	class IReflectObject;
	class XmlWriter;
	class XmlNode;

	class ReflectSerializer
	{
	public:
		static void serializeToXML(const char* path, const IReflectObject* obj);
		static void deserializeFromXML(const char* path, IReflectObject* obj);

	private:
		static void serializeToXMLInner(XmlWriter& xmlWriter, const IReflectObject* reflectObject, uint32 depth);
		static void deserializeFromXMLInner(const XmlNode& xmlNode, IReflectObject* reflectObject);
	public:
		//static void serializeToBinary(IBuffer* outBuffer, const IReflectObject* obj);
		//static void deserializeFromBinary(const IBuffer* const IReflectObject* obj);
	};
}