#include "ReflectSystemPch.h"
#include "ReflectSerializer.h"

#include "StaticBuffer.h"
#include "XmlReader.h"
#include "XmlWriter.h"
#include "IReflectProperty.h"
#include "ReflectMetaData.h"

namespace ke
{
	void ReflectSerializer::serializeToXML(const char* path, const IReflectObject* obj)
	{
		XmlWriter xmlWriter(path);
		serializeToXMLInner(xmlWriter, obj, 0);
		xmlWriter.writeToFile();
	}

	void ReflectSerializer::deserializeFromXML(const char* path, IReflectObject* obj)
	{
		XmlReader xmlReader(path);
		const XmlNode& rootNode = xmlReader.getRootNode();
		const std::vector<XmlNode>& childNodes = rootNode.getChildNodes();
		for (const XmlNode& childNode : childNodes)
		{
			deserializeFromXMLInner(childNode, obj);
		}
	}

	void ke::ReflectSerializer::serializeToXMLInner(XmlWriter& xmlWriter, const IReflectObject* reflectObject, uint32 depth)
	{
		static StaticBuffer<BUFFER_BYTES_256> propertyValueBuffer;

		const FlyweightStringA& objetName = reflectObject->getName();
		XmlBuilder builder(objetName.c_str(), objetName.length(), &xmlWriter, depth);

		const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();
		const OwnerVector<IReflectProperty>& properties = reflectMetaData->getAllProperties();
		std::vector<const IReflectProperty*> reflectObjectProperties;

		for (const IReflectProperty* property : properties)
		{
			// New extensible approach using getPropertyType()
			switch (property->getPropertyType())
			{
			case EReflectPropertyType::Object:
				reflectObjectProperties.push_back(property);
				break;
			case EReflectPropertyType::POD:
			case EReflectPropertyType::Vector:
			case EReflectPropertyType::Enum:
				{
					const FlyweightStringA& propertyName = property->getName();
					property->getToString(reflectObject, &propertyValueBuffer);
					builder.addAttribute(propertyName.c_str(), propertyName.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
					propertyValueBuffer.reset();
				}
				break;
			}
		}

		if (reflectObjectProperties.empty() == false)
		{
			builder.openHeaderEnd();
			for (const IReflectProperty* property : reflectObjectProperties)
			{
				const IReflectObjectProperty* objectProperty = property->as<IReflectObjectProperty>();
				if (objectProperty != nullptr)
				{
					serializeToXMLInner(xmlWriter, objectProperty->getReflectObject(reflectObject), depth + 1);
				}
			}
		}
	}

	static std::string_view createReflectiveString(const std::string_view& str) 
	{
		static StaticBuffer<BUFFER_BYTES_256> tempBuffer;
		tempBuffer.reset();

		tempBuffer.writeOne('_');
		tempBuffer.writeOne(std::tolower(str[0]));
		tempBuffer.write(str.data() + 1, str.size() - 1);

		return std::string_view(tempBuffer.getConstBuffer(), tempBuffer.getCursorPos());
	}

	void ReflectSerializer::deserializeFromXMLInner(const XmlNode& xmlNode, IReflectObject* reflectObject)
	{
		const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();
		for (XmlAttribute attribute = xmlNode.getFirstAttribute(); attribute.isValid(); attribute = attribute.getNextAttribute())
		{
			std::string_view name = attribute.getName();
			std::string_view value = attribute.getValue();

			FlyweightStringA propertyName(name);
			IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);

			if (reflectProperty != nullptr)
			{
				reflectProperty->setFromString(reflectObject, value.data(), value.length());
			}
		}

		const std::vector<XmlNode>& children = xmlNode.getChildNodes();
		for (const XmlNode& childNode : children)
		{
			std::string_view name = createReflectiveString(childNode.getName());

			FlyweightStringA propertyName(name);
			IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);

			if (reflectProperty != nullptr)
			{
				IReflectObjectProperty* objectProperty = reflectProperty->as<IReflectObjectProperty>();
				if (objectProperty != nullptr)
				{
					deserializeFromXMLInner(childNode, objectProperty->getReflectObject(reflectObject));
				}
			}
		}
	}
}