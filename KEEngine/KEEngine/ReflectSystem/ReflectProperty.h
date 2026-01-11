#pragma once
#include "IReflectObject.h"
#include "FlyweightString.h"
#include "IBuffer.h"
#include <memory>

namespace ke
{
	class IReflectProperty
	{
	public:
		constexpr IReflectProperty(const FlyweightStringA& name) : _name(name) {};

	private:
		FlyweightStringA _name;

	public:
		//constexpr virtual bool isReflectObject() const = 0;
		//constexpr virtual size_t getPropertyBufferSize() const = 0;

	//public:
	//	virtual void setFromBianry(IReflectObject* object, const void* src) = 0;
	//	virtual void getToBinary(const IReflectObject* object, void* outDst) const = 0;
	//	virtual void setFromString(IReflectObject* object, const char* src) = 0;
	//	virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const = 0;
	};

	template <typename ObjectType, typename PropertyType>
	using Getter = PropertyType & (ObjectType::*)();
	template <typename ObjectType, typename PropertyType>
	using ConstGetter = const PropertyType& (ObjectType::*)() const;
	template <typename ObjectType, typename PropertyType>
	using Setter = void (ObjectType::*)(const PropertyType&);

	template<typename ObjectType, typename PropertyType>
	class ReflectProperty : public IReflectProperty
	{
	public:
		ReflectProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);
		DELETE_DEFAULT_CONSTRUCTOR(ReflectProperty);

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
#include "ReflectProperty.hpp"