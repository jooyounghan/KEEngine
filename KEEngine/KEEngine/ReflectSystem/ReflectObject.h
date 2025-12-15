#pragma once
#include "ReflectSystemPch.h"
#include "ObjectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectObject
	{
	public:
		ReflectObject(ObjectType* object);

	protected:
		ObjectType* _object;

	protected:
		static void initializeMetaData();
		static void ensureInitialized();
		static ObjectMetaData<ObjectType> _metaData;

	public:
		static const ObjectMetaData<ObjectType>& getMetaData();
	};
}

/*
클래스마다 ReflectMetaData가 Static 변수로 존재한다.
ReflectMetaData는 ReflectObject를 구성하는 ReflectProperty에 대한 메타 정보를 담고 있다.
	메타 정보에는 Property의 이름, 타입, 기본값 등이 포함된다.
	ReflectMetaData는 ReflectObject의 Static 함수인 GetMetaData()를 통해 접근할 수 있다.
	ReflectMetaData는 ReflectProperty에 대한 Getter를 Instance를 인자로 받아서 제공한다.
*/

#include "ReflectObject.hpp"