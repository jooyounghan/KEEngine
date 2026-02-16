#pragma once

namespace ke
{
	class IReflectObject;

	class IReflectObjectProperty
	{
	public:
		virtual ~IReflectObjectProperty() = default;

	public:
		virtual IReflectObject* getReflectObject(IReflectObject* parentReflectObject) = 0;
		virtual const IReflectObject* getReflectObject(const IReflectObject* parentReflectObject) const = 0;
	};
}
