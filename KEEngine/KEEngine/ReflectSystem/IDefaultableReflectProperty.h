#pragma once

namespace ke
{
	template<typename PropertyType>
	struct RangedPropertyInfo
	{
		PropertyType	_maxValue;
		PropertyType	_minValue;
		PropertyType	_step;
	};

	class IDefaultableReflectPropertyBase
	{
	public:
		virtual ~IDefaultableReflectPropertyBase() = default;
		virtual void setDefaultFromBuffer(const void* data, size_t size) = 0;
		virtual void assignRangeInfoFromBuffer(const void* min, const void* max, const void* step, size_t elemSize) = 0;
	};

	template<typename PropertyType>
	class IDefaultableReflectProperty : public IDefaultableReflectPropertyBase
	{
	public:
		inline const PropertyType& getDefaultValue() const { return _defaultValue; }

	public:
		inline bool hasRange() const { return _rangeInfo != nullptr; }
		void assignRangeInfo(const PropertyType& minValue, const PropertyType& maxValue, const PropertyType& step);
		inline const RangedPropertyInfo<PropertyType>* getRangeInfo() const { return _rangeInfo.get(); }

	public:
		virtual void setDefaultFromBuffer(const void* data, size_t size) override;
		virtual void assignRangeInfoFromBuffer(const void* min, const void* max, const void* step, size_t elemSize) override;

	protected:
		PTR(RangedPropertyInfo<PropertyType>) _rangeInfo = nullptr;

	protected:
		PropertyType	_defaultValue;
	};
}
#include "IDefaultableReflectProperty.hpp"