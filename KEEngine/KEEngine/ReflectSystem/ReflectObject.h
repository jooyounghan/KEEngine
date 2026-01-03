#pragma once
#include "ReflectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectObject
	{
	public:
		ReflectObject(ObjectType* object);
		NONCOPYABLE(ReflectObject);

	protected:
		static void initializeMetaData();
		static void ensureInitialized();
		static ReflectMetaData<ObjectType> _reflectMetaData;

	public:
		static const ReflectMetaData<ObjectType>& getReflectMetaData();

	protected:
		void initializeProperties();
		template<typename PropertyType, typename ...Args>
		void registerProperty(FlyweightStringA propertyName, Args... args);;

	public:
		using ReflectPropertyIndexMap = std::unordered_map<FlyweightStringA, uint32, HASH(FlyweightStringA)>;
		using ReflectPropertyList = std::vector<std::unique_ptr<IReflectProperty>>;

	protected:
		ReflectPropertyIndexMap	_reflectPropertyIndexMap;
		ReflectPropertyList		_reflectPropertyList;
		ObjectType* _object;

	public:
		void initialize();
	};
}
#include "ReflectObject.hpp"