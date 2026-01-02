#pragma once
#include "ReflectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectObject
	{
	public:
		ReflectObject(ObjectType* object);

	protected:
		static void initializeMetaData();
		static void ensureInitialized();
		static ReflectMetaData<ObjectType> _reflectMetaData;

	public:
		static const ReflectMetaData<ObjectType>& getReflectMetaData();

	protected:
		ObjectType* _object;

	public:
		void initialize();
	};
}
#include "ReflectObject.hpp"