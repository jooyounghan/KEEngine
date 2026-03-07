#pragma once
#include "IReflectProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectProperty : public IReflectProperty, public ReflectPropertyAccessor<ObjectType, PropertyType>
	{
    public:
        ReflectProperty(
            const FlyweightStringA& name
            , Getter<ObjectType, PropertyType> getter
            , ConstGetter<ObjectType, PropertyType> constGetter
            , Setter<ObjectType, PropertyType> setter
        );
        ~ReflectProperty() override = default;

   
	public:
		virtual void serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const override final;
		virtual void deserializeFromXML(const XmlNode* xmlNode, const XmlAttribute* xmlAttribute, IReflectObject* obj) override final;

	public:
		virtual void serializeToBinary(IBuffer* dstBuffer, const IReflectObject* obj) const override final;
		virtual void deserializeFromBinary(const IBuffer* srcBuffer, const IReflectObject* obj) override final;

	protected:
		inline virtual bool isComplexProperty() const final { return false; }
		inline virtual bool isReflectObject() const final { return false; }
		inline virtual bool isDefault(const IReflectObject* obj) const final { return this->get(obj) == _defaultValue; }

	protected:
		PropertyType _defaultValue;
    };
}
#include "ReflectProperty.hpp"