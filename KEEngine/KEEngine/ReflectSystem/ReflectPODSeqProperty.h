#pragma once
#include "IReflectPODSeqProperty.h"
#include "IReflectPODProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectParser.h"
#include "EnumUtil.h"

namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	class ReflectPODSeqProperty : public IReflectPODSeqProperty, public ReflectPODPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>
	{
	public:
		ReflectPODSeqProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
		);

	protected:
		virtual const void* getTypeId() const;

	public:
		virtual size_t	size(const IReflectObject* parentReflectObject) const override;
		virtual void	resize(const IReflectObject* object, size_t newSize) override;

	protected:
		virtual IReflectPODProperty* getElementProperty(const size_t index, IReflectObject* object) override;
		virtual const IReflectPODProperty* getElementProperty(const size_t index, const IReflectObject* object) const override;

	private:
		class ElementProxy : public IReflectPODProperty, public ReflectPODPropertyInfo<PropertyType>
		{
		public:
			ElementProxy();

			void set(PropertyType* ptr) { _ptr = ptr; _constPtr = ptr; }
			void setConst(const PropertyType* ptr) const { _constPtr = ptr; }

		protected:
			virtual const void* getTypeId() const override;

		public:
			virtual void fromBianry(IReflectObject* object, const void* src) override;
			virtual void toBinary(const IReflectObject* object, IBuffer* outDst) const override;
			virtual void fromString(IReflectObject* object, const char* src, size_t strlen) override;
			virtual void toString(const IReflectObject* object, IBuffer* outStringBuffer) const override;

		private:
			PropertyType*			_ptr = nullptr;
			mutable const PropertyType*	_constPtr = nullptr;
		};

		mutable ElementProxy _elementProxy;
	};
}
#include "ReflectPODSeqProperty.hpp"