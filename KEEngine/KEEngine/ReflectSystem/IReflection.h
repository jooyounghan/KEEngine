#pragma once
#include "IBuffer.h"
#include "FlyweightString.h"
namespace ke
{
	class IReflection
	{
	public:
		IReflection(const char* name) : _name(name) {}
		virtual ~IReflection() = default;
		
	public:
		const FlyweightStringA& getName() const { return _name; }

	public:	
		virtual void serializeToString(IBuffer* outStringBuffer) const = 0;
		virtual void serializeToBinary(IBuffer* outBuffer) const = 0;
		virtual void deserializeFromString(const char* src) = 0;
		virtual void deserializeFromBinary(const void* src) = 0;

	private:
		FlyweightStringA _name;
	};
}