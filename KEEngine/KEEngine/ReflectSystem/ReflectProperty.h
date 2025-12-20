#pragma once
#include "IReflection.h"

namespace ke
{
	template<typename PropertyType>
	class ReflectProperty : public IReflection
	{
	public:
		DELETE_CONSTRUCTOR(ReflectProperty);
		ReflectProperty(const char* propertyName) requires std::is_base_of_v<IReflection, PropertyType>
			: IReflection(propertyName), _property(propertyName)
		{
		}

		ReflectProperty(const char* propertyName) requires (!std::is_base_of_v<IReflection, PropertyType>)
			: IReflection(propertyName)
		{
		}

		~ReflectProperty() override = default;

	public:
		inline bool getIsDefaultProperty() const { return _isDefaultProperty; }
		inline bool setIsDefaultProperty(bool isDefaultProperty) { _isDefaultProperty = isDefaultProperty; }

	public:
		inline void setReflectProperty(const PropertyType& property) { _property = property; }
		inline void setReflectProperty(PropertyType&& property) { _property = move(property); }
		inline const PropertyType& getReflectProperty() const { return _property; }

	public:
		void setFromString(const char* src) override;
		void setFromBinary(void const* src) override;
		void getToString(IBuffer* outBuffer) const override;
		void getToBinary(IBuffer* outBuffer) const override;

	private:
		bool			_isDefaultProperty = false; 
		PropertyType	_property;
	};
}
#include "ReflectProperty.hpp"