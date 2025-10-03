#pragma once
#include "ReflectMetaData.h"

#define REFLECT_OBJECT_CONSTRUCTOR() ReflectObject(this)

namespace ke
{
	template<typename ObjectType>
	class ReflectObject
	{
	public:
		ReflectObject(ObjectType* object);

	private:
		ObjectType* _object;
	
	private:
		inline static ReflectMetaData InitializeMetaData();
		inline static ReflectMetaData _metaData = InitializeMetaData();
	};
}

/*
Ŭ�������� ReflectMetaData�� Static ������ �����Ѵ�.
ReflectMetaData�� ReflectObject�� �����ϴ� ReflectProperty�� ���� ��Ÿ ������ ��� �ִ�.
	��Ÿ �������� Property�� �̸�, Ÿ��, �⺻�� ���� ���Եȴ�.
	ReflectMetaData�� ReflectObject�� Static �Լ��� GetMetaData()�� ���� ������ �� �ִ�.
	ReflectMetaData�� ReflectProperty�� ���� Getter�� Instance�� ���ڷ� �޾Ƽ� �����Ѵ�.
*/

#include "ReflectObject.hpp"