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
		virtual Offset setFromString(const char* src) = 0;
		virtual Offset setFromBinary(const char* src) = 0;
		virtual void getToString(IBuffer* outBuffer) const = 0;
		virtual void getToBinary(IBuffer* outBuffer) const = 0;

	private:
		FlyweightStringA _name;
	};
}