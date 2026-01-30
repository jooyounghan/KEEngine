#include "ReflectSystemPch.h"
#include "ReflectSerializer.h"

#include "StaticBuffer.h"
#include "XmlReader.h"
#include "XmlWriter.h"
#include "ReflectProperty.h"
#include "ReflectMetaData.h"

namespace ke
{
	void ReflectSerializer::serializeToXML(const char* path, const IReflectObject* obj)
	{
		XmlWriter xmlWriter(path);
		serializeToXMLInner(xmlWriter, obj, 0);
		xmlWriter.writeToFile();
	}

	void ke::ReflectSerializer::serializeToXMLInner(XmlWriter& xmlWriter, const IReflectObject* reflectObject, uint32 depth)
	{
		static StaticBuffer<256> propertyValueBuffer;

		const FlyweightStringA& objetName = reflectObject->getName();
		XmlBuilder builder(objetName.c_str(), objetName.length(), &xmlWriter, depth);

		const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();
		const std::vector<PTR(IReflectProperty)>& properties = reflectMetaData->getAllProperties();
		std::vector<IReflectProperty*> reflectObjectProperties;

		for (const PTR(IReflectProperty)& property : properties)
		{
			if (property->isReflectObject())
			{
				reflectObjectProperties.push_back(property.get());
			}
			else
			{
				const FlyweightStringA& propertyName = property->getName();
				property->getToString(reflectObject, &propertyValueBuffer);
				builder.addAttribute(propertyName.c_str(), propertyName.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
				propertyValueBuffer.reset();
			}
		}

		builder.openHeaderEnd();
		for (IReflectProperty* property : reflectObjectProperties)
		{
			serializeToXMLInner(xmlWriter, property->castAsReflectObject(reflectObject), depth + 1);
		}
	}
}