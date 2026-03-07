#define REFLECT_OBJECT_SEQUENCE_TEMPLATE \
    template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>

#define REFLECT_OBJECT_SEQUENCE_CLASS \
    ReflectObjectSequenceProperty<ObjectType, ContainerType, PropertyType>

namespace ke
{
	REFLECT_OBJECT_SEQUENCE_TEMPLATE
		REFLECT_OBJECT_SEQUENCE_CLASS::ReflectObjectSequenceProperty(
		const FlyweightStringA& name, 
		REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, ContainerType<PropertyType>)
	) : IReflectProperty(name),
		ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>(getter, constGetter, setter)
	{
		STATIC_ASSERT_IS_BASE_OF(IReflectObject, PropertyType);
		STATIC_ASSERT((ReflectSequenceContainerCompatible<ContainerType<PropertyType>, PropertyType>), "ContainerType must be ReflectSequenceContainerCompatible");
	}

	REFLECT_OBJECT_SEQUENCE_TEMPLATE
	void REFLECT_OBJECT_SEQUENCE_CLASS::serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const
	{
		XmlBuilder builder(_name.c_str(), _name.length(), xmlWriter, true/*isReflectObject()*/);
		const ContainerType<PropertyType>& containerProperty = this->get(obj);
		for (const PropertyType& property : containerProperty)
		{
			const IReflectObject* reflectObject = static_cast<const IReflectObject*>(&property);
			const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();

			const OwnerVector<IReflectProperty>& reflectProperties = reflectMetaData->getAllProperties();

			const FlyweightStringA& name = reflectObject->getName();
			XmlBuilder elementBuilder(name.c_str(), name.length(), xmlWriter, true/*isReflectObject()*/);
			for (const IReflectProperty* reflectProperty : reflectProperties)
			{
				reflectProperty->serailizeToXml(xmlWriter, &elementBuilder, reflectObject);
			}
		}
	}

	REFLECT_OBJECT_SEQUENCE_TEMPLATE
	void REFLECT_OBJECT_SEQUENCE_CLASS::deserializeFromXML(const XmlNode * xmlNode, const XmlAttribute * xmlAttribute, IReflectObject * obj)
	{
		const std::string_view name = xmlNode->getName();
		if (_name != name)
		{
			KE_ASSERT_DEV(false, "IReflectObjectProperty name mismatched with Node");
			return;
		}

		ContainerType<PropertyType>& containerProperty = this->get(obj);
		const std::vector<XmlNode>& children = xmlNode->getChildNodes();
		for (const XmlNode& childNode : children)
		{
			PropertyType& property = containerProperty.emplace_back();

			IReflectObject* reflectObject = static_cast<IReflectObject*>(&property);
			const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();

			for (XmlAttribute attribute = childNode->getFirstAttribute(); attribute.isValid(); attribute = attribute.getNextAttribute())
			{
				const std::string_view name = attribute.getName();
				const std::string_view value = attribute.getValue();

				FlyweightStringA propertyName(name);
				IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);

				if (reflectProperty == nullptr)
				{
					KE_ASSERT_DEV(false, "Attribute에 대한 이름이 ReflectObjectSequenceProperty의 Property 메타데이터에 없습니다.");
					continue;
				}

				reflectProperty->deserializeFromXML(childNode, &attribute, reflectObject);
			}

			const std::vector<XmlNode>& grandChildren = childNode->getChildNodes();
			for (const XmlNode& grandChildNode : grandChildren)
			{
				const FlyweightStringA propertyName(IReflectObjectProperty::convertToReflectName(grandChildNode.getName()));
				IReflectProperty* reflectProperty = reflectMetaData->getPropertyByName(propertyName);
				if (reflectProperty == nullptr)
				{
					KE_ASSERT_DEV(false, "Child Node에 대한 이름이 ReflectObjectSequenceProperty의 의 Property 메타데이터에 없습니다.");
					continue;
				}

				reflectProperty->deserializeFromXML(grandChildNode, nullptr, reflectObject);
			}
		}
	}

	REFLECT_OBJECT_SEQUENCE_TEMPLATE
	void REFLECT_OBJECT_SEQUENCE_CLASS::serializeToBinary(IBuffer * dstBuffer, const IReflectObject * obj) const
	{}

	REFLECT_OBJECT_SEQUENCE_TEMPLATE
	void REFLECT_OBJECT_SEQUENCE_CLASS::deserializeFromBinary(const IBuffer * srcBuffer, const IReflectObject * obj)
	{}

	REFLECT_OBJECT_SEQUENCE_TEMPLATE
	bool REFLECT_OBJECT_SEQUENCE_CLASS::isDefault(const IReflectObject * obj) const
	{
		bool isDefault = true;

		const ContainerType<PropertyType>& containerProperty = this->get(obj);
		for (const PropertyType& property : containerProperty)
		{
			const IReflectObject* reflectObject = static_cast<const IReflectObject*>(&property);
			const ReflectMetaData* reflectMetaData = reflectObject->getMetaData();

			const OwnerVector<IReflectProperty>& reflectProperties = reflectMetaData->getAllProperties();
			for (const IReflectProperty* reflectProperty : reflectProperties)
			{
				isDefault &= reflectProperty->isDefault();
				if (isDefault == false) break;
			}

			if (isDefault == false) break;
		}
		return isDefault;
	}
}

#undef REFLECT_OBJECT_SEQUENCE_TEMPLATE
#undef REFLECT_OBJECT_SEQUENCE_CLASS