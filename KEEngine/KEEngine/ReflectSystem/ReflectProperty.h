#pragma once
#include "ReflectSystemPch.h"
#include "IBuffer.h"
#include "FlyweightString.h"
#include "ReflectParser.h"

namespace ke
{
	class IReflectProperty
	{
	public:
		IReflectProperty(const FlyweightStringA& name) : _name(name) {}
		virtual ~IReflectProperty() = default;

	public:
		const FlyweightStringA& getName() const { return _name; }
		inline bool getIsDefaultProperty() const { return _isDefaultProperty; }
		inline void setIsDefaultProperty(bool isDefaultProperty) { _isDefaultProperty = isDefaultProperty; }

	public:
		virtual Offset setFromString(const char* src) = 0;
		virtual Offset setFromBinary(const char* src) = 0;
		virtual void getToString(IBuffer* outBuffer) const = 0;
		virtual void getToBinary(IBuffer* outBuffer) const = 0;

	private:
		bool				_isDefaultProperty = false;
		FlyweightStringA	_name;
	};

	template<typename PropertyType>
	class ReflectProperty : public IReflectProperty
	{
		template<typename Object, typename Property>
		friend class PropertyMetaData;

	public:
		ReflectProperty(const FlyweightStringA& propertyName, PropertyType* property);
		~ReflectProperty() override = default;


	public:
		Offset setFromString(const char* src) override;
		Offset setFromBinary(const char* src) override;
		void getToString(IBuffer* outBuffer) const override;
		void getToBinary(IBuffer* outBuffer) const override;

	private:
		PropertyType*	_property;
	};
}
#include "ReflectProperty.hpp"