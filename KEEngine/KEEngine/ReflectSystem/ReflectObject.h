#pragma once
#include "ReflectProperty.h"
#include "ReflectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectObject : public IReflection
	{
	public:
		ReflectObject(const char* objectName, ObjectType* object);

	protected:
		static void initializeMetaData();
		static void ensureInitialized();
		static ReflectMetaData<ObjectType> _reflectMetaData;

	public:
		static const ReflectMetaData<ObjectType>& getReflectMetaData();

	protected:
		ObjectType* _object;
	};
}
#include "ReflectObject.hpp"