#pragma once
#include "FlyweightString.h"

namespace ke
{
    class ReflectMetaData;

    class IReflectObject
    {
    public:
        virtual ~IReflectObject() = default;

    public:
        virtual const ReflectMetaData* getMetaData() const = 0;
    };
}