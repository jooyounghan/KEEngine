#pragma once

namespace ke
{
	enum class EReflectUIOption : uint8
	{
		None,
		Visible = 1 << 0,
		Editable = 1 << 1
	};

	class IReflectObject;
	class IReflectProperty
	{
	public:
		IReflectProperty(const FlyweightStringA& name);
		virtual ~IReflectProperty() = default;

	public:
		virtual void serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const = 0;
		virtual void deserializeFromXML(const XmlNode* xmlNode, const XmlAttribute* xmlAttribute, IReflectObject* obj) = 0;
	
	public:
		virtual void serializeToBinary(IBuffer* dstBuffer, const IReflectObject* obj) const = 0;
		virtual void deserializeFromBinary(const IBuffer* srcBuffer, const IReflectObject* obj) = 0;

	public:
		inline virtual bool isComplexProperty() const = 0;
		inline virtual bool isReflectObject() const = 0;
		inline virtual bool isDefault(const IReflectObject* obj) const = 0;

	public:
		const FlyweightStringA& getName() const { return _name; }
		const EReflectUIOption	getUIOption() const { return _uiOption; }
		void					setUIOption(EReflectUIOption uiOption) { _uiOption = uiOption; }

	protected:
		FlyweightStringA	_name;
		EReflectUIOption	_uiOption = EReflectUIOption::None;
		bool				_isModified = false;
	};
}