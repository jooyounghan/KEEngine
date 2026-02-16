#pragma once
#include "IReflectObject.h"
#include "FlyweightString.h"
#include "ReflectParser.h"

namespace ke
{
	DECLARE_ENUM_CLASS(EReflectUIOption, uint8,
		None,
		Visible = 1 << 0,
		Editable = 1 << 1
	);

	DECLARE_ENUM_CLASS(EReflectPropertyType, uint8,
		POD,
		Object,
		Vector,
		Enum
	);

	class IReflectPODProperty;
	class IReflectVectorProperty;
	class IReflectEnumProperty;

	template<typename PropertyType>
	class ReflectPODPropertyBase;

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
		// New extensible type system
		virtual EReflectPropertyType getPropertyType() const = 0;
		
		// Template-based safe casting for any property type
		template<typename T>
		T* as();
		
		template<typename T>
		const T* as() const;

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src) = 0;
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const = 0;
		virtual void setFromString(IReflectObject* object, const char* src, size_t strlen) = 0;
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const = 0;
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
}
#include "IReflectProperty.hpp"