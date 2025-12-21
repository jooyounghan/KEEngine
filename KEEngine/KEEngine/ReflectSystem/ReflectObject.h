#pragma once
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

	public:
		void initialize();

	public:
		Offset setFromString(const char* src) override;
		Offset setFromBinary(const char* src) override;
		void getToString(IBuffer* outBuffer) const override;
		void getToBinary(IBuffer* outBuffer) const override;
	};
}
#include "ReflectObject.hpp"