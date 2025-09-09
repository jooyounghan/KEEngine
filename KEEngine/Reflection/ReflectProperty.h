#pragma once
#include "ReflectParser.h"
#include "FlyweightString.h"

namespace ke
{
	/*
	ReflectProperty�� �� Ÿ�Կ� XML / Binary���� Serialize, Deserialize�� �����Ѵ�
	���� const char*�� ���� Setter�� void*�� ���� Setter�� �⺻������ �����Ѵ�
	*/

	class IReflectProperty
	{
	protected:
		FlyweightStringA _propertyName;

	public:
		virtual void setFromString(const char* src) = 0;
		virtual void setFromBinary(void const* src) = 0;

	public:
		virtual const char* getToString() const = 0;
		virtual const void* getToBinary() const = 0;
	};

	template<typename PropertyType>
	class ReflectProperty : public IReflectProperty
	{
	private:
		PropertyType _property;

	public:
		inline const char* getPropertName() const { return _propertyName.c_str(); }
		inline void setReflectProperty(const PropertyType& property) { _property = property; }
		inline void setReflectProperty(PropertyType&& property) { _property = move(property); }
		inline const PropertyType& getReflectProperty() const { return _property; }

	public:
		void setFromString(const char* src) override { _property = move(ReflectParser<PropertyType>::ParseFromString(src)); }
		void setFromBinary(void const* src) override { memcpy(&_property, src, sizeof(PropertyType)); }
		const char* getToString() const override { return ReflectParser<PropertyType>::ParseToString(_property); }
		const void* getToBinary() const override { return static_cast<const void*>(&_property); }
	};
}

#include "ReflectProperty.hpp"