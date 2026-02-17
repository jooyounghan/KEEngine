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

	protected:
		static ReflectMetaData _reflectMetaData;
		static FlyweightStringA _objectName;
	};
}
#include "ReflectObject.hpp"