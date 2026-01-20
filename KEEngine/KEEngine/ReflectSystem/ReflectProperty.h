#pragma once
#include "IReflectObject.h"
#include "FlyweightString.h"
#include "IBuffer.h"
#include "ReflectParser.h"
#include "IDefaultableReflectProperty.h"
#include <memory>

namespace ke
{
	DECLARE_ENUM_CLASS(EReflectUIOption, uint8,
		None,
		Visible = 1 << 0,
		Editable = 1 << 1
	);

	class IReflectProperty
	{
	public:
		constexpr IReflectProperty(const FlyweightStringA& name) : _name(name) {};
		virtual ~IReflectProperty() = default;
		
	private:
		FlyweightStringA	_name;
		EReflectUIOption	_uiOption = EReflectUIOption::None;

	public:
		inline const FlyweightStringA& getName() const { return _name; }
		inline void setUIOption(const EReflectUIOption& uiOption) { _uiOption = uiOption; }
		inline EReflectUIOption getUIOption() const { return _uiOption; }

	public:
		inline virtual bool isReflectObject() const = 0;
		inline virtual const ReflectMetaData* getMetaData() const = 0;

	public:
		inline virtual size_t getPropertyBufferSize() const = 0;

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src) = 0;
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const = 0;
		virtual void setFromString(IReflectObject* object, const char* src) = 0;
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const = 0;

	public:
		virtual IDefaultableReflectPropertyBase* asDefaultablePropertyBase() { return nullptr; }
	};

	template <typename ObjectType, typename PropertyType>
	using Getter = PropertyType & (ObjectType::*)();
	template <typename ObjectType, typename PropertyType>
	using ConstGetter = const PropertyType& (ObjectType::*)() const;
	template <typename ObjectType, typename PropertyType>
	using Setter = void (ObjectType::*)(const PropertyType&);

	template<typename ObjectType, typename PropertyType>
	class ReflectPropertyBase : public IReflectProperty
	{
	public:
		ReflectPropertyBase(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);
		~ReflectPropertyBase() override = default;
		DELETE_DEFAULT_CONSTRUCTOR(ReflectPropertyBase);

	private:
		Getter<ObjectType, PropertyType>			_getter;
		ConstGetter<ObjectType, PropertyType> 		_constGetter;
		Setter<ObjectType, PropertyType>			_setter;

	public:
		PropertyType& get(IReflectObject* o) { return (static_cast<ObjectType*>(o)->*_getter)(); }
		const PropertyType& get(const IReflectObject* o) const { return (static_cast<const ObjectType*>(o)->*_constGetter)(); }
		void set(IReflectObject* o, const PropertyType& v) { (static_cast<ObjectType*>(o)->*_setter)(v); }
	};

	template<typename ObjectType, typename PropertyType>
	class ReflectPODProperty : public ReflectPropertyBase<ObjectType, PropertyType>, public IDefaultableReflectProperty<PropertyType>
	{
	public:
		ReflectPODProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);
		~ReflectPODProperty() override = default;

	public:
		inline virtual bool isReflectObject() const { return false; };
		inline virtual const ReflectMetaData* getMetaData() const { return nullptr; }

	public:
		inline virtual size_t getPropertyBufferSize() const { return sizeof(PropertyType); }

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src);
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const;
		virtual void setFromString(IReflectObject* object, const char* src);
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const;

	public:
		inline virtual IDefaultableReflectPropertyBase* asDefaultablePropertyBase() override { return static_cast<IDefaultableReflectPropertyBase*>(this); }
	};

	template<typename ObjectType, typename PropertyType>
	class ReflectObjectProperty : public ReflectPropertyBase<ObjectType, PropertyType>
	{
	public:
		ReflectObjectProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);
		~ReflectObjectProperty() override = default;

	public:
		inline virtual bool isReflectObject() const { return true; };
		inline virtual const ReflectMetaData* getMetaData() const { return PropertyType::getObjectMetaData(); }

	public:
		inline virtual size_t getPropertyBufferSize() const { return INVALID_INDEX(size_t); }

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src);
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const;
		virtual void setFromString(IReflectObject* object, const char* src);
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const;
	};
}
#include "ReflectProperty.hpp"