#pragma once
#include "IReflectProperty.h"
#include "IReflectObject.h"

namespace ke
{
	class IReflectObjectProperty : public IReflectProperty
	{
	public:
		IReflectObjectProperty(const FlyweightStringA& name);
		~IReflectObjectProperty() override = default;

	public:
		virtual void serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const override final;
		virtual void deserializeFromXML(const XmlNode* xmlNode, const XmlAttribute* xmlAttribute, IReflectObject* obj) override final;

	public:
		virtual void serializeToBinary(IBuffer* dstBuffer, const IReflectObject* obj) const override final;
		virtual void deserializeFromBinary(const IBuffer* srcBuffer, const IReflectObject* obj) override final;

	public:
		inline virtual bool isComplexProperty() const final { return true; }
		inline virtual bool isReflectObject() const final { return true; }
		virtual bool		isDefault(const IReflectObject* obj) const final;

	public:
		virtual IReflectObject*			getReflectObject(IReflectObject* obj) = 0;
		virtual const IReflectObject*	getReflectObject(const IReflectObject* obj) const = 0;
	};
}