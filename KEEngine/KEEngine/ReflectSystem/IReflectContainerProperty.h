#pragma once
#include "IReflectProperty.h"

namespace ke
{
	class IReflectObject;

	template <typename Container, typename T>
	concept ReflectContainerCompatible = requires(Container c, const Container cc, std::size_t index)
	{
		{ c.size() } -> std::same_as<std::size_t>;
		{ c.resize(index) } -> std::same_as<void>;
		{ c[index] } -> std::same_as<T*>;
		{ cc[index] } -> std::same_as<const T*>;
	};

	class IReflectContainerProperty : public IReflectProperty
	{
	public:
		IReflectContainerProperty(const FlyweightStringA& name);
		~IReflectContainerProperty() override = default;

	public:
		virtual size_t	size(const IReflectObject* object) const = 0;
		virtual void	resize(const IReflectObject* object, size_t newSize) = 0;
	};
}