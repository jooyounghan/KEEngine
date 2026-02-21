#pragma once
#include "IReflectObject.h"
#include "ReflectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectObject : public IReflectObject
	{
	public:
		ReflectObject();

	protected:
		static void initializeMetaData();
		static void bindMetaData();
		static void ensureInitialized();

	public:
		static const ReflectMetaData* getObjectMetaData();
		static const FlyweightStringA& getObjectName() { return _objectName; };

	public:
		inline virtual const ReflectMetaData* getMetaData() const override { return getObjectMetaData(); };
		virtual const FlyweightStringA& getName() const override { return _objectName; };

	protected:
		static ReflectMetaData _reflectMetaData;
		static FlyweightStringA _objectName;
	};
}
#include "ReflectObject.hpp"