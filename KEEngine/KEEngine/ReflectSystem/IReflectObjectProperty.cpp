#include "ReflectSystemPch.h"
#include "IReflectObjectProperty.h"
#include "ReflectMetaData.h"

namespace ke
{
	IReflectObjectProperty::IReflectObjectProperty(const FlyweightStringA& name)
		: IReflectProperty(name)
	{
	}

	void IReflectObjectProperty::serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const
	{
		const IReflectObject* reflectObject = getReflectObject(obj);
		const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();

		const OwnerVector<IReflectProperty>& reflectProperties = reflectMetaData->getAllProperties();
				
		XmlBuilder builder(_name.c_str(), _name.length(), xmlWriter, true/*isReflectObject()*/);
		for (const IReflectProperty* reflectProperty : reflectProperties)
		{
			reflectProperty->serailizeToXml(xmlWriter, &builder, reflectObject);
		}
	}

	std::string IReflectObjectProperty::convertToReflectName(const std::string_view& str)
	{
		std::string reflectName;
		reflectName.reserve(str.length() + 1);
		reflectName.push_back('_');
		reflectName.push_back(std::tolower(static_cast<unsigned char>(str[0])));
		reflectName.append(str.data() + 1, str.size() - 1);
		return reflectName;
	}

	void IReflectObjectProperty::deserializeFromXML(const XmlNode* xmlNode, const XmlAttribute * xmlAttribute, IReflectObject * obj)
	{
		const std::string_view name = xmlNode->getName();
		if (_name != name)
		{
			KE_ASSERT_DEV(false, "IReflectObjectProperty name mismatched with Node");
			return;
		}

		IReflectObject* reflectObject = getReflectObject(obj);
		const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();

		for (XmlAttribute attribute = xmlNode->getFirstAttribute(); attribute.isValid(); attribute = attribute.getNextAttribute())
		{
			const std::string_view name = attribute.getName();
			const std::string_view value = attribute.getValue();

			FlyweightStringA propertyName(name);
			IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);

			if (reflectProperty == nullptr)
			{
				KE_ASSERT_DEV(false, "Attribute에 대한 이름이 ReflectObjectProperty의 메타데이터에 없습니다.");
				continue;
			}

			reflectProperty->deserializeFromXML(xmlNode, &attribute, reflectObject);
		}

		const std::vector<XmlNode>& children = xmlNode->getChildNodes();
		for (const XmlNode& childNode : children)
		{
			const FlyweightStringA propertyName(convertToReflectName(childNode.getName()));
			IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);
			if (reflectProperty == nullptr)
			{
				KE_ASSERT_DEV(false, "Child Node에 대한 이름이 ReflectObjectProperty의 메타데이터에 없습니다.");
				continue;
			}

			reflectProperty->deserializeFromXML(xmlNode, nullptr, reflectObject);
		}
	}

	void IReflectObjectProperty::serializeToBinary(IBuffer* dstBuffer, const IReflectObject* obj) const
	{}

	void IReflectObjectProperty::deserializeFromBinary(const IBuffer * srcBuffer, const IReflectObject * obj)
	{}

	bool IReflectObjectProperty::isDefault(const IReflectObject * obj) const
	{
		bool isDefault = true;
		const IReflectObject* reflectObject = getReflectObject(obj);
		const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();

		const OwnerVector<IReflectProperty>& reflectProperties = reflectMetaData->getAllProperties();
		for (const IReflectProperty* reflectProperty : reflectProperties)
		{			
			isDefault &= reflectProperty->isDefault(reflectObject);
			if (isDefault == false) break;
		}
		return isDefault;
	}
}
