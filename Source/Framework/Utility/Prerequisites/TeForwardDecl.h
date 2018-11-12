#pragma once

namespace te
{
    class GeneralAllocator;
    template<class T> 
    class MemoryAllocator;
    template <class T, class Allocator>
    class StdAllocator;
    class BasicAllocator;

    class Console;

    class DynLib;
    class DynLibManager;

    template<class T> class Module;

    class Time;
    class Timer;

    class NonCopyable;
}