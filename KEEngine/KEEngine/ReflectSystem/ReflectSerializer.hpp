#include "ReflectSerializer.h"
namespace ke
{
	template<typename ObjectType>
	void ReflectSerializer<ObjectType>::serializeToXML(IBuffer* outBuffer, const ReflectObject<ObjectType>* obj)
	{
		const ReflectMetaData* reflectMetaData = obj->getMetaData();
		serializeToXMLInner(outBuffer, reflectMetaData);
	}

	template<typename ObjectType>
	void ke::ReflectSerializer<ObjectType>::serializeToXMLInner(IBuffer* outBuffer, const ReflectMetaData* reflectMetaData)
	{
		const std::vector<PTR(IReflectProperty)>& properties = reflectMetaData->getAllProperties();

		for (const PTR(IReflectProperty)& property : properties)
		{
			if (property->isReflectObject())
			{
				// Reflect Object are serialize as children nodes
				serializeToXMLInner(outBuffer, property->getMetaData());
			}
			else
			{
				// Reflect POD are serialize as attributes
				//property.get()->getToString(obj, outBuffer);

			}
		}
	}
}