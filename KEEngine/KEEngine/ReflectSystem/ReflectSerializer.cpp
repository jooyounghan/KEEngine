#include "ReflectSystemPch.h"
#include "ReflectSerializer.h"

#include "StrUtil.h"
#include "XmlReader.h"
#include "XmlWriter.h"
#include "StaticBuffer.h"
#include "IReflectObject.h"
#include "ReflectMetaData.h"
#include "IReflectProperty.h"
#include "IReflectSequenceProperty.h"
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

		std::vector<const IReflectProperty*> complexProperties;

		for (const IReflectProperty* property : properties)
		{
			const EReflectPropertyType reflectPropertyType = property->getType();
			const FlyweightStringA& propertyName = property->getName();
			switch (reflectPropertyType)
			{
			case EReflectPropertyType::POD:
			{
				const IReflectPODProperty* reflectPODProperty = property->castTo<IReflectPODProperty>();
				if (reflectPODProperty == nullptr) break;
				reflectPODProperty->toString(reflectObject, &propertyValueBuffer);
				builder.addAttribute(propertyName.c_str(), propertyName.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
				propertyValueBuffer.reset();
				break;
			}
			case EReflectPropertyType::PODContainer:
			{
				const IReflectSequenceProperty* reflectPODContainerProperty = property->castTo<IReflectSequenceProperty>();
				if (reflectPODContainerProperty == nullptr) break;
				const size_t count = reflectPODContainerProperty->size(reflectObject);
				reflectPODContainerProperty->toString(0, reflectObject, &propertyValueBuffer);
				for (size_t idx = 1; idx < count; ++idx)
				{
					propertyValueBuffer.write(", ", 2);
					reflectPODContainerProperty->toString(idx, reflectObject, &propertyValueBuffer);
				}
				builder.addAttribute(propertyName.c_str(), propertyName.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
				propertyValueBuffer.reset();
				break;
			}
			case EReflectPropertyType::ReflectObject:
			case EReflectPropertyType::ReflectObjectContainer:
			{
				complexProperties.push_back(property);
				break;
			}
			default:
				break;
			}
		}

		if (complexProperties.empty() == false)
		{
			builder.openHeaderEnd();
			for (const IReflectProperty* property : complexProperties)
			{
				const EReflectPropertyType reflectPropertyType = property->getType();
				const FlyweightStringA& propertyName = property->getName();
				switch (reflectPropertyType)
				{
				case EReflectPropertyType::ReflectObject:
				{
					const IReflectObjectProperty* objectProperty = property->castTo<IReflectObjectProperty>();
					if (objectProperty == nullptr) break;
					serializeToXMLInner(xmlWriter, objectProperty->getReflectObject(reflectObject), depth + 1);
					break;
				}
				case EReflectPropertyType::ReflectObjectContainer:
				{
					const IReflectObjectSeqProperty* objectSeqProperty = property->castTo<IReflectObjectSeqProperty>();
					if (objectSeqProperty == nullptr) break;
					const size_t count = objectSeqProperty->size(reflectObject);
					for (size_t idx = 0; idx < count; ++idx)
					{
						serializeToXMLInner(xmlWriter, objectSeqProperty->getReflectObject(idx, reflectObject), depth + 1);
					}
					break;
				}
				case EReflectPropertyType::POD:
				case EReflectPropertyType::PODContainer:
				default:
					break;
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

			const EReflectPropertyType reflectPropertyType = reflectProperty->getType();
			switch (reflectPropertyType)
			{
			case EReflectPropertyType::POD:
			{
				IReflectPODProperty* reflectPODProperty = reflectProperty->castTo<IReflectPODProperty>();
				if (reflectPODProperty == nullptr) break;
				reflectPODProperty->fromString(reflectObject, value.data(), value.length());
				break;
			}
			case EReflectPropertyType::PODContainer:
			{
				IReflectSequenceProperty* reflectPODSeqProperty = reflectProperty->castTo<IReflectSequenceProperty>();
				if (reflectPODSeqProperty == nullptr) break;
				const std::vector<std::string_view> values = StrUtil::split(value.data(), value.length(), ", ", 2);
				const size_t count = values.size();
				reflectPODSeqProperty->resize(reflectObject, count);
				for (size_t idx = 0; idx < count; ++idx)
				{
					reflectPODSeqProperty->fromString(idx, reflectObject, values[idx].data(), values[idx].length());
				}
				break;
			}
			case EReflectPropertyType::ReflectObject:
			case EReflectPropertyType::ReflectObjectContainer:
			default:
				break;
			}
		}

		const std::vector<XmlNode>& children = xmlNode.getChildNodes();
		for (const XmlNode& childNode : children)
		{
			const std::string_view name = createReflectiveString(childNode.getName());

			const FlyweightStringA propertyName(name);
			IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);
			if (reflectProperty == nullptr) continue;

			const EReflectPropertyType reflectPropertyType = reflectProperty->getType();
			switch (reflectPropertyType)
			{
			case EReflectPropertyType::ReflectObject:
			{
				IReflectObjectProperty* objectProperty = reflectProperty->castTo<IReflectObjectProperty>();
				if (objectProperty == nullptr) break;
				deserializeFromXMLInner(childNode, objectProperty->getReflectObject(reflectObject));
				break;
			}
			case EReflectPropertyType::ReflectObjectContainer:
			{
				IReflectObjectSeqProperty* objectSeqProperty = reflectProperty->castTo<IReflectObjectSeqProperty>();
				if (objectSeqProperty == nullptr) break;

				const std::vector<XmlNode>& grandChildren = childNode.getChildNodes();
				const size_t count = grandChildren.size();
				objectSeqProperty->resize(reflectObject, count);
				for (size_t idx = 0; idx < count; ++idx)
				{
					deserializeFromXMLInner(grandChildren[idx], objectSeqProperty->getReflectObject(idx, reflectObject));

				}
				break;
			}
			case EReflectPropertyType::POD:
			case EReflectPropertyType::PODContainer:
			default:
				break;
			}
		}
	}
}