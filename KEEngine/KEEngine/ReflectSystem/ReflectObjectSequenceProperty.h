#pragma once
#include "IReflectObjectProperty.h"
#include "ReflectPropertyAccessor.h"

namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	class ReflectObjectSequenceProperty : public IReflectProperty, public ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>
	{
	public:
		ReflectObjectSequenceProperty(
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
		inline virtual bool isReflectObject() const final { return true; }
		inline virtual bool	isDefault(const IReflectObject* obj) const final;
	};
}
#include "ReflectObjectSequenceProperty.hpp"