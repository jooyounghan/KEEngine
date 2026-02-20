#include "ReflectSystemPch.h"
#include "ReflectSerializer.h"

#include "StrUtil.h"
#include "XmlReader.h"
#include "XmlWriter.h"
#include "StaticBuffer.h"
#include "IReflectObject.h"
#include "ReflectMetaData.h"
#include "IReflectProperty.h"
#include "IReflectPODSeqProperty.h"
#include "IReflectObjectProperty.h"
#include "IReflectObjectSeqProperty.h"

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
		static StaticBuffer<BUFFER_BYTES_1KB> propertyValueBuffer;

		const FlyweightStringA& objetName = reflectObject->getName();
		XmlBuilder builder(objetName.c_str(), objetName.length(), &xmlWriter, depth);

		const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();
		const OwnerVector<IReflectProperty>& properties = reflectMetaData->getAllProperties();

		std::vector<const IReflectProperty*> childProperties;

		for (const IReflectProperty* property : properties)
		{
			const FlyweightStringA& propertyName = property->getName();

			if (property->isAttributeProperty())
			{
				if (const IReflectPODProperty* reflectPODProperty = property->castTo<IReflectPODProperty>())
				{
					reflectPODProperty->toString(reflectObject, &propertyValueBuffer);
					builder.addAttribute(propertyName.c_str(), propertyName.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
					propertyValueBuffer.reset();
				}
				else if (const IReflectPODSeqProperty* reflectPODSeqProperty = property->castTo<IReflectPODSeqProperty>())
				{
					const size_t count = reflectPODSeqProperty->size(reflectObject);
					reflectPODSeqProperty->toString(0, reflectObject, &propertyValueBuffer);
					for (size_t idx = 1; idx < count; ++idx)
					{
						propertyValueBuffer.write(", ", 2);
						reflectPODSeqProperty->toString(idx, reflectObject, &propertyValueBuffer);
					}
					builder.addAttribute(propertyName.c_str(), propertyName.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
					propertyValueBuffer.reset();
				}
			}
			else
			{
				childProperties.push_back(property);
			}
		}

		if (childProperties.empty() == false)
		{
			builder.openHeaderEnd();
			for (const IReflectProperty* property : childProperties)
			{
				if (const IReflectObjectProperty* objectProperty = property->castTo<IReflectObjectProperty>())
				{
					serializeToXMLInner(xmlWriter, objectProperty->getReflectObject(reflectObject), depth + 1);
				}
				else if (const IReflectObjectSeqProperty* objectSeqProperty = property->castTo<IReflectObjectSeqProperty>())
				{
					const size_t count = objectSeqProperty->size(reflectObject);
					for (size_t idx = 0; idx < count; ++idx)
					{
						serializeToXMLInner(xmlWriter, objectSeqProperty->getReflectObject(idx, reflectObject), depth + 1);
					}
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
			const std::string_view name = attribute.getName();
			const std::string_view value = attribute.getValue();

			FlyweightStringA propertyName(name);
			IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);
			if (reflectProperty == nullptr) continue;
			if (!reflectProperty->isAttributeProperty()) continue;

			if (IReflectPODProperty* reflectPODProperty = reflectProperty->castTo<IReflectPODProperty>())
			{
				reflectPODProperty->fromString(reflectObject, value.data(), value.length());
			}
			else if (IReflectPODSeqProperty* reflectPODSeqProperty = reflectProperty->castTo<IReflectPODSeqProperty>())
			{
				const std::vector<std::string_view> values = StrUtil::split(value.data(), value.length(), ", ", 2);
				const size_t count = values.size();
				reflectPODSeqProperty->resize(reflectObject, count);
				for (size_t idx = 0; idx < count; ++idx)
				{
					reflectPODSeqProperty->fromString(idx, reflectObject, values[idx].data(), values[idx].length());
				}
			}
		}

		const std::vector<XmlNode>& children = xmlNode.getChildNodes();
		for (const XmlNode& childNode : children)
		{
			const std::string_view name = createReflectiveString(childNode.getName());

			const FlyweightStringA propertyName(name);
			IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);
			if (reflectProperty == nullptr) continue;
			if (reflectProperty->isAttributeProperty()) continue;

			if (IReflectObjectProperty* objectProperty = reflectProperty->castTo<IReflectObjectProperty>())
			{
				deserializeFromXMLInner(childNode, objectProperty->getReflectObject(reflectObject));
			}
			else if (IReflectObjectSeqProperty* objectSeqProperty = reflectProperty->castTo<IReflectObjectSeqProperty>())
			{
				const std::vector<XmlNode>& grandChildren = childNode.getChildNodes();
				const size_t count = grandChildren.size();
				objectSeqProperty->resize(reflectObject, count);
				for (size_t idx = 0; idx < count; ++idx)
				{
					deserializeFromXMLInner(grandChildren[idx], objectSeqProperty->getReflectObject(idx, reflectObject));
				}
			}
		}
	}
}