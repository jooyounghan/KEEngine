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
		inline const char* getPropertName() const { return _propertyName.c_str(); }

	public:
		virtual void setFromString(const char* src) = 0;
		virtual void setFromBinary(void const* src) = 0;
		virtual void getToString(IStaticBuffer* outBuffer) const = 0;
		virtual void getToBinary(IStaticBuffer* outBuffer) const = 0;

	public:
		virtual void OnPropertyChanged() {};
	};

	template<typename PropertyType>
	class ReflectProperty : public IReflectProperty
	{
	public:
		DELETE_CONSTRUCTOR(ReflectProperty);
		ReflectProperty(const char* str, const PropertyType& propertyType);
		ReflectProperty(const char* str, PropertyType&& propertyType);

	private:
		PropertyType _property;

	public:
		inline void setReflectProperty(const PropertyType& property) { _property = property; }
		inline void setReflectProperty(PropertyType&& property) { _property = move(property); }
		inline const PropertyType& getReflectProperty() const { return _property; }

	public:
		void setFromString(const char* src) override;
		void setFromBinary(void const* src) override;
		void getToString(IStaticBuffer* outBuffer) const override;
		void getToBinary(IStaticBuffer* outBuffer) const override;
	};

	template<typename PropertyType>
	class RangedReflectProperty : public IReflectProperty
	{
	public:
		DELETE_CONSTRUCTOR(RangedReflectProperty);
		RangedReflectProperty(const char* str, const PropertyType& maxPropertyType, const PropertyType& minPropertyType);
		RangedReflectProperty(const char* str, PropertyType&& maxPropertyType, PropertyType&& minPropertyType);

	private:
		PropertyType _minProperty;
		PropertyType _maxProperty;

	public:
		inline void setMaxReflectProperty(const PropertyType& property) { _maxProperty = property; }
		inline void setMaxReflectProperty(PropertyType&& property) { _maxProperty = move(property); }
		inline void setMinReflectProperty(const PropertyType& property) { _minProperty = property; }
		inline void setMinReflectProperty(PropertyType&& property) { _minProperty = move(property); }
		inline const PropertyType& getMaxReflectProperty() const { return _maxProperty; }
		inline const PropertyType& getMinReflectProperty() const { return _minProperty; }

	public:
		void setFromString(const char* src) override;
		void setFromBinary(void const* src) override;
		void getToString(IStaticBuffer* outBuffer) const override;
		void getToBinary(IStaticBuffer* outBuffer) const override;
	};
}

#include "ReflectProperty.hpp"