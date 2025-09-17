#pragma once
#include "FlyweightString.h"
#include "ReflectParser.h"

namespace ke
{
	/*
	ReflectProperty는 각 타입에 XML / Binary로의 Serialize, Deserialize를 지원한다
	따라서 const char*에 대한 Setter와 void*에 대한 Setter가 기본적으로 존재한다
	*/
	

	class IReflectProperty
	{
	public:
		IReflectProperty(const char* str);

	protected:
		FlyweightStringA _propertyName;

	public:
		virtual void setFromString(const char* src) = 0;
		virtual void setFromBinary(void const* src) = 0;

	public:
		virtual OwnedStringA getToString() const = 0;
		virtual const void* getToBinary() const = 0;
	};

	template<typename PropertyType>
	class ReflectProperty : public IReflectProperty
	{
	public:
		DELETE_CONSTRUCTOR(ReflectProperty);
		ReflectProperty(const char* str);

	private:
		PropertyType _property;

	public:
		inline const char* getPropertName() const { return _propertyName.c_str(); }
		inline void setReflectProperty(const PropertyType& property) { _property = property; }
		inline void setReflectProperty(PropertyType&& property) { _property = move(property); }
		inline const PropertyType& getReflectProperty() const { return _property; }

	public:
		void setFromString(const char* src) override;
		void setFromBinary(void const* src) override;
		OwnedStringA getToString() const override;
		void getToBinary(StaticBuffer<kPropertyBinaryBufferSize>& outBuffer) override;
	};
}

#include "ReflectProperty.hpp"