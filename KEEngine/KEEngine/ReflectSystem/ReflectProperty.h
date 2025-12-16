#pragma once
#include "FlyweightString.h"

namespace ke
{
	class IBuffer;
	
	class IReflectProperty
	{
	public:
		IReflectProperty(const char* str) : _propertyName(str) {}
		virtual ~IReflectProperty() = default;

	protected:
		bool				_isDefaultProperty = false;
		FlyweightStringA	_propertyName;

	public:
		inline bool getIsDefaultProperty() const { return _isDefaultProperty; }
		inline bool setIsDefaultProperty(bool isDefaultProperty) { _isDefaultProperty = isDefaultProperty; }

	public:
		inline const FlyweightStringA& getPropertName() const { return _propertyName; }

	public:
		virtual void setFromString(const char* src) = 0;
		virtual void setFromBinary(void const* src) = 0;
		virtual void getToString(IBuffer* outBuffer) const = 0;
		virtual void getToBinary(IBuffer* outBuffer) const = 0;

	public:
		virtual void OnPropertyChanged() {};
	};

	template<typename PropertyType>
	class ReflectProperty : public IReflectProperty
	{
	public:
		using Type = PropertyType;

	public:
		DELETE_CONSTRUCTOR(ReflectProperty);
		ReflectProperty(const char* str);
		ReflectProperty(const char* str, const PropertyType& propertyType);
		ReflectProperty(const char* str, PropertyType&& propertyType);
		~ReflectProperty() = default;

	private:
		PropertyType _property;

	public:
		inline void setReflectProperty(const PropertyType& property) { _property = property; }
		inline void setReflectProperty(PropertyType&& property) { _property = move(property); }
		inline const PropertyType& getReflectProperty() const { return _property; }

	public:
		void setFromString(const char* src) override;
		void setFromBinary(void const* src) override;
		void getToString(IBuffer* outBuffer) const override;
		void getToBinary(IBuffer* outBuffer) const override;
	};

	template<typename PropertyType>
	class RangedReflectProperty : public IReflectProperty
	{
	public:
		DELETE_CONSTRUCTOR(RangedReflectProperty);
		RangedReflectProperty(const char* str, const PropertyType& maxPropertyType, const PropertyType& minPropertyType);
		RangedReflectProperty(const char* str, PropertyType&& maxPropertyType, PropertyType&& minPropertyType);
		~RangedReflectProperty() = default;

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
		void getToString(IBuffer* outBuffer) const override;
		void getToBinary(IBuffer* outBuffer) const override;
	};
}

#include "ReflectProperty.hpp"