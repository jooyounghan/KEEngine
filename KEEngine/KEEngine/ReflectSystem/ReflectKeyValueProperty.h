#pragma once
#include "IReflectProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectContainerConcept.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>
	class ReflectKeyValueProperty : public IReflectProperty, public ReflectPropertyAccessor<ObjectType, ContainerType<KeyType, ValueType>>
	{
	public:
		ReflectKeyValueProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<KeyType, ValueType>> getter
			, ConstGetter<ObjectType, ContainerType<KeyType, ValueType>> constGetter
			, Setter<ObjectType, ContainerType<KeyType, ValueType>> setter
		);

	public:
		virtual void serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const override final;
		virtual void deserializeFromXML(const XmlNode* xmlNode, const XmlAttribute* xmlAttribute, IReflectObject* obj) override final;

	public:
		virtual void serializeToBinary(IBuffer* dstBuffer, const IReflectObject* obj) const override final;
		virtual void deserializeFromBinary(const IBuffer* srcBuffer, const IReflectObject* obj) override final;

	protected:
		inline virtual bool isComplexProperty() const final { return true; }
		inline virtual bool isReflectObject() const final { return false; }
		inline virtual bool	isDefault(const IReflectObject* obj) const final { return this->get(obj) == _defaultValue; };

	protected:
		ContainerType<KeyType, ValueType> _defaultValue;
	};
}
#include "ReflectKeyValueProperty.hpp"