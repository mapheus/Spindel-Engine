#pragma once

#include "Spindel/Core/Core.h"

namespace Spindel
{
    template<class Derived>
    class Singleton
    {

    public:

        static Ref<Derived>& instance();

    protected:

        Singleton() {};


    private:

        Singleton(const Singleton&) {};

        Singleton& operator=(const Singleton&) { return *this; };

    private:

        static Ref<Derived> _instance;
    };

}