#pragma once
#include "IReflectProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	class ReflectSequenceProperty : public IReflectProperty, public ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>
	{
	public:
		ReflectSequenceProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
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
		ContainerType<PropertyType> _defaultValue;
	};
}
#include "ReflectSequenceProperty.hpp"
